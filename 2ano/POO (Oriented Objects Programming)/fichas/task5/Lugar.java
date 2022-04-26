package task5;

public class Lugar{

    private String matricula;
    private String nome;
    private int minutos;
    private boolean permanente;

    public Lugar(){
        this.matricula = "";
        this.nome = "";
        this.minutos = 0;
        this.permanente = true;
    }

    public Lugar(String matricula, String nome, int minutos, boolean permanente){
        this.matricula = matricula;
        this.nome = nome;
        this.minutos = minutos;
        this.permanente = permanente;
    }

    public Lugar(Lugar l){
        this.matricula = l.getMatricula();
        this.nome = l.getNome();
        this.minutos = l.getMinutos();
        this.permanente = l.getPermanente();
    }

    public void setMatricula(String matricula){ this.matricula = matricula; }
    public void setNome(String nome){ this.nome = nome; }
    public void setMinutos(int minutos){ this.minutos = minutos; }
    public void setPermanente(boolean permanente){ this.permanente = permanente; }

    public String getMatricula(){ return this.matricula; }
    public String getNome(){ return this.nome; }
    public int getMinutos(){ return this.minutos; }
    public boolean getPermanente(){ return this.permanente; }
    public Lugar getLugar(String matricula){ return this.clone();}

    public Lugar clone(){ return new Lugar(this); }

    public boolean equals(Object o){
        if(this==o) return true;
        if((o==null) || (o.getClass())!=this.getClass()) return false;

        Lugar l = (Lugar) o;
        return l.getMatricula() == this.getMatricula() &&
                l.getNome() == this.getNome() &&
                l.getMinutos() == this.getMinutos() &&
                l.getPermanente() == this.getPermanente();
    }

    public String toString(){
        final StringBuffer s = new StringBuffer("== Lugar ==\n");
        s.append("Matricula : ").append(this.matricula).append('\n');
        s.append("Nome : ").append(this.nome).append('\n');
        s.append("Minutos : ").append(this.minutos).append('\n');
        s.append("Permanente : ").append(this.permanente).append('\n');
        return s.toString();
    }

}