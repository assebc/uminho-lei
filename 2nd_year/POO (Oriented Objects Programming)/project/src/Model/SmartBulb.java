package Model;

import java.lang.StringBuilder;
import java.time.LocalDate;
import java.time.temporal.ChronoUnit;

/**
 * Uma SmartBulb é uma lâmpada inteligente que além de ligar e desligar (já que
 * é subclasse de SmartDevice) também permite escolher a intensidade da iluminação
 * (a cor da mesma).
 *
 */
public class SmartBulb extends SmartDevice {
    
    private enum modo{
        COLD,
        NEUTRAL,
        WARM
    }

    private modo mode;
    private int dimensions;

    /**
     * Inicializador de lampada
     * @param id id a definir
     */
    public SmartBulb(int id) {
        super(id, state.OFF, 0, LocalDate.now(), LocalDate.now());
        this.mode=modo.NEUTRAL;
        this.dimensions=1;
    }

    /**
     * Inicializador de lampada
     * @param id id a definir
     * @param estado estado a definir
     */
    public SmartBulb(int id,state estado) {
        super(id, estado, 0, LocalDate.now(), LocalDate.now());
        this.mode=modo.NEUTRAL;
        this.dimensions=1;
    }

    /**
     * Inicializador de lampada
     * @param id id a definir
     * @param mode modo a definir
     * @param dimensions dimensões a definir
     * @param consumo consumo a definir
     */
    public SmartBulb(int id, modo mode,int dimensions, double consumo) {
        super(id, state.OFF, consumo, LocalDate.now(), LocalDate.now());
        this.mode = mode;
        this.dimensions=dimensions;
    }

    /**
     * Inicializador de lampada
     * @param id id a definir
     * @param mode modo a definir
     * @param dimensions dimensões a definir
     * @param consumo consumo a definir
     */
    public SmartBulb(int id, String mode,int dimensions, double consumo) {
        super(id, state.OFF, consumo, LocalDate.now(), LocalDate.now());

        modo modos = switch (mode.toUpperCase()) {
            case "COLD" -> modo.COLD;
            case "NEUTRAL" -> modo.NEUTRAL;
            case "WARM" -> modo.WARM;
            default -> modo.NEUTRAL;
        };

        this.mode = modos;
        this.dimensions=dimensions;
    }

    /**
     * Inicializador da lampada
     * @param id id a definir
     * @param mode modo a definir
     * @param dimensions dimensões a definir
     * @param consumo consumo a definir
     * @param estado estado a definir
     */
    public SmartBulb(int id, String mode,int dimensions, double consumo, String estado) {
        super(id, estado, consumo, LocalDate.now(), LocalDate.now());

        modo modos = switch (mode.toUpperCase()) {
            case "COLD" -> modo.COLD;
            case "NEUTRAL" -> modo.NEUTRAL;
            case "WARM" -> modo.WARM;
            default -> modo.NEUTRAL;
        };

        this.mode = modos;
        this.dimensions=dimensions;
    }

    /**
     * Inicializador de lampada
     * @param id id a definir
     * @param mode modo a definir
     * @param estado estado a definir
     * @param consumo consumo a definir
     * @param dimensions dimensões a definir
     * @param ligadoInit data de ativar a lampada a definir
     */
    public SmartBulb(int id, modo mode, state estado, double consumo, int dimensions, LocalDate ligadoInit) {
        super(id, estado, consumo, ligadoInit, LocalDate.now());
        this.mode = mode;
        this.dimensions=dimensions;
    }

    /**
     * Inicializar lampada
     * @param id id a definir
     * @param mode modo a definir
     * @param estado estado a definir
     * @param consumo consumo a definir
     * @param dimensions dimensões a definir
     * @param ligadoInit ativação a definir
     * @param dataFinal data de desligar a definir
     */
    public SmartBulb(int id, modo mode, state estado, double consumo, int dimensions, LocalDate ligadoInit, LocalDate dataFinal) {
        super(id, estado, consumo, ligadoInit, dataFinal);
        this.mode = mode;
        this.dimensions=dimensions;
    }

    /**
     * Duplicar lampada
     * @param sb Lampada a duplicar
     */
    public SmartBulb(SmartBulb sb) {
        super(sb.getID(), sb.getEstado(), sb.getConsumo(), sb.getLigadoInit(), sb.getDataFin());
        this.mode = sb.getMode();
        this.dimensions= sb.getDimensions();
    }

    /**
     * Getter do modo da lampada
     * @return modo da lampada
     */
    public modo getMode(){return this.mode;}

    /**
     * Setter do modo da lampada
     * @param mode modo a definar a lampada
     */
    public void setMode(modo mode){this.mode = mode;}

    /**
     * Setter de dimensões
     * @param dimensions dimensões a dar set
     */
    public void setDimensions(int dimensions){this.dimensions=dimensions;}

    /**
     * Getter de dimensões
     * @return dimensões
     */
    public int getDimensions(){return this.dimensions;}

    /**
     * Setter de consumo
     * @param con consumo a definir
     */
    public void setConsumo(float con){
        this.setConsumo(con);
    }

    /**
     * Getter de consumo
     * @return consumo
     */
    public double getConsumo() {
        if (this.getEstado() == state.ON){
            switch(this.mode.toString().toUpperCase()){
                case("WARM"):
                    return 10+0.7;
                case("NEUTRAL"):
                    return 10+0.2;
                case("COLD"):
                    return 10+0.5;
            }
        }
        return 0;
    }

    /**
     * Calcula o consumo da lampada
     * @param data_atual data que foi desligada a lampada
     * @param dataSimulacao data que foi ligada a lampada
     * @return consumo da lampada
     */
    public double getConsumo(LocalDate data_atual, LocalDate dataSimulacao){
        switch (this.getEstado().toString()) {
            case ("ON") ->
                    this.setConsumo((float)(ChronoUnit.DAYS.between(data_atual, dataSimulacao) * this.dimensions * Math.random()));
            case ("OFF") -> this.setConsumo(0);
        }
        return this.getConsumo();
    }


    /*
    public double getConsumo(LocalDate data_atual, LocalDate dataSimulacao){

        switch(this.estado.toString()){
            case("ON"):
                if(this.ligadoInit.isBefore(data_atual) && this.dataFin.isAfter(dataSimulacao)){
                    this.consumo = ChronoUnit.DAYS.between(data_atual, dataSimulacao)*this.dimensions*Math.random();
                }
                else if(this.ligadoInit.isBefore(data_atual) && this.dataFin.isBefore(dataSimulacao)){
                    this.consumo = ChronoUnit.DAYS.between(data_atual, this.dataFin)*this.dimensions*Math.random();
                }
                else if(this.ligadoInit.isAfter(data_atual) && this.dataFin.isAfter(dataSimulacao)){
                    this.consumo = ChronoUnit.DAYS.between(this.ligadoInit, dataSimulacao)*this.dimensions*Math.random();
                }
                else{ this.consumo = 0;}

            case("OFF"):
                this.consumo = ChronoUnit.DAYS.between(this.ligadoInit, this.dataFin)*this.dimensions*Math.random();
                this.estado = est;
        }
        return this.consumo;
    }*/

    /**
     * Compara a lampada a um objeto
     * @param obj objeto
     * @return Bool de validação da comparação entre objetos
     */
    public boolean equals(Object obj){
        if (this==obj)
            return true;

        if (this.getClass()!=obj.getClass() || obj==null)
            return false;

        SmartBulb lampada = (SmartBulb) obj;
        return (this.getID() == lampada.getID() && this.mode==lampada.getMode() && this.getEstado()==lampada.getEstado() &&
                this.dimensions==lampada.getDimensions() &&
                this.getLigadoInit().equals(lampada.getLigadoInit()));
    }

    /**
     * toString de uma lampada
     * @return String com todos os dados de uma lampada
     */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n[SmartBulb]");
        sb.append("\nID: ");
        sb.append(this.getID());
        sb.append("\nEstado: ");
        sb.append(this.getEstado());
        sb.append("\nModo: ");
        sb.append(this.mode);
        //sb.append(super(getOn())); // help on this
        sb.append("\nDimensões: ");
        sb.append(this.dimensions);
        sb.append(" cm");
        sb.append("\nÚltima vez ligada: ");
        sb.append(this.getLigadoInit());
        sb.append("\n");
        return sb.toString();
    }

    /**
     * Dar clone a uma lampada
     * @return Lampada clonada
     */
    public SmartBulb clone(){
        return new SmartBulb(this);
    }

    /**
     * Ligar uma lampada
     */
    public void turnOn(){
        if ("OFF".equals(this.getEstado().toString())) {
            this.setEstado(state.ON);
            this.setLigadoInit(LocalDate.now());
        }
    }

    /**
     * Desligar uma lampada
     */
    public void turnOff(){
        if ("ON".equals(this.getEstado().toString())) {
            this.setEstado(state.OFF);
            double factor = 0;
            switch (this.mode.toString()) {
                case ("COLD"):
                    factor = 10;
                case ("NEUTRAL"):
                    factor = 20;
                case ("WARM"):
                    factor = 30;
            }
            this.setConsumo((float)(0.5 + factor));
        }
    }

}


