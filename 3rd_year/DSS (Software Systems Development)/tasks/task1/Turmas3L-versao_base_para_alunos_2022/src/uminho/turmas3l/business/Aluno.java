/*
 *  DISCLAIMER: Este código foi criado para discussão e edição durante as aulas práticas de DSS, representando
 *  uma solução em construção. Como tal, não deverá ser visto como uma solução canónica, ou mesmo acabada.
 *  É disponibilizado para auxiliar o processo de estudo. Os alunos são encorajados a testar adequadamente o
 *  código fornecido e a procurar soluções alternativas, à medida que forem adquirindo mais conhecimentos.
 */
package uminho.turmas3l.business;

import java.util.Comparator;

/**
 * Classe que reprsenta um aluno
 *
 * @author DSS
 * @version 20201208
 */
public class Aluno implements Comparable<Aluno> {
    public static Comparator<Aluno> NumComparator = Comparator.comparing(Aluno::getNumero);

    private String numero;
    private String nome;
    private String email;

    public Aluno(String numero, String nome, String email) {
        this.numero = numero;
        this.nome = nome;
        this.email = email;
    }

    /**
     * Método que muda o número do aluno.
     *
     * Na realidade o número depois de atribuído não deve ser alterado, pelo que o método está privado.
     * Mas poderia/deveria ser removido.
     *
     * @param numero novo número
     */
    private void setNumero(String numero) {
        this.numero = numero;
    }

    /**
     * @param nome novo nome
     */
    public void setNome(String nome) {
        this.nome = nome;
    }

    /**
     * @param email novo email
     */
    public void setEmail(String email) {
        this.email = email;
    }

    /**
     * @return ...
     */
    public String getNumero() {
        return numero;
    }

    /**
     * @return nome do aluno
     */
    public String getNome() {
        return nome;
    }

    /**
     * @return email do aluno
     */
    public String getEmail() {
        return email;
    }

    /**
     * @return String que representa o aluno.
     */
    @Override
    public String toString() {
        return "Aluno("+this.numero+", "+this.nome+", "+this.email+")";
    }

    @Override
    public int compareTo(Aluno o) {
        return this.numero.compareTo(o.getNumero());
    }
}
