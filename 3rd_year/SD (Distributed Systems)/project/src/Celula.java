import java.util.concurrent.locks.ReentrantLock;

public class Celula {

    private int id;
    private int x;
    private int y;
    private Trotinete trotinete;
    private ReentrantLock lock;

    public Celula() {
        this.id = 0;
        this.x = 0;
        this.y = 0;
        this.trotinete = null;
        this.lock = new ReentrantLock();
    }

    public Celula(Celula c) {
        this.id = c.getId();
        this.x = c.getX();
        this.y = c.getY();
        this.trotinete = null;
        this.lock = new ReentrantLock();
    }

    public Celula(int id,int x,int y) {
        this.id = id;
        this.x = x;
        this.y = y;
        this.trotinete = null;
        this.lock = new ReentrantLock();
    }

    public void setCelula(int id, int x, int y) {
        this.id = id;
        this.x = x;
        this.y = y;
        this.trotinete = null;
    }

    public int getX() {
        return this.x;
    }

    public int getY() {
        return this.y;
    }

    public int getId() {
        return this.id;
    }

    @Override
    public boolean equals(Object obj) {
       Celula c = (Celula) obj;
       return (c==this) || ((c.getId() == this.getId()) && (c.getX()==this.getX()) && (c.getY() == this.getY()) && (c.getTrotinete().equals(this.getTrotinete())));
    }



    public Trotinete getTrotinete() {
        try{
            this.lock.lock();
            return this.trotinete;
        } finally{
            this.lock.unlock();
        }
    }

    public void setX(int x){
        this.x = x; 
    }

    public void setY(int y){
        this.y = y; 
    }

    public void setTrotinete(Trotinete t) {
        try{
            this.lock.lock();
            this.trotinete = t;
        } finally{
            this.lock.unlock();
        }
    }

    public void removeTrotinete(){
        try{
            this.lock.lock();
            this.trotinete = null;
        } finally{
            this.lock.unlock();
        }
    }

    public Boolean hasTrotinete(){
        try{
            this.lock.lock();
            return this.trotinete != null;
        } finally{
            this.lock.unlock();
        }
        
    }
}
