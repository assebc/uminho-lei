package task5;

import java.util.*;
import java.util.stream.Collectors;
import java.lang.StringBuilder;
import static java.util.stream.Collectors.toList;


public class Parque2 {
    private String nomeDoParque;
    private Map<String, Lugar> lugares;

    public Parque2(){
        this.nomeDoParque="";
        this.lugares = new TreeMap<String,Lugar>();
    }

    public Parque2(String nomeDoParque, Map<String,Lugar> lugares){
        setNomeDoParque(nomeDoParque);
        setLugares(lugares);
    }

    public Parque2(Parque2 parque){
        this(parque.getNomeDoParque(),parque.getLugares());
    }

    public String getNomeDoParque() {
        return this.nomeDoParque;
    }

    public void setNomeDoParque(String nomeDoParque) {
        this.nomeDoParque = nomeDoParque;
    }

    public Map<String, Lugar> getLugares() {
        return this.lugares;
    }

    public void setLugares(Map<String, Lugar> lugares) {
        for (String n : lugares.keySet()){
            this.lugares.put(n,lugares.get(n).clone());
        }
    }

    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Nome do Parque: ");
        sb.append(this.nomeDoParque);
        sb.append("\nLugares do Parque: ");
        sb.append(this.lugares.toString());
        sb.append("\n");
        return sb.toString();
    }

    public boolean equals(Object obj){
        if (this==obj)
            return true;

        if (obj==null || obj.getClass()!=this.getClass())
            return false;

        Parque2 newParque = (Parque2) obj;
        return (this.nomeDoParque.equals(newParque.getNomeDoParque())  &&  this.lugares.equals(newParque.getLugares()));
    }

    public Parque2 clone(){
        return new Parque2(this);
    }

    //Funcoes da ficha

    public List<Lugar> lugaresOcupados(){
        return this.lugares.values().stream().filter(e->e.getMinutos()>0).collect(toList());
    }

    public void addLugarOcupado(Lugar lugar){
        this.lugares.putIfAbsent(lugar.getMatricula(), lugar);
    }

    public void removeLugar(String matricula){
        this.lugares.remove(matricula);
    }

    public void alteraTempo(String matricula, int tempoRem){
        Lugar lugar = this.lugares.get(matricula);
        lugar.setMinutos(tempoRem);
        this.lugares.put(matricula,lugar);
    }

    public double totalMinInt(){
        return this.lugares.values().stream().mapToDouble(x->x.getMinutos()).sum();
    }

    public double totalMinExt(){
        double sum = 0;
        for (Lugar i : this.lugares.values()){
            sum+=i.getMinutos();
        }
        return sum;
    }

    public boolean existeRegisto(String matricula){
        return this.lugares.keySet().contains(matricula);
    }

    public List<String> matriculasComTempoSupInt(int temp){
        return this.lugares.values().stream().filter(x->x.getMinutos()>temp && x.isPermanente()).map(e->e.getMatricula()).collect(Collectors.toList());
    }

    public List<String> matriculasComTempoSupExt(int temp){
        List<String> matriculas = new ArrayList<String>();
        for (String n: this.lugares.keySet()){
            Lugar lug = this.lugares.get(n);
            if (lug.getMinutos()>temp)
                matriculas.add(n);
        }
        return matriculas;
    }

    public Map<String,Lugar> cloneLugares(){
        Map <String,Lugar> novosLugares = new TreeMap<String,Lugar>();
        novosLugares.putAll(this.lugares);
        return novosLugares;
    }