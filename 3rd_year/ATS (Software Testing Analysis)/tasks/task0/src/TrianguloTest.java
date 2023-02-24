import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class TrianguloTest {

    @Test
    void areaTriangulo() {
        Ponto p1 = new Ponto(0,1);
        Ponto p2 = new Ponto(1,0);
        Ponto p3 = new Ponto(-1,0);
        Triangulo t = new Triangulo(p1,p2,p3);
        double a = p1.distancia(p2);
        double b = p2.distancia(p3);
        double c = p3.distancia(p1);
        double area = 0.25 * Math.sqrt((a+b+c)*(-a+b+c)*(a-b+c)*(a+b-c));
        assertEquals(area,t.areaTriangulo(), 0.001,"area do triangulo invalida");
    }
}