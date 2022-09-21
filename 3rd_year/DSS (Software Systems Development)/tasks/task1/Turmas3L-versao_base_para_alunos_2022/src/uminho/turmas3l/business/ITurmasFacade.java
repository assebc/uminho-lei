/*
 *  DISCLAIMER: Este código foi criado para discussão e edição durante as aulas práticas de DSS, representando
 *  uma solução em construção. Como tal, não deverá ser visto como uma solução canónica, ou mesmo acabada.
 *  É disponibilizado para auxiliar o processo de estudo. Os alunos são encorajados a testar adequadamente o
 *  código fornecido e a procurar soluções alternativas, à medida que forem adquirindo mais conhecimentos.
 */
package uminho.turmas3l.business;

import java.util.Collection;

/**
 * API da Facade da lógica de negócio.
 *
 * @author DSS
 * @version 20201206
 */
public interface ITurmasFacade {

    /**
     * Método que adiciona um aluno.
     *
     * @param a aluno a adicionar
     */
    void adicionaAluno(Aluno a);

    /**
     * Método que adiciona uma turma
     *
     * @param t turma a dicionar
     */
    void adicionaTurma(Turma t);

    /**
     * Método que altera a sala da turma.
     *
     * @param tid id da turma que vai mudar de sala
     * @param s nova sala da turma
     */
    void alteraSalaDeTurma(String tid, Sala s);

    /**
     * Método que verifica se uma turma existe
     *
     * @param tid id da turma a procurar
     * @return true se a turma existe
     */
    boolean existeTurma(String tid);

    /**
     * Método que procura um aluno
     *
     * @param num número do aluno a procurar
     * @return true se o aluno existe
     */
    Aluno procuraAluno(String num);

    /**
     * Método que devolve os alunos de uma turma.
     *
     * @param tid id da turma
     * @return alunos da turma
     */
    Collection<String> getAlunos(String tid);

    /**
     * Método que devolve todas as turmas
     *
     * @return todas as turmas
     */
    Collection<Turma> getTurmas();

    /**
     * Método que verifica se um aluno existe
     *
     * @param num número do aluno a procurar
     * @return true se o aluno existe
     */
    boolean existeAluno(String num);

    /**
     * Método que adiciona um aluno à turma.
     *
     * @param tid id da turma onde se vai colocar o aluno
     * @param num número do aluno
     */
    void adicionaAlunoTurma(String tid, String num);

    /**
     * Método que devolve todos os alunos registados.
     *
     * @return todos os alunos registados
     */
    Collection<Aluno> getAlunos();

    /**
     * Método que remove um aluno da turma.
     *
     * @param tid id da turma
     * @param num número do aluno a remover
     */
    void removeAlunoTurma(String tid, String num);

    /**
     * Método que verifica se o aluno existe na turma
     *
     * @param tid Turma a pesqueisar
     * @param num Número de aluno a pesquisar
     * @return True se aluno existe na turma
     */
    boolean existeAlunoEmTurma(String tid, String num);
}
