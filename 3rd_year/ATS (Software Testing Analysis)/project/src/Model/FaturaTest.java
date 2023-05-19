package Model;

import org.junit.jupiter.api.Test;

import java.time.LocalDate;

import static org.junit.jupiter.api.Assertions.*;

class FaturaTest {

    @Test
    void getKwsConsumidos() {
        Fatura f = new Fatura(LocalDate.ofYearDay(2010,30),LocalDate.now(), 2.0, 15.0);
        assertEquals(2.0,f.getKwsConsumidos(),"Invalid kws value!");
    }

    @Test
    void getValorDaFatura() {
        Fatura f = new Fatura(LocalDate.ofYearDay(2010,30),LocalDate.now(), 2.0, 15.0);
        assertEquals(15.0,f.getValorDaFatura(),"Invalid value of receipt!");
    }

    @Test
    void getDataInicial() {
        Fatura f = new Fatura(LocalDate.ofYearDay(2010,30),LocalDate.now(), 2.0, 15.0);
        assertEquals(LocalDate.ofYearDay(2010,30),f.getDataInicial(),"Invalid start date!");
    }

    @Test
    void getDataFinal() {
        Fatura f = new Fatura(LocalDate.ofYearDay(2010,30),LocalDate.ofYearDay(2015,30), 2.0, 15.0);
        assertEquals(LocalDate.ofYearDay(2015,30),f.getDataFinal(),"Invalid end date!");
    }
}