package Model;

import java.io.Serializable;

public class Marca implements Serializable {

    private String nome;
    private double consumoDiario;

    /**
     * Inicializador de uma marca com o seu dome e o consumo pretendido
     * @param nome Nome da marca
     * @param consumo Consumo da marca
     */
    public Marca(String nome, double consumo) {
        this.nome = nome;
        this.consumoDiario = consumo;
    }

    /**
     * Inicializador de uma marca através do nome
     * Consumo diário default de 0.72
     * @param nome nome da marca
     */
    public Marca(String nome) {
        this.nome = nome;
        this.consumoDiario = 0.72; //coluna com consumo de 30W * 24h em kWh
    }

    /**
     * Getter do nome da marca
     * @return nome da marca
     */
    public String getNome() {
        return this.nome;
    }


    /**
     * Getter do consumo diário
     * @return Consumo diário
     */
    public double getConsumoDiario() {
        return this.consumoDiario;
    }

    /**
     * Setter do consumo diário
     * @param consumoDiario Consumo dirário a settar
     */
    public void setConsumoDiario(double consumoDiario) {
        this.consumoDiario = consumoDiario;
    }

    /**
     * toString de uma marca
     * @return String com os dados de uma Marca
     */
    public String toString(){
        StringBuffer sb = new StringBuffer();
        sb.append("NOME: ");
        sb.append(this.nome);
        sb.append("\tCONSUMO DIÁRIO: ");
        sb.append(this.consumoDiario);
        sb.append("\n");
        return sb.toString();
    }

}
