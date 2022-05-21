import Controller.Controller;
import Model.SmartCity;
import View.*;

import java.util.Scanner;

public class Main{
    public static void main(String[] args) {



        //city = p.parse(city.getDeviceId(), city.getHouseId());
        //System.out.println(city.toString());
        //city.saveState("state");
        SmartCity city = new SmartCity();
        Controller controller = new Controller(city);
        Scanner scanner = new Scanner(System.in);
        View view = new View(controller, scanner);
        view.run();
        scanner.close();

       

        // SmartHouse casa = new SmartHouse();
        // casa.addDivisao("teste");
        // SmartDevice disp = new SmartBulb(10);
        // casa.addDevice("teste", disp);
        // casa.setDivisaoOn("teste");
        // System.out.println(casa.toString());


        //SmartCity city = new SmartCity();
        //SmartCity nueva = city.loadState("state");
        //System.out.println(nueva.toString());
        // //System.out.println(nueva.toString());
    }   
}
