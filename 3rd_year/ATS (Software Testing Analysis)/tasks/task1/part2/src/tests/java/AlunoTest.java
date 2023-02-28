import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class AlunoTest {

    Aluno a;

    @BeforeEach
    public void setup(){
        a = new Aluno();
    }

    @Test
    void setNomeTest() {
        a.setNome("Miguel");
        assertEquals("Miguel", a.getNome(), "Nome do aluno incorreto");
    }

    @Test
    void setNotaTest() {
        assertThrows(NotaInvalidaException.class, () ->  a.setNota("ATS", 49), "Nota inválida aceite");
        assertThrows(NotaInvalidaException.class, () ->  a.setNota("ATS", -620), "Nota inválida aceite");
    }

    @Test
    void incrementaNotaTest() throws NotaInvalidaException {
        a.setNota("ATS", 10);
        a.incrementaNota("ATS", 5);
        assertEquals(15, a.getNota("ATS"), 0.05, "Nota inválida após incremento");

    }
}
