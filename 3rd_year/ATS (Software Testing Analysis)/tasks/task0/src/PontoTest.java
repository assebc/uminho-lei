import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class PontoTest {

    @Test
    void incCoord() {
        Ponto p = new Ponto(1,1);
        Ponto p2 = p;
        p2.setX(p.getX()+1);
        p2.setY(p.getY()+1);
        p.incCoord(p.getX(),p.getY());
        assertEquals(p2,p,"incrementation is invalid");
    }

    @Test
    void decCoord() {
        Ponto p = new Ponto(1,1);
        Ponto p2 = p;
        p2.setX(p.getX()-1);
        p2.setY(p.getY()-1);
        p.decCoord(p.getX(),p.getY());
        assertEquals(p2,p,"decrementation is invalid");
    }

    @Test
    void somaPonto() {
        Ponto p = new Ponto(1,1);
        Ponto p2 = new Ponto(2,2);
        Ponto p3 = new Ponto(1,1);
        p3.setX(p3.getX()+p2.getX());
        p3.setY(p3.getY()+p2.getY());
        p.somaPonto(p2);
        assertEquals(p3,p,"sum is invalid");
    }
}