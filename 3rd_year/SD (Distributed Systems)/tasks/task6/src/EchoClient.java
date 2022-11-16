import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

class Register{
    
    private int sum = 0;
    private int n = 0;

    public int add(int val){
        this.sum+=val;
        this.n++;
        return this.sum;
    }

    public float avg(){
        return (float)this.sum/this.n;
    }
    
}

public class EchoClient {

    public static void main(String[] args) {
        try {
            System.out.println("Sending socket...");
            Socket socket = new Socket("localhost", 12345);

            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream());

            BufferedReader systemIn = new BufferedReader(new InputStreamReader(System.in));

            String userInput;
            while ((userInput = systemIn.readLine()) != null) {
                out.println(userInput);
                out.flush();

                String response = in.readLine();
                System.out.println("Server response: " + response);
            }

            socket.shutdownOutput();

            String response = in.readLine();
            System.out.println("Average: " +response);

            socket.shutdownInput();
            socket.close();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}