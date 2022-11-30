import java.net.ServerSocket;
import java.net.Socket;

public class ServerWithWorkers {
    final static int WORKERS_PER_CONNECTION = 3;

    public static void main(String[] args) throws Exception {
        try (ServerSocket ss = new ServerSocket(12345)) {
            while(true) {
                Socket s = ss.accept();
                try (FramedConnection c = new FramedConnection(s)) {
                    
                    Runnable worker = () -> {
                        try {
                            while(true) {
                                TaggedConnection.Frame frame = c.receive();
                                int tag = frame.tag;
                                String data = new String(frame.data);
                                if (frame.tag == 0)
                                    System.out.println("Got one-way: " + data);
                                else if (frame.tag % 2 == 1) {
                                    System.out.println("Replying to: " + data);
                                    c.send(frame.tag, data.toUpperCase().getBytes());
                                } else {
                                    for (int i = 0; i < data.length(); ++i) {
                                        String str = data.substring(i, i+1);
                                        System.out.println("Streaming: " + str);
                                        c.send(tag, str.getBytes());
                                        Thread.sleep(100);
                                    }
                                    c.send(tag, new byte[0]);
                                }
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

