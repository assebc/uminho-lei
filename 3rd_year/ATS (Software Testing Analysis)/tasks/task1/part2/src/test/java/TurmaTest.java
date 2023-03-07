import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class TurmaTest {

    Aluno a, b, c;
    Turma t;

    @BeforeEach
    public void setup() {
        a = new Aluno("Alfredo", "A00000");
        b = new Aluno("Bernardo", "A00001");
        c = new Aluno("Carlos", "A00002");
        t = new Turma();
    }

    @Test
    void addAlunoTest() {
        t.addAluno(a);
        assertTrue(t.containsAluno("A00000"), "Aluno inserido nao se encontra na turma");
    }

    @Test
    void getAlunoTest() {
        t.addAluno(a);
        try {
            Aluno r = t.getAluno("A00000");
            assertEquals(a, r, "Alfredo inserido e obtido de turma nao e igual ao original");
        } catch (AlunoInexistenteException e) {
            fail("AlunoInexistenteException no teste getAlunoTest");
        }
    }

    @Test
    void mediaTest() {
        try {
            a.setNota("ATS", 10);
            b.setNota("ATS", 12);
            c.setNota("ATS", 8);
            t.addAluno(a);
            t.addAluno(b);
            t.addAluno(c);
            assertEquals(10.0, t.media(), 0.05, "Media calculada com valor incorreto");
        } catch (Exception e) {
            fail("NotaInvalidaException no teste mediaException");
        }
    }
}
