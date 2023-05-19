package Model;

import java.time.LocalDate;

public class Fatura {
    private LocalDate dataInit;
    private LocalDate dataFim;
    private double KwsConsumidos;
    private double valorDaFatura;


    /**
     * Inicializador de fatura
     * @param dataInit data de inicio de fatura
     * @param dataFim data de retirar fatura
     * @param KwsConsumidos kWs a definir
     * @param valorDaFatura valor da fatura a definir
     */
    public Fatura(LocalDate dataInit, LocalDate dataFim, double KwsConsumidos, double valorDaFatura){
        this.dataInit=dataInit;
        this.dataFim=dataFim;
        this.KwsConsumidos=KwsConsumidos;
        this.valorDaFatura=valorDaFatura;
    }

    /**
     * Duplicar fatura
     * @param fat fatura a duplicar
     */
    public Fatura(Fatura fat){
        this.dataInit=fat.getDataInicial();
        this.dataFim=fat.getDataFinal();
        this.KwsConsumidos=fat.getKwsConsumidos();
        this.valorDaFatura=fat.getValorDaFatura();
    }

    /**
     * Getter kWs consumidos
     * @return kWs consumidos
     */
    public double getKwsConsumidos(){return this.KwsConsumidos;}

    /**
     * Getter valor da fatura
     * @return valor da fatura
     */
    public double getValorDaFatura(){return this.valorDaFatura;}

    /**
     * Getter da data inicial
     * @return data inicial
     */
    public LocalDate getDataInicial(){return this.dataInit;}

    /**
     * Getter da data final
     * @return data final
     */
    public LocalDate getDataFinal(){return this.dataFim;}

    /**
     * Verificar se faturas são iguais
     * @param obj objeto a comparar
     * @return boolean de comparação entre objetos
     */
    public boolean equals(Object obj){
        if (this==obj)
            return true;
        
        if(obj==null||this.getClass()!=obj.getClass())
            return false;

        Fatura nF = (Fatura) obj;
        return(this.dataFim.equals(nF.getDataFinal())  &&  
            this.dataInit.equals(nF.getDataInicial())  &&
            this.KwsConsumidos==nF.getKwsConsumidos()  &&
            this.valorDaFatura==nF.getValorDaFatura());
    }

    /**
     * Clone de fatura
     * @return fatura clonada
     */
    public Fatura clone() throws CloneNotSupportedException {
        return new Fatura(this);
    }

    /**
     * toString de uma fatura
     * @return String com todos os componentes de uma fatura
     */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Início de contagem: ");
        sb.append(this.dataInit.toString());
        sb.append("\tTérmino de contagem: ");
        sb.append(this.dataFim.toString());
        sb.append("\tkWs Consumidos na casa: ");
        sb.append(this.KwsConsumidos);
        sb.append("\tTotal a pagar (IVA incl.): ");
        sb.append(this.valorDaFatura);
        sb.append("\n");
        return sb.toString();
    }
}
