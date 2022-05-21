package Model;

import java.time.LocalDate;
import java.time.temporal.ChronoUnit;

/**
 * Um SmartSpeaker é um SmartDevice que além de ligar e desligar permite também ouvir estações de rádio
 * aumentando e descendo o volume.
 *
 * Obtém a estação atual
 * Obtém o volume
 * Pertence a uma dada marca
 * Consumo Energético
 *
 */

public class SmartSpeaker extends SmartDevice {
    private int volume;
    private String estacao;
    private Marca marca;

    /**
     * Inicializador de coluna
     * @param id id a definir
     * @param volume volume a definir
     * @param estacao estação a definir
     * @param marca marca a definir
     * @param consumo consumo a definir
     */
    public SmartSpeaker(int id,int volume, String estacao, Marca marca, double consumo) {
        super(id,state.OFF, consumo, LocalDate.now(), LocalDate.now());
        this.volume = volume;
        this.estacao = estacao;
        this.marca = marca;
    }

    /**
     * Inicializador de coluna
     * @param id id a definir
     * @param volume volume a definir
     * @param estacao estação a definir
     * @param estado estado a definir
     * @param marca marca a definir
     * @param consumo consumon a definir
     */
    public SmartSpeaker(int id,int volume, String estacao, String estado, Marca marca, double consumo) {
        super(id,estado, consumo, LocalDate.now(), LocalDate.now());
        this.volume = volume;
        this.estacao = estacao;
        this.marca = marca;
    }

    /**
     * Duplicador de coluna
     * @param speaker coluna a duplicar
     */
    public SmartSpeaker(SmartSpeaker speaker) {
        super(speaker.getID(),speaker.getEstado(), speaker.getConsumo(), speaker.getLigadoInit(), speaker.getDataFin());
        this.marca = speaker.getMarca();
        this.volume = speaker.getVolume();
        this.estacao = speaker.getEstacao();
    }

    /**
     * Getter da marca
     * @return marca
     */
    public Marca getMarca() {
        return this.marca;
    }

    /**
     * Setter da marca
     * @param marca marca a definir
     */
    public void setMarca(Marca marca) {
         this.marca = marca;
    }

    /**
     * Getter do volume
     * @return volume da coluna
     */
    public int getVolume() {
        return this.volume;
    }

    /**
     * Setter do volume da coluna
     * @param volume volume a definir
     */
    public void setVolume(int volume) {
        if((volume <= 20) && (volume >= 0)) this.volume = volume;
    }

    /**
     * Getter de estação
     * @return estação
     */
    public String getEstacao() {
        return this.estacao;
    }

    /**
     * Setter de estação
     * @param estacao estação a definir
     */
    public void setEstacao(String estacao) {
        this.estacao = estacao;
    }

    /**
     * Getter do consumo
     * @return consumo
     */
    @Override
    public double getConsumo() {
        double result;
        if (this.getEstado() == state.OFF) {
            result = 0;
        } else {
            result = this.marca.getConsumoDiario()+0.05*this.volume;
        }
        return result;
    }

    /**
     * Getter de consumo dentro de determinado periodo do tempo
     * @param data_atual Data atual
     * @param dataSimulacao data de inicial da cortina de tempo
     * @return consumo
     */
    public double getConsumo(LocalDate data_atual, LocalDate dataSimulacao){

        switch (this.getEstado().toString()) {
            case ("ON") ->
                    this.setConsumo((float)(ChronoUnit.DAYS.between(data_atual, dataSimulacao) * this.volume * this.marca.getConsumoDiario() * ((Math.random() * 2) + 1)));
            case ("OFF") -> this.setConsumo(0);
        }
        return this.getConsumo();
    }

    /**
     * Clone a coluna
     * @return coluna clonada
     */
    @Override
    public SmartDevice clone() {
        return new SmartSpeaker(this);
    }

    /**
     * Verificação entre duas colunas
     * @param obj objeto a verificar
     * @return boolean se objeto é a mesma coluna
     */
    public boolean equals(Object obj){
        if(this==obj)
            return true;

        if (obj==null||obj.getClass()!=this.getClass())
            return false;

        SmartSpeaker newC = (SmartSpeaker) obj;
        return (this.getID() == newC.getID() && this.volume == (newC.getVolume()) && this.estacao.equals(newC.getEstacao()) && this.getEstado().toString().equals(newC.getEstado().toString())
                &&  this.getConsumo() == (newC.getConsumo()));
    }

    /**
     * toString da coluna
     * @return String com as especificcações da coluna
     */
    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n[SmartSpeaker]");
        sb.append("\nID: ");
        sb.append(this.getID());
        sb.append("\nEstado: ");
        sb.append(this.getEstado());
        sb.append("\nEstação: ");
        sb.append(this.estacao);
        sb.append("\nVolume: ");
        sb.append(this.volume);
        sb.append("\n");

        return sb.toString();
    }

    /**
     * Aumentar o volume uma unidade
     */
    public void volumeUp(){
        if(this.volume < 20) this.setVolume(this.volume+1);
    }

    /**
     * Diminuir o volume uma unidade
     */
    public void volumeDown(){
        if(this.volume > 0) this.setVolume(this.volume-1);
    }
}   