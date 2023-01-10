import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.lang.Math;
import java.util.Random;
import java.util.Set;
import java.util.concurrent.locks.ReentrantLock;


public class Mapa {

    private ReentrantLock lock;
    final static String map_path = "maps/map_1.txt"; // path to one of the maps

    private Set<Trotinete> trotinetes; // indexed list of all of the trotinetezez (yezes) available in the map (index = trotinete's ID)
    private Set<Recompensa> recompensas;
    public Celula[][] map_positions; // indexed list of map positions (index = celula's ID)
    public int numTrotinetes;
    public int map_dimensions;

    public Mapa(int N, int quantidadeTrotinetes){
        this.trotinetes = new HashSet<>();
        this.recompensas = new HashSet<>();
        this.lock = new ReentrantLock();
        this.map_positions = new Celula[N][N];
        this.numTrotinetes = quantidadeTrotinetes;
        this.map_dimensions = N;

        generateMap();
        populateMap();
    }

    public void removeTrotinete(Celula c){
        try{
            this.lock.lock();
            this.map_positions[c.getX()][c.getY()].removeTrotinete();
        } finally{
            this.lock.unlock();
        }
        
    }

    public void addRecompensa(List<Recompensa> r){
        try{
            this.lock.lock();
            this.recompensas.clear();
            this.recompensas.addAll(r);
        } finally{
            this.lock.unlock();
        }
    }

    public void addRecompensa(Recompensa r){
        try{
            this.lock.lock();
            this.recompensas.add(r);
        } finally{
            this.lock.unlock();
        }
    }

    public void removeRecompensa(Recompensa r){
        try{
            this.lock.lock();
            this.recompensas.remove(r);
        } finally{
            this.lock.unlock();
        }
    }
    public Set<Recompensa> getRecompensas(){
        try{
            this.lock.lock();
            return this.recompensas;
        } finally{
            this.lock.unlock();
        }
    }

    public void addTrotinete(Celula c,Trotinete t){
        try{
            this.lock.lock();
            t.setDisponivel(true);
            this.map_positions[c.getX()][c.getY()].setTrotinete(t);
        } finally{
            this.lock.unlock();
        } 
    }

    public void addTrotineteRecompensas(){  
        for(Recompensa r:this.recompensas){
            this.map_positions[r.getPosInit().getY()][r.getPosInit().getX()].getTrotinete().setRecompensa(r);
        }
        for(Trotinete t: this.trotinetes){
            Recompensa aux = this.map_positions[t.getY()][t.getX()].getTrotinete().getRecompensa();
            if(aux!=null){
                t.setRecompensa(aux);
            }
        } 
    }

    public Map<Integer,Recompensa> checkRecompensas(Client c){
        Map<Integer,Recompensa> recompensas = new HashMap<>();
        int id = 1;
        //System.out.println(this.recompensas);
        for(Recompensa r: this.recompensas){
            if(dist_manhattan(c.getCelula(),r.getPosInit())<=2){
                recompensas.put(id,r);
                id++;
            }
        }
        return recompensas;
    }

    public String cod_reserva(){
        Random rand = new Random();
        String AlphaNumericString = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        StringBuilder sb = new StringBuilder(5);
        for(int i=0;i<5;i++){
            int index = rand.nextInt(AlphaNumericString.length());
            sb.append(AlphaNumericString.charAt(index));
        }
        return sb.toString();
    }

    public Set<Trotinete> getTrotinetes() {
        try{
            this.lock.lock();
            return this.trotinetes;
        } finally{
            this.lock.unlock();
        } 
    }

    public Celula[][] getMap_positions() {
        try{
            this.lock.lock();
            return this.map_positions;
        } finally{
            this.lock.unlock();
        }  
    }

    public Celula get_celula_position(int c, int l ) {
        return this.map_positions[l][c];

    }


    public void populateMap () {
        Random rand = new Random();

        for(int j = 0; j < this.numTrotinetes; j++){
            //random position x
            int c = rand.nextInt(this.map_dimensions); // coluna ... x
            //random position y
            int l = rand.nextInt(this.map_dimensions); // linha ... y 
            //verifica se existe trotinete nessa celula
            if(!(this.map_positions[l][c].hasTrotinete())){
                Trotinete t = new Trotinete(true, this.map_positions[l][c]);
                this.map_positions[l][c].setTrotinete(t);
                this.trotinetes.add(t);
            }
        }
    }

    public void generateMap () {
        int i = 0;
        for(int l = 0; l < this.map_dimensions; l++ ){
            for(int c = 0; c < this.map_dimensions; c++){
                //cria célula com índice i e posições x,y
                Celula cel1 = new Celula(i,c,l);
                this.map_positions[l][c] = cel1;
                i++;
            }
        }

    }

    public void printMap () {
        try{
            this.lock.lock();
            for(int y = 0; y < this.map_dimensions; y++ ){
                for(int x = 0; x < this.map_dimensions; x++){
                    Celula c = this.map_positions[y][x];
                    if(c.hasTrotinete()){
                        System.out.print("T");
                    }
                    else{
                        System.out.print("-");
                    }
                    System.out.print(" ");
                }
                System.out.print("\n");
            }
        } finally{
            this.lock.unlock();
        }
        
    }

    public Integer dist_manhattan (Celula c1, Celula c2) { //|x1 – x2| + |y1 – y2|.
        return Math.abs(c1.getX()-c2.getX())+Math.abs(c1.getY()-c2.getY());
    }
    

    @Override
    public String toString() {
        return "Map{" +
                "trotinetes=" + trotinetes +
                ", map_positions=" + map_positions +
                '}';
    }

    public Boolean isInRange(Celula origem, Trotinete destino, int raio) {
        try{
            this.lock.lock();
            Celula dest = new Celula(0, destino.getX(), destino.getY());
            return dist_manhattan(origem, dest) <= raio;
        } finally{
            this.lock.unlock();
        }
        
    }

    public Boolean isInRange(Celula origem, Celula destino, int raio) {
        try{
            this.lock.lock();
            return dist_manhattan(origem, destino) <= raio;
        } finally{
            this.lock.unlock();
        }
        
    }

    public Boolean insertInRange(Celula c,Trotinete t){
        try{
            this.lock.lock();
            Set<Trotinete> nearby = new  HashSet<>(getNearbyTrotinetes(c, 1));
            if(nearby.size() == 9) return false;
            else{
                for(Celula near:getNearbyCelulas(c, 1)){
                    if(near.getTrotinete().equals(null)){
                        addTrotinete(near, t);
                        break;
                    }
                }
            }
            return true;
        } finally{
            this.lock.unlock();
        }
    }

    public Set<Trotinete> getNearbyTrotinetes(Celula c, int raio) {
        //para uma dada posição verifica as que se encontram num dado raio, colocando-as numa lista
        try{
            this.lock.lock();
            Set<Trotinete> nearby = new HashSet<>();
            for (Trotinete t : this.trotinetes) {
                if (isInRange(c, t, raio)) {
                    nearby.add(t);
                }
            }
            return nearby;
        } finally{
            this.lock.unlock();
        }
        
    }

    public List<Celula> getNearbyCelulas(Celula c, int raio) {
        //para uma dada posição verifica as que se encontram num dado raio, colocando-as numa lista
        try{
            this.lock.lock();
            List<Celula> nearby = new ArrayList<>();
            for (int i = 0; i<this.map_dimensions;i++) {
                for (int j = 0; j<this.map_dimensions;j++) {
                    if (isInRange(c, this.map_positions[i][j], raio)) {
                        nearby.add(this.map_positions[i][j]);
                    }
                }
            }
            return nearby;
        } finally{
            this.lock.unlock();
        }
        
    }
}