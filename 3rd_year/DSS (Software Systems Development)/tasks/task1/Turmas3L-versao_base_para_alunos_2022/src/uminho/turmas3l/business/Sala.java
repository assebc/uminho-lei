/*
 *  DISCLAIMER: Este código foi criado para discussão e edição durante as aulas práticas de DSS, representando
 *  uma solução em construção. Como tal, não deverá ser visto como uma solução canónica, ou mesmo acabada.
 *  É disponibilizado para auxiliar o processo de estudo. Os alunos são encorajados a testar adequadamente o
 *  código fornecido e a procurar soluções alternativas, à medida que forem adquirindo mais conhecimentos.
 */
package uminho.turmas3l.business;

/**
 * Classe que representa uma sala.
 *
 * @author DSS
 * @version 20201206
 */
public class Sala {
    private String numero;
    private String edificio;
    private int capacidade;

    public Sala() {
        this.numero = "n/d";
        this.edificio = "n/d";
        this.capacidade = 0;
    }
    public Sala(String numero, String edificio, int capacidade) {
        this.numero = numero;
        this.edificio = edificio;
        this.capacidade = capacidade;
    }

    /**
     * @param capacidade nova capacidade
     */
    public void setCapacidade(int capacidade) {
        this.capacidade = capacidade;
    }

    /**
     * @param edificio novo edifício
     */
    public void setEdificio(String edificio) {
        this.edificio = edificio;
    }

    /**
     * @param numero novo número
     */
    public void setNumero(String numero) {
        this.numero = numero;
    }

    /**
     * @return capacidade da sala
     */
    public int getCapacidade() {
        return capacidade;
    }

    /**
     * @return edifício onde a sala se localiza
     */
    public String getEdificio() {
        return edificio;
    }

    /**
     * @return número da sala
     */
    public String getNumero() {
        return numero;
    }

    /**
     * @return String que representa a sala
     */
    @Override
    public String toString() {
        return "Sala("+this.edificio +", "+this.numero +", "+this.capacidade +")"
                ;
    }

}
