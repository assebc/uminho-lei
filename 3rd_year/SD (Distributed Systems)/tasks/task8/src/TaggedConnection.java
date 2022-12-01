import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.concurrent.locks.ReentrantLock;

public class TaggedConnection implements AutoCloseable{
    private final Socket socket;
    private final DataInputStream in;
    private final DataOutputStream out;
    private final ReentrantLock sendLock = new ReentrantLock();
    private final ReentrantLock receiveLock = new ReentrantLock();
    
    public static class Frame{
        public final int tag;
        public final byte[] data;
        public Frame(int tag, byte[] data){ this.tag = tag; this.data = data;}
    }
    public TaggedConnection(Socket socket) throws IOException{
        this.socket = socket;
        this.in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
        this.out = new DataOutputStream(new BufferedOutputStream(socket.getOutputStream()));
    }

    public void send(Frame frame) throws IOException{
        this.send(frame.tag,frame.data);
    }

    public void send(int tag, byte[]data) throws IOException{
        try{
            this.sendLock.lock();
            this.out.writeInt(data.length);
            this.out.writeInt(tag);
            this.out.write(data);
            this.out.flush();
        } finally{
            this.sendLock.unlock();
        }
    }

    public Frame receive() throws IOException {
        byte[] data;
        try{
            this.receiveLock.lock();
            int size = this.in.readInt();
            int tag = this.in.readInt();
            data = new byte[size];
            this.in.readFully(data);  
            return new Frame(tag,data); 

        } finally{
            this.receiveLock.unlock();
        }
    }

    @Override
    public void close() throws Exception {
        this.socket.close();
        
    }
}