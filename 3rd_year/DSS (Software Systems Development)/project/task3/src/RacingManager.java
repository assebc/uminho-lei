package task3.src;

import task3.src.UI.TextUI;
import task3.src.data.*;

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
