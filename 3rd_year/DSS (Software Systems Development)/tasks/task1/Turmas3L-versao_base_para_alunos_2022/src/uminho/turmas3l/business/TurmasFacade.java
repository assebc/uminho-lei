/*
 *  DISCLAIMER: Este código foi criado para discussão e edição durante as aulas práticas de DSS, representando
 *  uma solução em construção. Como tal, não deverá ser visto como uma solução canónica, ou mesmo acabada.
 *  É disponibilizado para auxiliar o processo de estudo. Os alunos são encorajados a testar adequadamente o
 *  código fornecido e a procurar soluções alternativas, à medida que forem adquirindo mais conhecimentos.
 */
package uminho.turmas3l.business;

import uminho.turmas3l.data.TurmaDAO;
import uminho.turmas3l.data.AlunoDAO;
import uminho.turmas3l.data.SalaDAO;

import java.util.*;

/**
 * Versão muito simplificada de um Facade para a turma.
 *
 * @author JFC
 * @version 20201206
 */
public class TurmasFacade implements ITurmasFacade {

    private Map<String,Turma> turmas;
    private Map<String,Aluno> alunos;
    private Map<String,Sala> salas;

    public TurmasFacade() {
        this.turmas = TurmaDAO.getInstance();
        this.alunos = AlunoDAO.getInstance();
        this.salas = SalaDAO.getInstance();
    }

    /**
     * Método que devolve todos os alunos registados.
     *
     * @return todos os alunos registados
     */
    @Override
    public Collection<Aluno> getAlunos() {
        return new ArrayList<>(this.alunos.values());
    }

    /**
     * Método que devolve todos as salas registadas.
     *
     * @return todos as salas registadas
     */
    @Override
    public Collection<Sala> getSalas() {
        return new ArrayList<>(this.salas.values());
    }

    /**
     * Método que remove um aluno da turma.
     *
     * @param tid id da turma
     * @param num número do aluno a remover
     */
    @Override
    public void removeAlunoTurma(String tid, String num) {
        Turma t = this.turmas.get(tid);
        t.removeAluno(num);
        this.turmas.put(tid, t);  // Necessário fazer put para actualizar a BD.
    }

    /**
     * Método que devolve os alunos de uma turma.
     *
     * Transforma a lista de Números de aluno que vem do TurmaDAO em alunos que vai buscar ao AlunoDAO.
     *
     * @param tid id da turma
     * @return alunos da turma
     */
    @Override
    public Collection<String> getAlunos(String tid) {

        return turmas.get(tid).getAlunos();
    }

    /**
     * @return todas as turmas
     */
    @Override
    public Collection<Turma> getTurmas() {
        return turmas.values();
    }

    /**
     * @param a aluno a adicionar
     */
    @Override
    public void adicionaAluno(Aluno a) {
        this.alunos.put(a.getNumero(), a);
    }

    /**
     * @param t turma a dicionar
     */
    @Override
    public void adicionaTurma(Turma t) {
        this.turmas.put(t.getId(), t);
    }

    /**
     * @param s sala a dicionar
     */
    @Override
    public void adicionaSala(Sala s) {
        this.salas.put(s.getNumero(),s);
    }

    /**
     * @param s sala a procurar
     * @return true se a sala existe
     */
    @Override
    public boolean existeSala(Sala s) {
        return this.salas.containsValue(s);
    }

    /**
     * @param tid id da turma que vai mudar de sala
     * @param s nova sala da turma
     */
    @Override
    public void alteraSalaDeTurma(String tid, Sala s) {
        Turma t = turmas.get(tid);
        if(salas.containsValue(s)) {
            t.setSala(s);
            turmas.put(t.getId(), t); // Para actualizar a BD!
        } else salas.put(s.getNumero(),s);

    }

    /**
     * @param tid id da turma a procurar
     * @return true se a turma existe
     */
    @Override
    public boolean existeTurma(String tid) {
        return turmas.containsKey(tid);
    }

    /**
     * @param num número do aluno a procurar
     * @return true se o aluno existe
     */
    @Override
    public Aluno procuraAluno(String num) {
        return this.alunos.get(num);
    }

    /**
     * @param num número do aluno a procurar
     * @return true se o aluno existe
     */
    @Override
    public boolean existeAluno(String num) {
        return this.alunos.containsKey(num);
    }

    /**
     * Método que adiciona um aluno à turma.
     *
     * NOTA 1: Falta garantir que aluno existe
     * NOTA 2: Uma vez que o modelo relacional só permite que o aluno esteja numa turma, este será retirado da
     * turma anterior, se estiver numa.
     *
     * @param tid id da turma onde se vai colocar o aluno
     * @param num número do aluno
     */
    @Override
    public void adicionaAlunoTurma(String tid, String num) {
        Turma t = this.turmas.get(tid);
        t.adiciona(num);
        turmas.put(tid, t);
    }

    /**
     * @param tid Turma a pesqueisar
     * @param num Número de aluno a pesquisar
     * @return True se aluno existe na turma
     */
    @Override
    public boolean existeAlunoEmTurma(String tid, String num) {
        return this.turmas.get(tid).existeAluno(num);
    }

}
