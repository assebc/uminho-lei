import java.lang.Boolean;

public class Trotinete extends Celula{

    private Boolean disponivel; // 1 se estiver, 0 se não estiver
    private Recompensa recompensa;

    public Trotinete() {
        super();
        this.disponivel = true;
        this.recompensa = null;
    }

    public Trotinete(Boolean disponivel,Celula c) {
        super(c);
        this.disponivel = disponivel;
        this.recompensa = null;
    }

    public void setTrotinete(Boolean disponivel) {
        this.disponivel = disponivel;
    }

    public void setDisponivel(Boolean disponivel) {
        this.disponivel = disponivel;
    }
    
    public Boolean getDisponivel() {
        return disponivel;
    }

    public void setRecompensa(Recompensa recompensa) {
        this.recompensa = recompensa;
    }

    public Recompensa getRecompensa () {
        return this.recompensa;
    }

    public int getX() {
        return super.getX();
    }
    
    public int getY(){
        return super.getY();
    }

    public void setX(int x){
        super.setX(x);
    }

    public void setY(int y){
        super.setX(y);
    }

    @Override
    public String toString() {
        return "Trotinete{" +
                "posição=" +
                "(" + super.getX() + "," + super.getY() + ")" +
                "," +
                "disponivel=" + this.disponivel + " " +
                this.recompensa +
                '}';
    }

    @Override
    public boolean equals(Object obj) {
        Trotinete t = (Trotinete) obj;
        return (t==this) || ((t.getDisponivel() == this.getDisponivel()) && t.getRecompensa().equals(this.getRecompensa()));
    }
}
