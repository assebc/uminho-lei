import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

class ServerWorker implements Runnable{
    
    private Socket socket;
    private final Register register;

    public ServerWorker(Socket socket, Register reg){
        this.socket = socket;
        this.register = reg;
    }

    @Override
    public void run(){
        
        try{
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream());
    
            String line;
            while ((line = in.readLine()) != null) {
                out.println(String.valueOf(this.register.add(Integer.parseInt(line))));
                out.flush();
            }
                
            out.println(String.valueOf(this.register.avg()));
            out.flush();
    
            socket.shutdownOutput();
            socket.shutdownInput();
            socket.close();
        } catch(IOException e){
            System.out.println(e);
        }      
    }
}

public class EchoServer {

    public static void main(String[] args) {
        try {
            System.out.println("Starting server...");
            ServerSocket ss = new ServerSocket(12345);

            while(true){
                Socket socket = ss.accept();
                Thread worker = new Thread(new ServerWorker(socket,new Register()));
                worker.start();
            }
        
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}