import java.util.*;
import java.util.stream.Collectors;

public class Fitness{

    private Map<String, Utilizador> user;
    private List<Atividade> act;

    public Fitness(){
        this.user = new HashMap<>();
        this.act = new ArrayList<>();
    }
    public boolean existeUtilizador(String email){
        return user.containsKey(email);
    }

    public int quantos(){
        return user.size();
    }

    public int quantos(String atividade, String email){
        return user.get(email).getAtividades(atividade).size();
    }

    public Utilizador getUtilizador(String email){
        return user.get(email);
    }

    public void adiciona(String email, Atividade act){
        user.get(email).setAtividade(act);
    }

    public List<Atividade> getAllAtividades(){
        return this.act;
    }

    public void adiciona(String email, Set<Atividade> ativs){
        user.get(email).setAtividades(ativs);
    }

    public int tempoTotalUtilizador(String email){
        int tempo = 0;
        for(Atividade a : this.act){
            if(a.getUser().equals(getUtilizador(email))) tempo += a.getDuracao();
        }
        return tempo;
    }

    public Atividade atividadeMaisExigente() {
        double calorias = 0;
        int j = 0;
        for(int i = 0;i<act.size();i++){
            if(act.get(i).calorias()>calorias) {
                calorias = act.get(i).calorias();
                j=i;
            }
        }
        return act.get(j);
    }

    public <K, V extends Comparable<V>> K maxUsingIteration(Map<K, V> map) {
        Map.Entry<K, V> maxEntry = null;
        for (Map.Entry<K, V> entry : map.entrySet()) {
            if (maxEntry == null || entry.getValue()
                    .compareTo(maxEntry.getValue()) > 0) maxEntry = entry;
        }
        return maxEntry.getKey();
    }

    public Utilizador utilizadorMaisAtivo(){
        Map<Utilizador,Double> caloriasUser = new HashMap<>();
        for(Atividade a:this.act){
            if(caloriasUser.containsKey(a.getUser()==null)) caloriasUser.put(a.getUser(),a.calorias());
            else caloriasUser.put(a.getUser(), caloriasUser.get(a.getUser()) + a.calorias() );
        }
        return maxUsingIteration(caloriasUser);
    }

    public void atualizaDesportoFav(){
        Collection<Utilizador> values = user.values();
        ArrayList<Utilizador> listofUsers = new ArrayList<>(values);
        for(Utilizador u:listofUsers){
            if(u.getDesporto_Fav()!= maxUsingIteration(u.getVezes())) u.setDesporto_Fav(maxUsingIteration(u.getVezes()));
        }
    }

    // Fase 2

    public void sortByValue(boolean order, Map<Utilizador, Double> map ) {
        List<Map.Entry<Utilizador, Double>> list = new LinkedList<>(map.entrySet());
        Collections.sort(list, new Comparator<Map.Entry<Utilizador, Double>>() {
            public int compare(Map.Entry<Utilizador, Double> o1, Map.Entry<Utilizador, Double> o2) {
                if (order) {
                    return o1.getValue().compareTo(o2.getValue());}
                else {
                    return o2.getValue().compareTo(o1.getValue());
                }
            }
        });
    }

    public Set<Utilizador> ordenarUtilizadores_set(){
        Map<Utilizador,Double> caloriasUser = new HashMap<>();
        for(Atividade a:this.act){
            if(caloriasUser.containsKey(a.getUser()==null)) caloriasUser.put(a.getUser(),a.calorias());
            else caloriasUser.put(a.getUser(), caloriasUser.get(a.getUser()) + a.calorias() );
        }
        sortByValue(true,caloriasUser);
        Set<Utilizador> novos = caloriasUser.keySet().stream().collect(Collectors.toSet());
        return novos;
    }

    public List<Utilizador> ordenarUtilizadores_list(){
        Map<Utilizador,Double> caloriasUser = new HashMap<>();
        for(Atividade a:this.act){
            if(caloriasUser.containsKey(a.getUser()==null)) caloriasUser.put(a.getUser(),a.calorias());
            else caloriasUser.put(a.getUser(), caloriasUser.get(a.getUser()) + a.calorias() );
        }
        sortByValue(true,caloriasUser);
        List<Utilizador> novos = caloriasUser.keySet().stream().collect(Collectors.toList());
        return novos;
    }

    Set<Utilizador> ordenarUtilizador(Comparator<Utilizador> c){
        Set<Utilizador> emails = (Set<Utilizador>) this.user.values();
        emails.stream().sorted(c);
        return emails;
    }

    public List<Utilizador> ordenarUtilizadores_desporto(String code){
        Map<Utilizador,Double> caloriasUser = new HashMap<>();
        for(Atividade a:this.act){
            if(a.getCodigo().equals(code)) {
                if (caloriasUser.containsKey(a.getUser() == null)) caloriasUser.put(a.getUser(), a.calorias());
                else caloriasUser.put(a.getUser(), caloriasUser.get(a.getUser()) + a.calorias());
            }
        }
        sortByValue(true,caloriasUser);
        List<Utilizador> novos = caloriasUser.keySet().stream().collect(Collectors.toList());
        return novos;
    }

    public Map<String, List<Utilizador>> podiumPorActiv(){
         Map<String,List<Utilizador>> podium = new HashMap<>();
         List<String> codes = new ArrayList<>();
         for(int i = 0;i<act.size();i++){
             if(codes.contains(act.get(i).getCodigo())){
                 codes.add(act.get(i).getCodigo());
             }
         }
         for(String code:codes){
             podium.put(code, (List<Utilizador>) ordenarUtilizadores_desporto(code).stream().limit(3));
         }
         return podium;
    }

    // Fase 3

    public List<FazMetros> daoPontos(){

    }


}

