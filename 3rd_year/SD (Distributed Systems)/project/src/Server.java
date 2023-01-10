import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.time.LocalTime;
import java.time.temporal.ChronoUnit;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.locks.ReentrantLock;
import java.util.ArrayList;
import java.util.HashMap;

class ServerWorker implements Runnable{

    private Map<String,Client> clientes; 
    private Socket socket;
    private Mapa mapa;
    private ReentrantLock lock;

    public ServerWorker(Socket socket,Mapa mapa, Map<String, Client> clientes){
        this.socket = socket;
        this.clientes = clientes;
        this.mapa = mapa;
        this.lock = new ReentrantLock();
    }
    
    public void putCliente(Map<String,Client> plus){
        try{
            this.lock.lock();
            this.clientes.putAll(plus);
        } finally{
            this.lock.unlock();
        }
    }

    public Map<String,Client> getClientes(){
        try{
            this.lock.lock();
            return this.clientes;
        } finally{
            this.lock.unlock();
        }
    }

    public void setMapa(Mapa mapa) {
        this.mapa = mapa;
    }

    public Mapa getMapa() {
        return this.mapa;
    }

    // Run auxiliar methods

    private String register(String register){
        try{
            this.lock.lock();
            String [] acc = register.split(";");
            Client cl = new Client(acc[0],acc[1]);
            if(this.clientes.containsKey(cl.getUserName())){
                Client ver = this.clientes.get(cl.getUserName());
                if(ver.getPassword().equals(cl.getPassword())) return "false";
                else return "pass";
            }
            else this.clientes.put(cl.getUserName(), cl);
            return "true";
        } finally{
            this.lock.unlock();
        }
    }

    private void main_menu(PrintWriter out){
        out.println("Bem vindo a Troti-NET!\n");
        out.flush();
        out.println("Escolha uma das opções:");
        out.flush();
        out.println("1 - Log In");
        out.flush();
        out.println("2 - Registo");
        out.flush();
        out.println("3 - Sair");
        out.flush();
    }

    private Client startUser(BufferedReader in, PrintWriter out, Integer option) throws IOException{
        Client client = null;
        String read = new String();
        switch(option){
            case 1: case 2:
                out.println("Insira o nome de utilizador e a palavra-passe, da seguinte forma: user password");
                out.flush();
                read = new String(in.readLine());
                String ver_reg = register(read);
                if(ver_reg.equals("true")){ out.println("Registado e logado com sucesso!"); System.out.println("Novo utilizador com o username: " + read.split(";")[0]);}
                else if(ver_reg.equals("false")){ out.println("Já possui uma conta, por isso, foi logado automaticamente!"); System.out.println("O utilizador com o username: " + read.split(";")[0] + " fez login novamente");}
                else{
                    while(ver_reg.equals("pass")){
                        out.println("Palavra-passe errada ou esse nome de utilizador já está a ser utilizado!");
                        out.flush();
                        out.println("Insira um novo nome de utilizador ou tente novamente, da seguinte forma: user password");
                        out.flush();
                        read = new String(in.readLine());
                        ver_reg = register(read);
                    }
                    out.println("Foi logado com sucesso!");
                    System.out.println("O utilizador com o username: " + read.split(";")[0] + " fez login novamente");
                }
                out.flush();
                String [] user = read.split(";");
                client = new Client(user[0],user[1]);
                break;

            case 3:
                out.println("Adeus, espero voltar a vê-lo em breve!\n");
                out.flush();
                socket.close();
                break;
        }
        return client;
    }

    private String positionUser(BufferedReader in, PrintWriter out) throws IOException{
        out.println("Bem vindo à Troti-Net!");
        out.flush();
        out.println("Indique onde se encontra, da seguinte forma -> x y");
        out.flush();
        return new String(in.readLine());
    } 

    private Integer menuReserva(BufferedReader in, PrintWriter out, String username) throws NumberFormatException, IOException{
        out.println("Bem vindo à Troti-Net!");
        out.flush(); 
        out.println("Escolha uma das opções:");
        out.flush();
        out.println("1 - Reservar trotinete");
        out.flush();
        if(this.clientes.get(username).hasNotifications()){ 
            out.println("2 - Desligar as notificações de recompensas"); 
            out.flush();  
            out.println("3 - Efetuar uma recompensa");
            out.flush(); 
            out.println("4 - Sair");
            out.flush();
        } else{
            out.println("2 - Ligar as notificações de recompensas"); 
            out.flush();
            out.println("3 - Sair");
            out.flush();
        }
        return Integer.parseInt(in.readLine());
    }
    
    private void custoViagem(BufferedReader in, PrintWriter out, Integer old_x, Integer old_y, Integer x, Integer y, Long diff, String username) throws IOException{
        Integer distancia = this.mapa.dist_manhattan(this.mapa.map_positions[old_x][old_y], this.mapa.map_positions[x][y]);
        Float preco_mult = (float) (distancia * diff) / 60;
        out.println("O preço da sua viagem foi de " + preco_mult + "€");
        out.flush();
        if(this.clientes.get(username).getCoupons()>0) {
            out.println("Possui, neste momento, " + this.clientes.get(username).getCoupons() + " coupons, pretende utilizar? (S/N)");
            out.flush();
            if(in.readLine().equals("S")){
                try{
                    this.lock.lock();
                    this.clientes.get(username).removeCoupon();
                } finally{
                    this.lock.unlock();
                }
                out.println("Foi utilizado 1 coupon, a viagem não terá um custo, tem neste momento " + this.clientes.get(username).getCoupons() + " coupons!");
                out.flush();
            } else{
                out.println("Será lhe debitado um total de " + preco_mult + "€");
                out.flush();
            }
        } else{
            out.println("Não possui coupons para utilizar!");
            out.flush();
        }          
    }

    private void giveRecompensa(PrintWriter out, String username, Recompensa r){
        if (this.mapa.dist_manhattan(r.getPosInit(), r.getPosFinal())<=10){
            out.println("Foi lhe creditado uma viagem gratuita!");
            out.flush();
            this.clientes.get(username).addCoupon();
        } else if(this.mapa.dist_manhattan(r.getPosInit(), r.getPosFinal())<=20){
            out.println("Foi lhe creditado duas viagens gratuitas!");
            out.flush();
            this.clientes.get(username).addCoupon();
            this.clientes.get(username).addCoupon();
        } else if(this.mapa.dist_manhattan(r.getPosInit(), r.getPosFinal())<=30){
            out.println("Foi lhe creditado três viagens gratuitas!");
            out.flush();
            this.clientes.get(username).addCoupon();
            this.clientes.get(username).addCoupon();
            this.clientes.get(username).addCoupon();
        } else{
            out.println("Foi lhe creditado quatro viagens gratuitas!");
            out.flush();
            this.clientes.get(username).addCoupon();
            this.clientes.get(username).addCoupon();
            this.clientes.get(username).addCoupon();
            this.clientes.get(username).addCoupon();
        }
    }
    private void moveTrotinete(BufferedReader in, PrintWriter out, Integer id_trotinete, Map<Integer,Trotinete> trotinetes, String username) throws IOException{
        if(trotinetes.containsKey(id_trotinete)){
            Trotinete t = trotinetes.get(id_trotinete);
            t.setDisponivel(false);
            this.mapa.removeTrotinete(this.mapa.getMap_positions()[t.getX()][t.getY()]);
            this.mapa.printMap();
            System.out.println("=============================");
            out.println("Trotinete " + id_trotinete + " reservada com sucesso!");
            out.flush();
            out.println("Código da reserva: " + this.mapa.cod_reserva());
            out.flush();
            LocalTime time_reserve = LocalTime.now();
            out.println("Indique o seu destino, da seguinte forma -> x y");
            out.flush();
            int old_x = t.getX();
            int old_y = t.getY();
            String[] user_coord = new String(in.readLine()).split(" ");
            int x = Integer.parseInt(user_coord[0]);
            int y = Integer.parseInt(user_coord[1]);
            t.setDisponivel(true);
            t.setX(x);
            t.setY(y);
            //System.out.println(t.toString());
            if(this.mapa.getMap_positions()[x][y].hasTrotinete()){
                // insert into other coord in a radius of 1
                if(this.mapa.insertInRange(this.mapa.getMap_positions()[x][y], t)){
                    out.println("Trotinete entregue e pronta para ser reutilizada!");
                    out.flush();
                    this.mapa.printMap();
                } else{
                    out.println("Este sítio encontra-se lotado!");
                    out.flush();
                }
            } else{
                this.mapa.addTrotinete(this.mapa.getMap_positions()[x][y], t);
                out.println("Trotinete entregue e pronta para ser reutilizada!");
                out.flush();
                if(t.getRecompensa()!=null){
                    giveRecompensa(out,username,t.getRecompensa()); 
                    Set<Recompensa> rec = this.mapa.getRecompensas();
                    rec.remove(t.getRecompensa());
                    this.mapa.addRecompensa(new ArrayList<>(rec));
                    t.setRecompensa(null);
                    trotinetes.get(id_trotinete).setRecompensa(null);
                    new Recompensa().recompensaNearby(this.mapa);
                    mapa.addTrotineteRecompensas();
                } else{
                    out.println("");
                    out.flush();
                }
                this.mapa.printMap();
            }
            LocalTime time_entrega = LocalTime.now();
            Long diff = time_reserve.until(time_entrega, ChronoUnit.SECONDS);
            custoViagem(in,out,old_x,old_y,x,y,diff,username);    
        }
    }

    private void selecioneTrotinete(BufferedReader in, PrintWriter out, String username) throws IOException{
        out.println("Reserve uma trotine em Troti-Net!");
        out.flush();
        out.println("Selecione uma das trotines disponíveis:");
        out.flush();
        Map<Integer,Trotinete> trotinetes = new HashMap<>();

        int x = this.clientes.get(username).getY();
        int y = this.clientes.get(username).getX();
        try{
            this.lock.lock();
            if(this.mapa.getNearbyTrotinetes(this.mapa.getMap_positions()[x][y],2).isEmpty()){
                out.println("Não existem trotinetes nas suas redondezas!");
                out.flush();
                socket.close();
            } else{
                int id = 1;
                for(Trotinete t:this.mapa.getNearbyTrotinetes(this.mapa.getMap_positions()[x][y], 2)) {
                    trotinetes.put(id,t);
                    id++;
                }
                out.println(trotinetes.toString());
                out.flush();
                Integer id_trotinete = Integer.parseInt(new String(in.readLine()));
                moveTrotinete(in, out, id_trotinete, trotinetes , username);
            } 
        } finally{
            this.lock.unlock();
        }
    }

    private void notifications(BufferedReader in, PrintWriter out, String username) throws NumberFormatException, IOException{
        Integer opt = 0;
        try{
            this.lock.lock();
            if(this.clientes.get(username).hasNotifications()){
                this.clientes.get(username).deactivateNotifications();
            } else this.clientes.get(username).activateNotifications();
            opt = menuReserva(in, out, username);
        } finally{
            this.lock.unlock();
        }
        reserveTrotine(in, out, opt, username);
    }

    private void recompensas(BufferedReader in, PrintWriter out, String username) throws NumberFormatException, IOException{
        try{
            this.lock.lock();
            
            Map<Integer,Recompensa> recompensas = this.mapa.checkRecompensas(this.clientes.get(username));
            if(recompensas.isEmpty()){
                out.println("Não existem recompensas onde se encontra!"); 
                out.flush();
            } else {
                out.println(recompensas.toString());
                out.flush();
                Integer opts = Integer.parseInt(in.readLine());
                out.println("Recorde-se que a sua trotinete está em (" + recompensas.get(opts).getPosInit().getX() +","+ recompensas.get(opts).getPosInit().getY()+")");
                out.flush();
            }
            Integer user_option = menuReserva(in,out, username);
            reserveTrotine(in,out,user_option,username);
        } finally{
            this.lock.unlock();
        }
    }
    
    private void byebye(PrintWriter out) throws IOException{
        out.println("Adeus, espero voltar a vê-lo em breve!\n");
        out.flush();
        socket.close();
    }


    private void reserveTrotine(BufferedReader in, PrintWriter out, Integer option, String username) throws IOException{
        if(this.clientes.get(username).hasNotifications()){
            switch(option){
                case 1:
                    selecioneTrotinete(in, out, username);
                    break;
                case 2:
                    notifications(in, out, username);
                    break;
                
                case 3:
                    recompensas(in,out,username);
                    break;
                    
                case 4:
                    byebye(out);
                    break;
            }
        } else{
            switch(option){
                case 1:
                    selecioneTrotinete(in, out, username);
                    break;
                case 2:
                    notifications(in, out, username);
                    break;
                case 3:
                    byebye(out);
                    break;
            }
        }
    }

    // End of auxiliar methods of run
    
    @Override
    public void run(){
        
        try{
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream());
            
            main_menu(out);

            Integer option = Integer.parseInt(in.readLine());
            Client c = startUser(in, out, option);

            try{
                this.lock.lock();
                clientes.put(c.getUserName(),c);
            } finally{
                this.lock.unlock();
            }
            
            // user is well registed and logged in
            String[] coord = positionUser(in,out).split(" ");
            try{
                this.lock.lock();
                this.clientes.get(c.getUserName()).setX(Integer.parseInt(coord[0]));
                this.clientes.get(c.getUserName()).setY(Integer.parseInt(coord[1]));
            } finally{
                this.lock.unlock();
            }

            Integer user_option = menuReserva(in,out, c.getUserName());
            reserveTrotine(in,out,user_option,c.getUserName());

            socket.close();
        } catch(IOException e){
            System.out.println(e);
        } 
    }
}

public class Server{

    private static void clearScreen(){
        System.out.print("\033[H\033[2J");  
        System.out.flush(); 
    }

    public static void main(String[] args) throws Exception {
        try {
            clearScreen();
            Mapa mapa = new Mapa(20,20);
            Map<String,Client> clientes = new HashMap<>();
            new Recompensa().recompensaNearby(mapa);
            mapa.addTrotineteRecompensas();
            System.out.println("==== SERVER ONLINE ====");
            mapa.printMap();
            System.out.println("=======================");

            ServerSocket ss = new ServerSocket(12345);
            ServerWorker sw;
            Map<String,Client> aux = new HashMap<>();
            while(true){
                Socket socket = ss.accept();
                sw = new ServerWorker(socket,mapa,clientes);
                sw.putCliente(aux);
                Thread worker = new Thread(sw);
                worker.start();
                worker.join();
                aux.putAll(sw.getClientes());
                mapa = sw.getMapa();
                clientes = sw.getClientes();
            } 
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}