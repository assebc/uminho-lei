import java.io.IOException;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;
import java.util.Map;
import java.util.Queue;
import java.util.ArrayDeque;
import java.util.HashMap;

public class Demultiplexer implements AutoCloseable{
    private TaggedConnection tc;
    private final ReentrantLock lock = new ReentrantLock();
    private Map<Integer,FrameValue> tags = new HashMap<>();
    private IOException exception = null;

    private class FrameValue{
        int waiters = 0;
        Queue<byte []> queue = new ArrayDeque<>();
        Condition c = lock.newCondition();

        public FrameValue(){}
    }

    public Demultiplexer(TaggedConnection conn) throws IOException {
        this.tc = conn;
    }
    
    public void start() { 
        new Thread(() -> {
            try{
                while(true){
                    TaggedConnection.Frame frame = this.tc.receive();
                    this.lock.lock();
                    try{
                        FrameValue fv = this.tags.get(frame.tag);
                        if(fv == null){
                            fv = new FrameValue();
                            this.tags.put(frame.tag,fv);
                        }
                        fv.queue.add(frame.data);
                        fv.c.signal();
                    } finally{
                        this.lock.unlock();
                    }
                }
            } catch (IOException e){
                this.exception = e;
            }
        }).start();
    }

    public void send(TaggedConnection.Frame frame) throws IOException {
        this.tc.send(frame.tag,frame.data);
    }

    public void send(int tag, byte[] data) throws IOException { 
        this.tc.send(tag,data);
    }

    public byte[] receive(int tag) throws IOException, InterruptedException {
        this.lock.lock();
        FrameValue fv;
        try{
            fv = this.tags.get(tag);
            if (fv == null){
                fv = new FrameValue();
                this.tags.put(tag,fv);
            }
            fv.waiters++;
            while(true){
                if(!fv.queue.isEmpty()){
                    fv.waiters--;
                    byte[] reply = fv.queue.poll();
                    if (fv.waiters == 0 && fv.queue.isEmpty()) this.tags.remove(tag);
                    return reply;
                }
                if (this.exception != null) throw this.exception;
                fv.c.await();
            }
        } finally{
            this.lock.unlock();
        }
    }

    @Override
    public void close() throws Exception {  
        this.tc.close();
    }
    
}
