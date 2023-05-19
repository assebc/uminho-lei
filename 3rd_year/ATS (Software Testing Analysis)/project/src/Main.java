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

    }   
}
