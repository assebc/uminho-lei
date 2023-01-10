import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.locks.ReentrantLock;

public class Recompensa {

    //celula em que esta a trotinete, e a celula para onde e para ir 
    private Celula celula_inicial;
    private Celula celula_final;
    private ReentrantLock lock;

    public Recompensa(){
        this.celula_inicial = new Celula();
        this.celula_final = new Celula();
        this.lock = new ReentrantLock();
    }

    public Recompensa(Celula a, Celula b){
        this.celula_inicial = a;
        this.celula_final = b;
        this.lock = new ReentrantLock();
    }

    public Celula getPosInit(){
        try{
            this.lock.lock();
            return this.celula_inicial;
        } finally{
            this.lock.unlock();
        }  
    }

    public Celula getPosFinal(){
        try{
            this.lock.lock();
            return this.celula_final;
        } finally{
            this.lock.unlock();
        }  
    }

    @Override
    public String toString() {
        return "Recompensa de: (" + celula_inicial.getX() + "," + 
        celula_inicial.getY() +") -> (" + celula_final.getX() + 
        "," + celula_final.getY() +")";
    }

    @Override
    public boolean equals(Object obj) {
       Recompensa r = (Recompensa) obj;
       return (r==this) || (r.getPosInit().equals(this.getPosInit()) && r.getPosFinal().equals(this.getPosFinal()));
    }

    public void recompensaNearby(Mapa m) {
        int accum = 0 ;
        Celula t = new Celula();
        Celula new_t = new Celula();
        Map<Integer,Recompensa> recomp = new HashMap<>();
        int id = 1;
        try{
            this.lock.lock();
            for(int l = 0;l<20;l++){
                for(int c = 0;c<20;c++){
                    ArrayList<Celula> celulas_prox = new ArrayList<>(m.getNearbyCelulas(new Celula(0,l,c), 2));
                    for (Celula aux : celulas_prox) {
                        if (aux.hasTrotinete()){
                            t = aux;
                            accum++;
                        }
                    }
                    
                    if (accum >= 2) {
                        new_t = nextSpotTrotinete(m,t);
                        
                        Recompensa r = new Recompensa(t,new_t);
                        if(!recomp.values().contains(r)) {recomp.put(id,r); id++;}
                    }
                }
            }
            m.addRecompensa(new ArrayList<>(recomp.values()));
        } finally{
            this.lock.unlock();
        }   
    }

    private Celula nextSpotTrotinete(Mapa m, Celula c) {
        try{
            this.lock.lock();
            int x = c.getX();
            int y = c.getY();
            int opt = 1;
            if((x!=y) && m.getNearbyTrotinetes(m.getMap_positions()[y][x], 2).size()>=2) opt = 1;
            else if ((x<10 && y<10) && m.getNearbyTrotinetes(m.getMap_positions()[19][19], 2).size()>=2) opt = 2;
            else if ((x<10 && y>10) && m.getNearbyTrotinetes(m.getMap_positions()[19][0], 2).size()>=2) opt = 3;
            else if ((x>10 && y<10) && m.getNearbyTrotinetes(m.getMap_positions()[0][19], 2).size()>=2) opt = 4;
            else opt = 5;   

            return switchSpotTrotinete(m,x,y,opt);
            
        } finally{
            this.lock.unlock();
        } 
    }

    private Celula switchSpotTrotinete(Mapa m, Integer x, Integer y, Integer opt){
        Celula nov = new Celula();
        switch(opt){
            case 1:
                nov = m.getMap_positions()[x][y];
                break;
            case 2:
                nov = m.getMap_positions()[19][19];
                break;
            case 3:
                nov = m.getMap_positions()[19][0];
                break;
            case 4:
                nov = m.getMap_positions()[0][19];
                break;
            default:
                nov = m.getMap_positions()[0][0];
        }

        if(m.getNearbyTrotinetes(nov, 2).size()>=2){
            if(opt<=4) nov = switchSpotTrotinete(m, x, y, opt+1);
            else switchSpotTrotinete(m, x, y, 2);  
        }
        return nov;
    }
}
    

