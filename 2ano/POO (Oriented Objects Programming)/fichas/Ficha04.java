import java.util.ArrayList;
import java.util.Comparator;
import java.util.Set;
import java.util.TreeSet;
import java.util.stream.Collectors;

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

        public Lampada maisGastadora(){
            return Lamp.stream().clone();
        }
        public int compares(Lampada l1, Lampada l2) {
            if (l1.totalConsumo()>(l2.totalConsumo())) return 1;
            if (l1.totalConsumo()<(l2.totalConsumo())) return -1;
            return 0;
        }

        public Set<Lampada> podiumEconomia(){
            return Lamp.stream().map(Lampada::clone)
                       .sorted((l1,l2)->compares(l1,l2))
                       .limit(3).collect(Collectors.toSet());

        }

        public void reset(){
            Lamp.stream().forEach(l->l.setPeriodoConsumo(0.0));
        }


    }

    public static void main(String [] args){

    }
}