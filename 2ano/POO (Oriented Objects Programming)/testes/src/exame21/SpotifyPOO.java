package exame21;

import java.util.*;

public class SpotifyPOO {

    private Map<String, Podcast> podcasts;
    private Map<String,Utilizador> users;

    public List<Episodio> getEpisodio(String nomePodcast){
        if (this.podcasts.get(nomePodcast) == null) return new ArrayList<>();
        return this.podcasts.get(nomePodcast).getEpisodioList().stream().map(Episodio::clone).toList();
    }

    public void remove(String nomeP) throws PodcastNaoExisteException, UtilizadorSubscreveException {
        if(!this.podcasts.containsKey(nomeP)) throw new PodcastNaoExisteException(nomeP);
        else{
            if(this.podcasts.get(nomeP).getSubscricoes()>0) throw  new UtilizadorSubscreveException(nomeP);
            else this.podcasts.remove(nomeP);
        }
    }

    public Episodio getEpisodioMaisLongo(String u){
        if(!this.users.containsKey(u)) return null;
        return this.users.get(u).getPod_subs().values()
                .stream()
                .flatMap(pName -> this.podcasts.get(pName).getEpisodioList().stream())
                .max(Comparator.comparingDouble(Episodio::getDuracao))
                .get();
    }

    public Map<Integer, List<Episodio>> episodiosPorClassf() {
        Map<Integer, List<Episodio>> map = new HashMap<>();
        podcasts.values()
                .stream()
                .flatMap(p -> p.getEpisodioList().stream())
                .forEach(e -> map.getOrDefault(e.getClassificacao(), new ArrayList<>()).add(e));
        return map;
    }
}
