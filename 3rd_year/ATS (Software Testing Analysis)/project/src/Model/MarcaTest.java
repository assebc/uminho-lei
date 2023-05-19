package Model;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class MarcaTest {

    @Test
    void getNome() {
        Marca m = new Marca("ATS");
        assertEquals(m.getNome(),"ATS","Invalid name!");
    }

    @Test
    void getConsumoDiario() {
        Marca m = new Marca("ATS");
        assertEquals(m.getConsumoDiario(),0.72,"Invalid default consume!");
        m = new Marca("ATS", 0.05);
        assertEquals(m.getConsumoDiario(),0.05,"Invalid consume!");
    }

    @Test
    void setConsumoDiario() {
        Marca m = new Marca("ATS");
        m.setConsumoDiario(0.05);
        assertEquals(m.getConsumoDiario(),0.05, "Invalid consume!");
    }
}