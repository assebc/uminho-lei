import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Fitness {

    private List<User> utilizadores = new ArrayList<>();
    private List<Atividade> atividades = new ArrayList<>();

    public boolean existeUtilizador(String email){
        return utilizadores.stream().anyMatch(u->u.getEmail().equals(email));
    }
    public int quantos(){
        return utilizadores.size();
    }
    public int quantos(String atividade, String email){
        return (int) utilizadores.stream()
                .map(u->u.getEmail().equals(email) && u.getAtividades().equals(atividade))
                .count();
    }

    public User getUtilizador(String email){
        return (User) utilizadores.stream().map(u->u.getEmail().equals(email));
    }

    public void adiciona(String email, Atividade act){
        User u = getUtilizador(email);
        u.setAtividade(act);
    }

    public List<Atividade> getAllAtividades(){
        return this.atividades;
    }

    public void adiciona(String email, Set<Atividade> act){
        User u = getUtilizador(email);
        List<Atividade> act_l= new ArrayList<>(act);
        u.setAtividades(act_l);
    }

    public int tempoTotalUtilizador(String email){
        User u = getUtilizador(email);
        List<Atividade> acts = u.getAtividades();
        return acts.stream().map(a->a.getDuracao()).sum();
    }

    public Atividade atividadeMaisExigente(){
        return atividades.stream()
                .map(a->a.getCalorias())
                .max().clone();
    }

    public User utilizadorMaisAtivo(){
        int idx = -1, max = 0;
        for(User u:utilizadores){
            for(Atividade a : u.getAtividades()){
                if(max < a.getCalorias()) {
                    max = a.getCalorias(); idx++;
                }
            }
        }
        return utilizadores.get(idx);
    }

    public void atualizaDesportoFav(){
        for(User u:utilizadores){
            u.setDesporto_Fav(u.getAtividades()
                        .stream()
                        .map(a->a.atualizaDesporto()));
        }
    }

    public void swap(int i, int j, List<User> users){
        User tmp = users.get(i);
        users.set(i,users.get(j));
        users.set(j,tmp);
    }
    public Set<User> ordenarUtilizadores(){
        int idx = 0;
        Set<User> ordered = new HashSet<>();
        List<User> ordered_l = new ArrayList<>();
        for(User u:utilizadores){
            ordered_l.add(u);
            idx = 0;
            for(User p : ordered_l){
                if(u.getCalorias()<p.getCaloras()){
                    swap(idx, ordered_l.get(ordered_l.indexOf(u)), ordered_l);
                    break;
                } else idx++;
            }
        }

    }

}
