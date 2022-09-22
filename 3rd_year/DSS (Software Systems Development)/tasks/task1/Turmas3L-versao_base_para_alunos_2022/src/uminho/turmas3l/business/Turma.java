/*
 *  DISCLAIMER: Este código foi criado para discussão e edição durante as aulas práticas de DSS, representando
 *  uma solução em construção. Como tal, não deverá ser visto como uma solução canónica, ou mesmo acabada.
 *  É disponibilizado para auxiliar o processo de estudo. Os alunos são encorajados a testar adequadamente o
 *  código fornecido e a procurar soluções alternativas, à medida que forem adquirindo mais conhecimentos.
 */
package uminho.turmas3l.business;

import java.util.ArrayList;
import java.util.Collection;
import java.util.TreeSet;
import java.util.stream.Collectors;

/**
 * Classe que representa uma turma
 *
 * ATENÇÃO:
 * Esta versão ainda utiliza um Collection para registar a lista de alunos da turma.
 * Essa colecção deverá passsar a ser apenas dos números dos alunos quando o exercício da Ficha 5 for resolvido.
 *
 * Considera-se que a lista de alunos é uma agregação.
 *
 * @author JFC
 * @version 20201206
 */
public class  Turma {

    private String id;
    private Sala sala;
    private Collection<String> lstalunos;

    public Turma() {
        this.id = "";
        this.sala = new Sala();
        this.lstalunos = new TreeSet<>();
    }

    public Turma(String id, Sala sala) {
        this();
        this.sala = sala;
        this.id = id;
    }

    public Turma(String id, Sala sala, Collection<String> alunos) {
        this();
        this.sala = sala;
        this.id = id;
        this.lstalunos.addAll(alunos);
    }

    /**
     * @return identificador da turma
     */
    public String getId() {
        return this.id;
    }

    /**
     * @return sala da turma
     */
    public Sala getSala() { return sala; }

    /**
     * @param s nova sala da turma
     */
    public void setSala(Sala s) {
        this.sala = s;
    }

    /**
     * Método que adiciona um aluno à turma.
     *
     * Deverá ser garantido que o aluno existe no AlunoDAO.
     *
     * @param a novo aluno
     */
    public void adiciona(String a) {
         this.lstalunos.add(a);
    }

    /**
     * @return Todos os alunos da turma
     */
    public Collection<String> getAlunos() {
        return new ArrayList<>(this.lstalunos);
    }

    /**
     * @return String que representa a Turma
     */
    public String toString() {
        return "Turma("+this.id+", "+this.sala+", "+this.lstalunos +")";
    }

    /**
     * @param num Numero de aluno a remover
     */
    public void removeAluno(String num) {
        this.lstalunos.remove(num);
    }

    /**
     * @param num Número de aluno a pesquisar
     * @return True se aluno existe na turma
     */
    public boolean existeAluno(String num) {
        return this.lstalunos.contains(num);
    }
}
