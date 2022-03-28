import java.util.ArrayList;
import java.time.LocalDateTime;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.List;
import java.util.ListIterator;

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

        public int length(){
            return STACK.size();
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
            return Lamp.stream().map(Lampada::clone).max((l1,l2)->compares(l1,l2)).get();
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

    public class FBFeed{

        private ArrayList<FBPost> FB = new ArrayList<>();

        public ArrayList<FBPost> getTimeline() {
            return this.FB;
        }

        public void setTimeline(ArrayList<FBPost> timeline) {
            this.FB = timeline;
        }

        public FBFeed(){
            this.FB = new ArrayList<FBPost>();
        }

        public FBFeed(ArrayList<FBPost> timeline){
            ListIterator<FBPost> iter =  timeline.listIterator();
            while(iter.hasNext()){
                FBPost pos = iter.next();
                this.FB.add(pos.clone());
            }
        }

        public FBFeed(FBFeed feedToPaste){
            this.FB = feedToPaste.getTimeline();
        }


        public int nrPosts(String user){
            return FB.stream() // iterador interno
                    .map(FBPost::clone)
                    .filter(f->f.get_Nome().equals(user)) // condição necessária
                    .collect(Collectors.toCollection(ArrayList::new)) //por os posts de user num Set
                    .size(); // tamanho do Set será o número de posts
        }

        public int nrPosts2(String user){ return postsOf(user).size(); }

        public List<FBPost> postsOf(String user){
            return FB.stream()
                    .map(FBPost::clone)
                    .filter(f->f.get_Nome().equals(user))
                    .collect(Collectors.toList());
        }

        public List<FBPost> postOf_hours(String user, LocalDateTime inicio, LocalDateTime fim){
            for(FBPost f : this.FB){
                if(f.get_Nome().equals(user)){
                    return FB.stream()
                            .filter(fb->fb.get_Date().compareTo(inicio) >=0
                                    && fb.get_Date().compareTo(fim)<=0)
                            .collect(Collectors.toList());
                }
            }
            return null;
        }

        public FBPost getPost(int id){
            for(FBPost f : this.FB){
                if(f.get_Identificador().equals(id))
                    return f.clone();
            }
            return null;
        }

        public void insert_comment(FBPost post, String comentario){
            for(FBPost f : this.FB)
                if(f.equals(post)) f.set_Comments(comentario);

        }

        public void insert_comment_id(int postid, String comentario){
            for(FBPost f : this.FB)
                if(f.get_Identificador().equals(postid)) f.set_Comments(comentario);
        }

        public void like(int postid){
            for(FBPost f : this.FB)
                if(f.get_Identificador().equals(postid)) f.set_Likes(f.get_Likes()+1);
        }

        public int compares(FBPost f1, FBPost f2) {
            if ((f1.get_Comments().size())>(f2.get_Comments().size())) return 1;
            if ((f1.get_Comments().size())<(f2.get_Comments().size())) return -1;
            return 0;
        }

        public List<Integer> top5Comments_int(){
            return FB.stream().map(FBPost::clone)
                    .sorted((f1,f2)->compares(f1,f2))
                    .limit(5)
                    .map(FBPost::get_Identificador)
                    .collect(Collectors.toList());
        }
        public List<Integer> top5Comments_ext() {
            ArrayList<FBPost> copy = new ArrayList<>(this.FB);
            List<Integer> top5 = new ArrayList<>();
            for(int i = 0; i < 5; i++) {
                FBPost mostCommented = null;
                for(FBPost f : copy)
                    if(mostCommented == null || mostCommented.get_Comments().size() < f.get_Comments().size())
                        mostCommented = f;
                top5.add(mostCommented.get_Identificador());
                copy.remove(mostCommented);
            }
            return top5;
        }

    }
    public static void main(String [] args){

    }
}