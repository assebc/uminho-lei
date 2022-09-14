package task4;

import java.time.LocalDateTime;
import java.util.ArrayList;

public class FBPost{

    private Integer identificador;
    private String nome;
    private LocalDateTime date_creation;
    private String content;
    private Integer num_likes;
    private ArrayList<String> comments;

    public FBPost(){
        this.identificador = -1;
        this.nome = null;
        this.date_creation = null;
        this.content = null;
        this.num_likes = 0;
        this.comments = null;
    }

    public FBPost(Integer id, String n1, LocalDateTime d1, String content, Integer likes, ArrayList<String> cmnt){
        this.identificador = id;
        this.nome = n1;
        this.date_creation = d1;
        this.content = content;
        this.num_likes = likes;
        this.comments = cmnt;
    }

    public FBPost(FBPost f){
        this.identificador = f.get_Identificador();
        this.nome = f.get_Nome();
        this.date_creation = f.get_Date();
        this.content = f.get_Content();
        this.num_likes = f.get_Likes();
        this.comments = f.get_Comments();
    }

    public Integer get_Identificador(){
        return this.identificador;
    }

    public void set_Identificador(Integer id){
        this.identificador = id;
    }

    public String get_Nome(){
        return this.nome;
    }

    public void set_Nome(String nome){
        this.nome = nome;
    }

    public LocalDateTime get_Date(){
        return this.date_creation;
    }

    public void set_Date(LocalDateTime d1){
        this.date_creation = d1;
    }

    public String get_Content(){
        return this.content;
    }

    public void set_Content(String content){ this.content = content; }

    public Integer get_Likes(){
        return this.num_likes;
    }

    public void set_Likes(Integer likes){
        this.num_likes = likes;
    }

    public ArrayList<String> get_Comments(){
        return this.comments;
    }

    public void set_Comments(ArrayList<String> comments) {
        this.comments = new ArrayList<>(comments);
    }

    public void set_Comments(String cmnts){
        this.comments.add(cmnts);
    }

    public boolean equals(Object o){
        if(this==o) return true;
        if ((o==null) || (o.getClass() != this.getClass())) return false;

        FBPost f = (FBPost) o;
        return f.get_Identificador() == this.identificador &&
                f.get_Nome() == this.nome &&
                f.get_Date() == this.date_creation &&
                f.get_Content() == this.content &&
                f.get_Likes() == this.num_likes &&
                f.get_Comments() == this.comments;
    }

    public FBPost clone() {
        return new FBPost(this);
    }


}