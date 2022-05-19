package exame21;

import java.util.List;
import java.util.stream.Collectors;

public class Podcast {

    private String nome;
    private int subscricoes;
    private List<Episodio> episodioList;

    public Podcast(List<Episodio> ep){
        this.subscricoes = 0;
        this.episodioList = ep.stream().map(Episodio::clone).toList();
    }

    public Podcast(String nome, int subscricoes, List<Episodio> episodioList) {
        this.nome = nome;
        this.subscricoes = subscricoes;
        this.episodioList = episodioList.stream().map(Episodio::clone).toList();
    }

    public List<Episodio> getEpisodioList(){
        return this.episodioList.stream().map(Episodio::clone).collect(Collectors.toList());
    }

    public int getSubscricoes(){ return this.subscricoes; }

    public String getNome(){ return this.nome; }
}
