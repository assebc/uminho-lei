package Model;

import java.io.Serializable;
import java.time.LocalDate;

public abstract class SmartDevice implements Serializable{

    public enum state {
        ON,
        OFF
    }

    private final double custoInstalacao = 2.5;
    private int id;
    private state estado;
    private double consumo;
    private LocalDate ligadoInit;
    private LocalDate dataFin;

    public SmartDevice(int id,state estado,double consumo,LocalDate ligadoInit,LocalDate dataFin){
        this.id = id;
        this.estado = estado;
        this.consumo = consumo;
        this.dataFin = dataFin;
        this.ligadoInit = ligadoInit;
    }

    public SmartDevice(int id,String estado,double consumo,LocalDate ligadoInit,LocalDate dataFin){
        this.id = id;
        this.estado = toState(estado);
        this.consumo = consumo;
        this.dataFin = dataFin;
        this.ligadoInit = ligadoInit;
    }

    /**
     * Converter uma string referente a um estado para um valor State
     * @param str_state Estado em formato string
     * @return estado
     */
    public state toState(String str_state){
        state ret = switch (str_state.toUpperCase()) {
            case ("ON") -> state.ON;
            case ("OFF") -> state.OFF;
            default -> state.OFF;
        };

        return ret;
    }

    /**
     * Getter do custo associado à instalação de um dispositivo
     * @return custo de instalação do dispositivo
     */
    public double getCustoInstalacao(){return this.custoInstalacao;}

    /**
     * Getter do id do dispositivo
     * @return id do dispositivo
     */
    public int getID(){return this.id;} //para definir nas subclasses

    /**
     * Getter de estado do device
     * @return estado do device
     */
    public state getEstado(){return this.estado;}

    /**
     * Getter da data de desligar
     * @return data de desligar o dispositivo
     */
    public LocalDate getDataFin(){return this.dataFin;}

    /**
     * Getter da data de ligar
     * @return data de ligar o dispositivo
     */
    public LocalDate getLigadoInit(){return this.ligadoInit; }

    /**
     * Getter de consumo
     * @return consumo
     */
    public double getConsumo(){return this.consumo;}

    /**
     * Getter de consumo em determinada cortina do cosnumo
     * @param data_atual data atual da simulação
     * @param data_sim data inicial da simulação
     * @return consumo dentro de determinado tempo
     */
    public abstract double getConsumo(LocalDate data_atual, LocalDate data_sim);

    
    /**
     * Setter da data de ativação
     * @param data data de ativação a definir
     */
    public void setLigadoInit(LocalDate data){this.ligadoInit=data;}

    /**
     * Setter da data de ativação
     * @param data data de ativação a definir
     */
    public void setDataFin(LocalDate data){this.dataFin=data;}

    /**
     * Setter do estado de uma lampada
     * @param est Estado a dar set
     */
    public void setEstado(state est){
        switch (est.toString()) {
            case ("ON") -> {
                this.ligadoInit = LocalDate.now();
                this.estado = est;
            }
            case ("OFF") -> {
                this.consumo = this.getConsumo();
                this.estado = est;
            }
        }
    }

    /**
     * Setter do consumo
     * @param c consumo
     */
    public void setConsumo(double c){this.consumo=c;}
    
    /**
     * Ligar dispositivo
     */
    public void turnOn(){
        this.setEstado(state.ON);
    }

    /**
     * Desligar dispositivo
     */
    public void turnOff(){
        this.setEstado(state.OFF);
    }

    /**
     * Clone de dispositvo
     * @return dispositivo clonado
     */
    public abstract SmartDevice clone();

    /**
     * toString de dispositivo
     * @return String com os componentes do dispositivo
     */
    public abstract String toString();

}
