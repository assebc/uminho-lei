import java.io.IOException;
//import java.io.InterruptedException;
//import java.net.Socket;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;
import java.util.Map;
import java.util.HashMap;

public class Demultiplexer implements AutoCloseable{
    private Thread thread;
    private final ReentrantLock sendLock = new ReentrantLock();
    private final ReentrantLock receiveLock = new ReentrantLock();
    private final Condition condition = this.receiveLock.newCondition();
    private Map<Integer,TaggedConnection> tags = new HashMap<>();

    public Demultiplexer(TaggedConnection conn) throws IOException {
        this.tags.put(conn.receive().tag, conn);
        this.thread = new Thread();
    }
    
    public void start() { 
        this.thread.start();
    }

    public void send(TaggedConnection.Frame frame) throws IOException {
        this.send(frame.tag,frame.data);
    }

    public void send(int tag, byte[] data) throws IOException { 
        try{
            this.sendLock.lock();
            this.tags.get(tag).send(tag,data);
        } finally{
            this.sendLock.unlock();
        }
    }

    public byte[] receive(int tag) throws IOException, InterruptedException {
        try{
            this.receiveLock.lock();
            if (this.tags.containsKey(tag)){
                TaggedConnection.Frame frame = this.tags.get(tag).receive();
                return frame.data;
            }
            else this.condition.await();
        } finally{
            this.receiveLock.unlock();
        }
        return null;
    }

    @Override
    public void close() throws Exception {  
        for(int t:this.tags.keySet()){
            this.tags.get(t).close();
        }
    }
    
}
