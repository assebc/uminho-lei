import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.concurrent.locks.ReentrantLock;

public class FramedConnection implements AutoCloseable{
    private final Socket socket;
    private final DataInputStream in;
    private final DataOutputStream out;
    private final ReentrantLock sendLock = new ReentrantLock();
    private final ReentrantLock receiveLock = new ReentrantLock();

    public FramedConnection(Socket socket) throws IOException{
        this.socket = socket;
        this.in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
        this.out = new DataOutputStream(new BufferedOutputStream(socket.getOutputStream()));
    }

    public void send(byte[] data) throws IOException{
        try{
            this.sendLock.lock();
            this.out.writeInt(data.length);
            this.out.write(data);
            this.out.flush();

        } finally{
            this.sendLock.unlock();
        }
    }

    public byte[] receive() throws IOException{
        byte[] data;
        try{
            this.receiveLock.lock();
            int size = this.in.readInt();
            data = new byte[size];
            this.in.readFully(data);  
            return data; 

        } finally{
            this.receiveLock.unlock();
        }
    }
    public void close() throws IOException{
        this.socket.close();
    }
}