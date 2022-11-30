import java.net.ServerSocket;
import java.net.Socket;

public class SimpleServerWithWorkers {
    final static int WORKERS_PER_CONNECTION = 3;

    public static void main(String[] args) throws Exception {
        try (ServerSocket ss = new ServerSocket(12345)) {
            while(true) {
                Socket s = ss.accept();
                try (FramedConnection c = new FramedConnection(s)) {
                    Runnable worker = () -> {
                        try{
                            while(true) {
                                byte[] b = c.receive();
                                String msg = new String(b);
                                System.out.println("Replying to: " + msg);
                                c.send(msg.toUpperCase().getBytes());
                            }
                        } catch (Exception ignored) { }
                    };

                    for (int i = 0; i < WORKERS_PER_CONNECTION; ++i)
                        new Thread(worker).start();
                }
            }
        }
    }
}

