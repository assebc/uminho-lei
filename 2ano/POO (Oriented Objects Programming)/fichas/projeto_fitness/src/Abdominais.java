//package src;

import java.time.LocalDateTime;
import java.lang.StringBuilder;

public class Abdominais{

    private String id;
    private String description;
    private LocalDateTime data_atividade;
    private Double duracao;
    private String tipo;
    private Integer reps;


    // init

    public Abdominais(){
        this.id = "";
        this.description = "";
        this.data_atividade = LocalDateTime.now();
        this.duracao = 0.0;
        this.tipo = "";
        this.reps = 0;
    }

    public Abdominais(Abdominais c){
        this.id = c.getId();
        this.description = c.getDescription();
        this.data_atividade = c.getData_Atividade();
        this.duracao = c.getDuracao();
        this.tipo = c.getTipo();
        this.reps = c.getReps();
    }

    public Abdominais(String id){
        this.id = id;
        this.description = "";
        this.data_atividade = LocalDateTime.now();
        this.duracao = 0.0;
        this.tipo = "";
        this.reps = 0;
    }

    public Abdominais(String id, String description, LocalDateTime data, double duracao, String tipo, int num){
        this.id = id;
        this.description = description;
        this.data_atividade = data;
        this.duracao = duracao;
        this.tipo = tipo;
        this.reps = num;
    }

    // setters

    public void setId(String id){ this.id = id; }
    public void setDescription(String description) { this.description = description; }
    public void setData_Atividade(LocalDateTime data) { this.data_atividade = data; }
    public void setDuracao(double duracao) { this.duracao = duracao; }
    public void setTipo(String tipo){ this.tipo = tipo; }
    public void setReps(int num){ this.reps = num; }

    // getters

    public String getId(){ return this.id; }
    public String getDescription(){ return this.description; }
    public LocalDateTime getData_Atividade(){ return this.data_atividade; }
    public double getDuracao(){ return this.duracao; }
    public String getTipo(){ return this.tipo; }
    public int getReps(){ return this.reps; }

    // equals, clone e toString

    public boolean equals(Object obj){
        if(this==obj) return true;
        if(obj==null||obj.getClass()!=this.getClass()) return false;
        Abdominais c = (Abdominais) obj;
        return (this.id == c.getId() && this.description == c.getDescription() &&
                this.data_atividade == c.getData_Atividade() && this.duracao == c.getDuracao() &&
                this.tipo == c.getTipo() && this.reps == c.getReps());
    }
    /*
    public Abdominais clone(){
        return new Abdominais(this);
    }
    */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Código dos abdominais: \n");
        sb.append(this.id);
        sb.append("Descrição dos abdominais: \n");
        sb.append(this.description);
        sb.append("Data de realização dos abdominais: \n");
        sb.append(this.data_atividade);
        sb.append("Duração dos abdominais: \n");
        sb.append(this.duracao);
        sb.append("Tipo de abdominais: \n");
        sb.append(this.tipo);
        sb.append("Número de repetições da abdominais: \n");
        sb.append(this.reps);
        return sb.toString();
    }

    public double caloriasAbdominais(){
        return ((this.duracao * this.reps)*0.6);
    }

}
