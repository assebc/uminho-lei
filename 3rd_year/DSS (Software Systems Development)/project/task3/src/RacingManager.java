package EntregaFinal.src;

import EntregaFinal.src.UI.TextUI;
import EntregaFinal.src.data.*;

public class RacingManager {
    public static void main(String[]args){
        CarroDAO.buildInstance();
        ContasDAO.buildInstance();
        PilotoDAO.buildInstance();
        CampeonatoDAO.buildInstance();
        CircuitoDAO.buildInstance();
        CampeonatoAtivoDAO.buildInstance();
        JogadorAtivoDAO.buildInstance();
        new TextUI().run();
    }
}
