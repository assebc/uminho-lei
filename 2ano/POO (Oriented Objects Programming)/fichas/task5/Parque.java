package task5;

import java.util.ArrayList;
import java.util.stream.Collectors;
import java.util.List;

public class Parque{

    private ArrayList<Lugar> Parque = new ArrayList<>();

    public ArrayList<Lugar> getParque(){ return this.Parque; }
    public void setParque(ArrayList<Lugar> p){ this.Parque = p; }
    public Parque(){ this.Parque = new ArrayList<Lugar>(); }
    public Parque(Parque parque){ this.Parque = parque.getParque(); }

    public /* algo */ get_matriculasLugares(){ }


}