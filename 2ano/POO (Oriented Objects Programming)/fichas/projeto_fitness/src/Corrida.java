//package src;

import java.time.LocalDateTime;
import java.lang.StringBuilder;
public class Corrida extends Atividade{
    private Double distancia_percorrida;
    private Double altimetria;
    private String percurso;

    // init

    public Corrida(){
        this.distancia_percorrida = 0.0;
        this.altimetria = 0.0;
        this.percurso = "";
    }

    public Corrida(Corrida c){
        this.distancia_percorrida = c.getDistancia_Percorrida();
        this.altimetria = c.getAltimetria();
        this.percurso = c.getPercurso();
    }

    public Corrida(String id, String description, LocalDateTime data, double duracao, double distancia, double altimetria, String percurso){
        this.distancia_percorrida = distancia;
        this.altimetria = altimetria;
        this.percurso = percurso;
    }

    // setters
    public void setDistancia_Percorrida(double distancia){ this.distancia_percorrida = distancia; }
    public void setAltimetria(double altimetria){ this.altimetria = altimetria; }
    public void setPercurso(String percurso){ this.percurso = percurso; }

    // getters
    public double getDistancia_Percorrida(){ return this.distancia_percorrida; }
    public double getAltimetria(){ return this.altimetria; }
    public String getPercurso(){ return this.percurso; }

    // equals, clone e toString

    public boolean equals(Object obj){
        if(this==obj) return true;
        if(obj==null||obj.getClass()!=this.getClass()) return false;
        Corrida c = (Corrida) obj;
        return (this.distancia_percorrida == c.getDistancia_Percorrida() && this.altimetria == c.getAltimetria() &&
                this.percurso == c.getPercurso());
    }
    /*
    public Corrida clone(){
        return new Corrida(this);
    }
    */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Distância percorrida na corrida: \n");
        sb.append(this.distancia_percorrida);
        sb.append("Altimetria da corrida: \n");
        sb.append(this.altimetria);
        sb.append("Percurso da corrida: \n");
        sb.append(this.percurso);
        return sb.toString();
    }

}
