import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.concurrent.locks.ReentrantLock;

public class Client{
    
    private ReentrantLock lock;
    private String name;
    private String password;
    private Integer x;
    private Integer y;
    private Integer coupons;
    private Boolean notif_recompensas;

    public Client(){
        this.name = "";
        this.password = "";
        this.x = 0;
        this.y = 0;
        this.coupons = 0;
        this.notif_recompensas = true;
        this.lock = new ReentrantLock();
    }

    public Client(String user,String password){
        this.name = user;
        this.password = password;
        this.x = 0;
        this.y = 0;
        this.coupons = 0;
        this.notif_recompensas = true;
        this.lock = new ReentrantLock();
    }

    public Celula getCelula(){
        return new Celula(1000,getX(),getY());
    }
    public String getUserName(){
        return this.name;
    }

    public String getPassword(){
        return this.password;
    }

    public void setX(Integer x) {
        try{
            this.lock.lock();
            this.x = x;
        } finally{
            this.lock.unlock();
        }
        
    }

    public void setY(Integer y) {
        try{
            this.lock.lock();
            this.y = y;
        } finally{
            this.lock.unlock();
        }
    }

    public Integer getX() {
        try{
            this.lock.lock();
            return this.x;
        } finally{
            this.lock.unlock();
        }
    }

    public Integer getY() {
        try{
            this.lock.lock();
            return this.y;
        } finally{
            this.lock.unlock();
        }
    }

    public void addCoupon(){
        try{
            this.lock.lock();
            this.coupons += 1;
        } finally{
            this.lock.unlock();
        }
    }

    public void removeCoupon(){
        try{
            this.lock.lock();
            this.coupons -=1;
        } finally{
            this.lock.unlock();
        }
    }

    public Integer getCoupons(){
        try{
            this.lock.lock();
            return this.coupons;
        } finally{
            this.lock.unlock();
        }
    }

    public Boolean hasNotifications(){
        try{
            this.lock.lock();
            return this.notif_recompensas;
        } finally{
            this.lock.unlock();
        }
    }
    
    public void activateNotifications(){
        try{
            this.lock.lock();
            this.notif_recompensas = true;
        } finally{
            this.lock.unlock();
        }
    }
    
    public void deactivateNotifications(){
        try{
            this.lock.lock();
            this.notif_recompensas = false;
        } finally{
            this.lock.unlock();
        }
    }
    
    public String[] getCoords(){
        try{
            this.lock.lock();
            String [] coords = new String [2];
            coords[0] = String.valueOf(this.x);
            coords[1] = String.valueOf(this.x);
            return coords;
        } finally{
            this.lock.unlock();
        }
    }

    public String toString(){
        return this.getUserName() + "->" + this.getPassword();
    }

    private static String initUser(BufferedReader in, PrintWriter out, BufferedReader systemIn) throws IOException{
        for(int i = 0; i<6;i++){
            System.out.println(in.readLine());
        }
        out.println(systemIn.readLine());
        out.flush();
        
        String ans = in.readLine();
        System.out.println("\n"+ans);
        return ans;
    }

    private static void closeClient(Socket socket) throws IOException{
        socket.shutdownOutput();
        socket.shutdownInput();
        socket.close(); 
        System.exit(0);
    }
    
    private static void clearScreen(){
        System.out.print("\033[H\033[2J");  
        System.out.flush(); 
    }

    private static Client criaUser(BufferedReader in, PrintWriter out, BufferedReader systemIn, String [] cliente, String ans) throws IOException{
        cliente = new String(systemIn.readLine()).split(" ");
        Client cl = new Client(cliente[0],cliente[1]);
        out.println(cl.getUserName() + ";" + cl.getPassword());
        out.flush();
        ans = in.readLine();
        return cl;
    }
    
    private static void wrongPassword(BufferedReader in, PrintWriter out, BufferedReader systemIn, String [] cliente, String ans, Client cl) throws IOException{
        while(ans.equals("Palavra-passe errada ou esse nome de utilizador já está a ser utilizado!")){

            System.out.println("\n"+ans);
            ans = in.readLine();
            System.out.println(ans);
            cliente = new String(systemIn.readLine()).split(" ");
            cl = new Client(cliente[0],cliente[1]);
            out.println(cl.getUserName() + ";" + cl.getPassword());
            out.flush();
            ans = in.readLine();
        }
        System.out.println("\n"+ans);
    }

    private static void LogIn(BufferedReader in, PrintWriter out, BufferedReader systemIn) throws IOException{
        for(int i = 0;i<2;i++){
            System.out.println(in.readLine());
        }
        out.println(systemIn.readLine());
        out.flush();
    }

    private static void menuLogIn(BufferedReader in, PrintWriter out, BufferedReader systemIn, Socket socket, Boolean opts, Boolean no) throws IOException{

        if(no) clearScreen();
        int max = 0;
        if (opts) max = 6; else max = 5;
        for(int i = 0;i<max;i++){
            System.out.println(in.readLine());
        }

        String opt = systemIn.readLine();
        out.println(opt);
        out.flush();
        
        if(opt.equals("2")){
            menuLogIn(in,out,systemIn,socket,!opts,true);
        } else if(opt.equals("3")){
            String ans = in.readLine();
            System.out.println(ans + "\n");
            if(!ans.contains("Não")){
                out.println(systemIn.readLine());
                out.flush();
                System.out.println(in.readLine()+ "\n");
            }
            menuLogIn(in, out, systemIn, socket, opts,false);
        } else if(opt.equals("4")){
            System.out.println("\n" + in.readLine()); 
            closeClient(socket);
        } else{
            System.out.println("\n" + in.readLine());
        }
    }

    private static void menuReserva(BufferedReader in, PrintWriter out, BufferedReader systemIn, String ans, Socket socket) throws IOException{
        for(int i = 0;i<2;i++){
            ans = in.readLine();
            System.out.println(ans);
        }

        if(ans.equals("Não existem trotinetes nas suas redondezas!")){closeClient(socket);}

        out.println(systemIn.readLine()); // which trotinete
        out.flush();

        for(int i = 0;i<3;i++){
            System.out.println(in.readLine());
        }
        out.println(systemIn.readLine()); // coords which trotine was left
        out.flush();
    }

    private static void closingMenu(BufferedReader in, PrintWriter out, BufferedReader systemIn, Socket socket) throws IOException{
        String ans = "";
        for(int i = 0;i<4;i++){
            ans = in.readLine();
            System.out.println(ans);
        }  
        if(ans.equals("Não possui coupons para utilizar!")) closeClient(socket);
        else{
            String opt = systemIn.readLine().toUpperCase();
            out.println(opt);
            out.flush();
            System.out.println(in.readLine());
        }      
    }
    
    public static void main(String [] args) throws Exception{
        try{
            Socket socket = new Socket("localhost",12345);
            clearScreen(); 
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream());
            BufferedReader systemIn = new BufferedReader(new InputStreamReader(System.in));
            
            String ans = initUser(in,out,systemIn);

            if(ans.contains("Adeus")){closeClient(socket);}

            String [] cliente = new String[2];
            Client cl = criaUser(in, out, systemIn, cliente, ans);
            
            wrongPassword(in, out, systemIn, cliente, ans, cl);
            
            clearScreen();

            LogIn(in, out, systemIn);
            menuLogIn(in, out, systemIn, socket,true,true);
            
            menuReserva(in, out, systemIn, ans, socket);

            closingMenu(in, out, systemIn, socket);
            
            socket.shutdownOutput();
            socket.shutdownInput();
            socket.close();
            
        } catch(Exception e){
            e.printStackTrace();
        }
    }

}