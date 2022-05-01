//package src;

import java.time.LocalDateTime;
import java.lang.StringBuilder;

public class Abdominais extends Atividade{
    private String tipo;
    private Integer reps;


    // init

    public Abdominais(){
        this.tipo = "";
        this.reps = 0;
    }

    public Abdominais(Abdominais c){
        this.tipo = c.getTipo();
        this.reps = c.getReps();
    }

    public Abdominais(String id){
        this.tipo = "";
        this.reps = 0;
    }

    public Abdominais(String id, String description, LocalDateTime data, double duracao, String tipo, int num){
        this.tipo = tipo;
        this.reps = num;
    }

    // setters

    public void setTipo(String tipo){ this.tipo = tipo; }
    public void setReps(int num){ this.reps = num; }

    // getters
    public String getTipo(){ return this.tipo; }
    public int getReps(){ return this.reps; }

    // equals, clone e toString

    public boolean equals(Object obj){
        if(this==obj) return true;
        if(obj==null||obj.getClass()!=this.getClass()) return false;
        Abdominais c = (Abdominais) obj;
        return (this.tipo == c.getTipo() && this.reps == c.getReps());
    }
    /*
    public Abdominais clone(){
        return new Abdominais(this);
    }
    */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Duração dos abdominais: \n");
        sb.append(this.duracao);
        sb.append("Tipo de abdominais: \n");
        sb.append(this.tipo);
        sb.append("Número de repetições da abdominais: \n");
        sb.append(this.reps);
        return sb.toString();
    }

}
