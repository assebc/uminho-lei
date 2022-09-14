/**
 * Classe que implementa uma Lampada do exercicio da Ficha 3.
 * Esta classe foi desenvolvida durante as aulas praticas pelo que algumas das
 * linhas de codigo decorrem de decisoes tomadas na altura. Existe naturalmente
 * espaaço para melhorar e alterar este codigo.
 *
 * ATENCAO: a classe Lampada utiliza um enum para guardar os diferentes tipos
 * de consumo. Poderia tambem ser feito com constantes.

 *
 * @author  MaterialPOO
 * @version 20220321
 */


package task4;

public class Lampada {

    public enum Modo {
        ON,
        OFF,
        ECO
    }

    private Modo modo; //maneira mais elegante
    private double cpSEco; //consumo por segundo Eco
    private double cpSOn; //Consumo por segundo On
    private double consumoTotal;
    private double periodoConsumo;

    public Lampada() {
        this.modo = Modo.OFF;
        this.cpSEco = 1;
        this.cpSOn = 2;
        this.consumoTotal = 0;
        this.periodoConsumo = 0;
    }

    public Lampada(Modo x, double cpsE, double cpsO, double cT, double pC) {
                
        this.cpSEco = cpsE;
        this.cpSOn = cpsO;
        this.modo = x;
        this.consumoTotal = cT;
        this.periodoConsumo = pC;
    }

    public Lampada(Lampada l) {
        this.cpSEco = l.getCpSEco();
        this.cpSOn = l.getCpSOn();
        this.modo = l.getModo();
        this.consumoTotal = l.getConsumoTotal();
        this.periodoConsumo = l.getPeriodoConsumo();
    }

    public Modo getModo(){
        return this.modo;
    }

    public void setModo(Modo m) {
        this.modo = m;
    }

    public double getCpSEco(){
        return this.cpSEco;
    }

    public void setCpSEco(double x){
        this.cpSEco = x;
    }

    public double getCpSOn(){
        return this.cpSOn;
    }

    public void setCpSOn(double x){
        this.cpSOn = x;
    }

    public double getConsumoTotal(){
        return this.consumoTotal;
    }

    public void setConsumoTotal(double cT){
        this.consumoTotal = cT;
    }

    public double getPeriodoConsumo(){
        return this.periodoConsumo;
    }

    public void setPeriodoConsumo(double pC){
        this.periodoConsumo = pC;
    }

    public boolean equals(Object o) {
        if (this==o) return true;
        if ((o == null) || (this.getClass() != o.getClass())) return false;

        Lampada l = (Lampada) o;
        return l.getModo() == this.modo &&
                l.getCpSOn() == this.cpSOn &&
                l.getCpSEco() == this.cpSEco &&
                l.getConsumoTotal() == this.consumoTotal &&
                l.getPeriodoConsumo() == this.periodoConsumo;
    }

    public Lampada clone() {
        return new Lampada(this);
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Lampada: ").append(this.modo)
                .append("\nConsumo por segundo Eco: ").append(this.cpSEco)
                .append("\nConsumo por segundo On: ").append(this.cpSOn)
                .append("\nConsumoTotal: ").append(this.consumoTotal)
                .append("\nInicio de ultimo consumo: ").append(this.periodoConsumo);
        return sb.toString();
    }

    private void calculaEco(){
        this.consumoTotal += (System.currentTimeMillis() - this.periodoConsumo) * this.cpSEco;
    }

    private void calculaOn(){
        this.consumoTotal += (System.currentTimeMillis() - this.periodoConsumo) * this.cpSOn;
    }

    //a) 
    public void lampON() {
        if (this.modo == Modo.ECO) {
            calculaEco();
        }
        this.periodoConsumo = System.currentTimeMillis();
        this.modo = Modo.ON;
    }

    //b) 
    public void lampOFF(){
        if (this.modo == Modo.ECO) {
            calculaEco();
        }
        if (this.modo == Modo.ON) {
            calculaOn();
        }
        this.periodoConsumo = System.currentTimeMillis();
        this.modo = Modo.OFF;
    }

    //c)
    public void lampECO(){
        if (this.modo == Modo.ON) {
            calculaOn();
        }
        this.periodoConsumo = System.currentTimeMillis();
        this.modo = Modo.ECO;
    }

    //d)
    public double totalConsumo(){
        //consumo total so mede os usos anteriores, falta o que esta a decorrer agora
        return periodoConsumo() + consumoTotal;
    }

    //e)
    public double periodoConsumo() {
        double atual = 0;
        if (modo == Modo.ON) atual = (System.currentTimeMillis() - this.periodoConsumo) * this.cpSOn;
        else if (modo == Modo.ECO) atual = (System.currentTimeMillis() - this.periodoConsumo) * this.cpSEco;
        return atual;
    }

    
}