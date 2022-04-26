//package src;

import java.time.LocalDateTime;
import java.lang.StringBuilder;

public class Canoagem{

    private String id;
    private String description;
    private LocalDateTime data_atividade;
    private Double duracao;
    private Double distancia_percorrida;
    private String embarcacao;
    private Double vel_vento; // km/h
    private enum pontos_c{
        Norte,
        Sul,
        Este,
        Oeste
    }
    private pontos_c direcao;
    private Integer n_voltas;


    // init

    public Canoagem(){
        this.id = "";
        this.description = "";
        this.data_atividade = LocalDateTime.now();
        this.duracao = 0.0;
        this.distancia_percorrida = 0.0;
        this.embarcacao = "";
        this.vel_vento = 0.0;
        this.direcao = pontos_c.Norte;
        this.n_voltas = 0;
    }

    public Canoagem(Canoagem c){
        this.id = c.getId();
        this.description = c.getDescription();
        this.data_atividade = c.getData_Atividade();
        this.duracao = c.getDuracao();
        this.distancia_percorrida = c.getDistancia_Percorrida();
        this.embarcacao = c.getEmbarcacao();
        this.vel_vento = c.getVel_Vento();
        this.direcao = c.getDirecao();
        this.n_voltas = c.getN_Voltas();
    }

    public Canoagem(String id){
        this.id = id;
        this.description = "";
        this.data_atividade = LocalDateTime.now();
        this.duracao = 0.0;
        this.distancia_percorrida = 0.0;
        this.embarcacao = "";
        this.vel_vento = 0.0;
        this.direcao = pontos_c.Norte;
        this.n_voltas = 0;
    }

    public Canoagem(String id, String description, LocalDateTime data, double duracao, double distancia, String embarcacao, double vel, pontos_c c, int num){
        this.id = id;
        this.description = description;
        this.data_atividade = data;
        this.duracao = duracao;
        this.distancia_percorrida = distancia;
        this.embarcacao = embarcacao;
        this.vel_vento = vel;
        this.direcao = c;
        this.n_voltas = num;
    }

    // setters

    public void setId(String id){ this.id = id; }
    public void setDescription(String description) { this.description = description; }
    public void setData_Atividade(LocalDateTime data) { this.data_atividade = data; }
    public void setDuracao(double duracao) { this.duracao = duracao; }
    public void setDistancia_Percorrida(double distancia){ this.distancia_percorrida = distancia; }
    public void setEmbarcacao(String embarcacao){ this.embarcacao = embarcacao; }
    public void setVel_Vento(double vel){ this.vel_vento = vel; }
    public void setDirecao(pontos_c c){ this.direcao = c; }
    public void setN_Voltas(int num){ this.n_voltas = num; }

    // getters

    public String getId(){ return this.id; }
    public String getDescription(){ return this.description; }
    public LocalDateTime getData_Atividade(){ return this.data_atividade; }
    public double getDuracao(){ return this.duracao; }
    public double getDistancia_Percorrida(){ return this.distancia_percorrida; }
    public String getEmbarcacao(){ return this.embarcacao; }
    public double getVel_Vento(){ return this.vel_vento; }
    public pontos_c getDirecao(){ return this.direcao; }
    public int getN_Voltas(){ return this.n_voltas; }

    // equals, clone e toString

    public boolean equals(Object obj){
        if(this==obj) return true;
        if(obj==null||obj.getClass()!=this.getClass()) return false;
        Canoagem c = (Canoagem) obj;
        return (this.id == c.getId() && this.description == c.getDescription() &&
                this.data_atividade == c.getData_Atividade() && this.duracao == c.getDuracao() &&
                this.distancia_percorrida == c.getDistancia_Percorrida() && this.embarcacao == c.getEmbarcacao() &&
                this.vel_vento == c.getVel_Vento() && this.direcao == c.getDirecao() &&
                this.n_voltas == c.getN_Voltas());
    }
    /*
    public Canoagem clone(){
        return new Canoagem(this);
    }
    */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Código da canoagem: \n");
        sb.append(this.id);
        sb.append("Descrição da canoagem: \n");
        sb.append(this.description);
        sb.append("Data de realização da canoagem: \n");
        sb.append(this.data_atividade);
        sb.append("Duração da canoagem: \n");
        sb.append(this.duracao);
        sb.append("Distância percorrida na canoagem: \n");
        sb.append(this.distancia_percorrida);
        sb.append("Tipo de embarcação da canoagem: \n");
        sb.append(this.embarcacao);
        sb.append("Velocidade do vento na canoagem: \n");
        sb.append(this.vel_vento);
        sb.append("Direcao da canoagem: \n");
        sb.append(this.direcao);
        sb.append("Número de voltas da canoagem: \n");
        sb.append(this.n_voltas);
        return sb.toString();
    }

    public double caloriasCanoagem(int idade){
        return ((this.distancia_percorrida * this.vel_vento * this.duracao * idade)/4);
    }

}