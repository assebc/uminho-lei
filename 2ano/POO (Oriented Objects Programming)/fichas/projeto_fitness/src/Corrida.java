//package src;

import java.time.LocalDateTime;
import java.lang.StringBuilder;
public class Corrida{

    private String id;
    private String description;
    private LocalDateTime data_atividade;
    private Double duracao;
    private Double distancia_percorrida;
    private Double altimetria;
    private String percurso;

    // init

    public Corrida(){
        this.id = "";
        this.description = "";
        this.data_atividade = LocalDateTime.now();
        this.duracao = 0.0;
        this.distancia_percorrida = 0.0;
        this.altimetria = 0.0;
        this.percurso = "";
    }

    public Corrida(Corrida c){
        this.id = c.getId();
        this.description = c.getDescription();
        this.data_atividade = c.getData_Atividade();
        this.duracao = c.getDuracao();
        this.distancia_percorrida = c.getDistancia_Percorrida();
        this.altimetria = c.getAltimetria();
        this.percurso = c.getPercurso();
    }

    public Corrida(String id){
        this.id = id;
        this.description = "";
        this.data_atividade = LocalDateTime.now();
        this.duracao = 0.0;
        this.distancia_percorrida = 0.0;
        this.altimetria = 0.0;
        this.percurso = "";
    }

    public Corrida(String id, String description, LocalDateTime data, double duracao, double distancia, double altimetria, String percurso){
        this.id = id;
        this.description = description;
        this.data_atividade = data;
        this.duracao = duracao;
        this.distancia_percorrida = distancia;
        this.altimetria = altimetria;
        this.percurso = percurso;
    }

    // setters

    public void setId(String id){ this.id = id; }
    public void setDescription(String description) { this.description = description; }
    public void setData_Atividade(LocalDateTime data) { this.data_atividade = data; }
    public void setDuracao(double duracao) { this.duracao = duracao; }
    public void setDistancia_Percorrida(double distancia){ this.distancia_percorrida = distancia; }
    public void setAltimetria(double altimetria){ this.altimetria = altimetria; }
    public void setPercurso(String percurso){ this.percurso = percurso; }

    // getters

    public String getId(){ return this.id; }
    public String getDescription(){ return this.description; }
    public LocalDateTime getData_Atividade(){ return this.data_atividade; }
    public double getDuracao(){ return this.duracao; }
    public double getDistancia_Percorrida(){ return this.distancia_percorrida; }
    public double getAltimetria(){ return this.altimetria; }
    public String getPercurso(){ return this.percurso; }

    // equals, clone e toString

    public boolean equals(Object obj){
        if(this==obj) return true;
        if(obj==null||obj.getClass()!=this.getClass()) return false;
        Corrida c = (Corrida) obj;
        return (this.id == c.getId() && this.description == c.getDescription() &&
                this.data_atividade == c.getData_Atividade() && this.duracao == c.getDuracao() &&
                this.distancia_percorrida == c.getDistancia_Percorrida() && this.altimetria == c.getAltimetria() &&
                this.percurso == c.getPercurso());
    }
    /*
    public Corrida clone(){
        return new Corrida(this);
    }
    */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Código da corrida: \n");
        sb.append(this.id);
        sb.append("Descrição da corrida: \n");
        sb.append(this.description);
        sb.append("Data de realização da corrida: \n");
        sb.append(this.data_atividade);
        sb.append("Duração da corrida: \n");
        sb.append(this.duracao);
        sb.append("Distância percorrida na corrida: \n");
        sb.append(this.distancia_percorrida);
        sb.append("Altimetria da corrida: \n");
        sb.append(this.altimetria);
        sb.append("Percurso da corrida: \n");
        sb.append(this.percurso);
        return sb.toString();
    }

    public double caloriasCorrida(double peso, int idade){
        return ((this.distancia_percorrida * peso * this.duracao * idade)/50);
    }

}
