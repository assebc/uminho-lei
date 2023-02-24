import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

class PoligonoConvexoTest {

    @Test
    void triangula() {
        List<Triangulo> triangles = new ArrayList<>();
        List<Ponto> points = new ArrayList<>();
        points.add(new Ponto(1,1));
        points.add(new Ponto(2,1));
        points.add(new Ponto(3,1));
        points.add(new Ponto(4,1));
        points.add(new Ponto(10,1));
        PoligonoConvexo p = new PoligonoConvexo(points);
        for(int i = 1; i<points.size()-1; i++){
            triangles.add(new Triangulo(points.get(0),points.get(i),points.get(i+1)));
        }
        assertEquals(triangles.size(),p.triangula().size(),"invalid triangula");
    }
}