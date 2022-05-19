package exame21;

import java.util.Map;

public class Utilizador {

    private Map<String, Podcast> pod_subs; //podcasts a qual o user esta subscrito
    private int num_podcasts;
    private String name;

    public Utilizador(Utilizador utilizador) {
        this.pod_subs = utilizador.getPod_subs();
        this.num_podcasts = utilizador.getNum_podcasts();
        this.name = utilizador.getName();
    }

    public String getName(){
        return this.name;
    }

    public int getNum_podcasts() {
        return num_podcasts;
    }

    public Map<String,Podcast> getPod_subs(){
        return this.pod_subs;
    }

    public Utilizador clone(){
        return new Utilizador(this);
    }
}
