import java.util.ArrayList;
import java.util.Collections;
import java.util.Collections.*;

public class Ficha04{

    public class Stack {
        private ArrayList<String> STACK = new ArrayList<>();

        public boolean empty() {
            return (STACK.isEmpty());
        }

        public String top() {
            if (empty()) return null;
            return STACK.get(STACK.size() - 1);
        }

        public void push(String a) {
            STACK.add(a);
        }

        public void pop() {
            STACK.remove(STACK.size() - 1);
        }

        public int length() {
            return (STACK.size());
        }
    }

    public class CasaInteligente{

        private ArrayList<Lampada> Lamp = new ArrayList<>();

        public void addLampada(Lampada l){
            Lamp.add(l);
        }

        public void ligaLampadaNormal(int index){
            Lamp.get(index).lampON();
        }

        public void ligaLampadaEco(int index){
            Lamp.get(index).lampECO();
        }

        public int qtEmEco(){
            return (int)(Lamp.stream().filter(l -> (l.getModo().equals(Lampada.Modo.ECO))).count());
        }

        public void removeLampada(int index){
            Lamp.remove(this.Lamp.get(index));
        }

        public void ligaTodasEco(){
            Lamp.stream().forEach(Lampada::lampECO);
        }

        public void ligaTodasMax(){
            Lamp.stream().forEach(Lampada::lampON);
        }

        public double consumoTotal(){
            return Lamp.stream().mapToDouble(Lampada::totalConsumo).sum();
        }

        public Lampada maisGastadora(){}

        public Set<Lampada> podiumEconomia(){}

        public void reset(){}


    }

    public static void main(String [] args){

    }
}