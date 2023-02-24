import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class RetanguloTest {

    @Test
    void areaQuadrado() {
        // rectangle
        Ponto p1 = new Ponto(1,1);
        Ponto p2 = new Ponto(-1,-1);
        Ponto p3 = new Ponto(1,-1);
        Ponto p4 = new Ponto(-1,1);
        Retangulo r = new Retangulo(p1,p2,p3,p4);
        double area = p1.distancia(p2) * p2.distancia(p3);
        assertEquals(area,r.areaQuadrado(),0.001,"failed the test");

        // square
        Ponto px = new Ponto(2,2);
        Ponto py = new Ponto(0,0);
        Ponto pz = new Ponto(2,0);
        Ponto pw = new Ponto(0,2);
        Retangulo r2 = new Retangulo(px,pz,py,pw);
        double area2 = px.distancia(pw) * px.distancia(pw);
        assertEquals(area2,r2.areaQuadrado(),0.001, "failed 2nd test");
    }
}