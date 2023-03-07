package Calculator;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class CalculadoraTest {
    @Test
    public void adiciona01() {
        Calculadora c = new Calculadora();
        int x = c.adiciona(5);
        assertEquals(5,x);
    }
    @Test
    public void adiciona02() {
        Calculadora c = new Calculadora();
        int x = c.adiciona(2,2);
        assertEquals(4,x);
    }

    @Test
    public void adiciona03() {
        Calculadora c = new Calculadora();
        int x = c.adiciona(1,1);
        assertEquals(2,x);
    }

    @Test
    public void subtrai01() {
        Calculadora c = new Calculadora();
        int x = c.subtrai(0,0);
        assertEquals(0,x);
    }

    @Test
    public void subtrai02() {
        Calculadora c = new Calculadora();
        int x = c.subtrai(5,2);
        assertEquals(-7,x);
    }

    @Test
    public void subtrai03() {
        Calculadora c = new Calculadora();
        int x = c.subtrai(3);
        assertEquals(-3,x);
    }

    @Test
    public void ultimoResultado01() {
        Calculadora c = new Calculadora();
        assertEquals(0,c.ultimoResultado());
    }

    @Test
    public void ultimoResultado02() {
        Calculadora c = new Calculadora();
        c.adiciona(10);
        assertEquals(10,c.ultimoResultado());
    }

    @Test
    public void adiciona_subtraiTest(){
        Calculadora c = new Calculadora();
        c.subtrai(5);
        c.adiciona(5);
        assertEquals(0,c.ultimoResultado());
        c.adiciona(10,10);
        c.subtrai(10,10);
        assertEquals(0,c.ultimoResultado());
    }
}
