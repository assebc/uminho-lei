import java.util.*;
import java.lang.StringBuilder;
import java.time.LocalDateTime;

public class Utilizador {

    private String email;
    private String password;
    private enum genero{
        M,
        F
    }
    private genero gen;
    private Integer altura;
    private Double peso;
    private LocalDateTime data_nascimento; // YYYY-MM-DD
    private String desporto_fav; // desporto que pratica mais atividades

    private Map<String, List<Atividade>> atividades;
    //id de atividade com lista de vezes que aconteceu x atividade
    // init

    public Utilizador(){ // init por default
        this.email = "";
        this.password = "";
        this.gen = genero.F;
        this.altura = 0;
        this.peso = 0.0;
        this.data_nascimento = LocalDateTime.now();
        this.desporto_fav = "";
        this.atividades = new HashMap<>();
    }

    public Utilizador(Utilizador u){ // copia de class
        this.email = u.getEmail();
        this.password = u.getPassword();
        this.gen = u.getGenero();
        this.altura = u.getAltura();
        this.peso = u.getPeso();
        this.data_nascimento = u.getData_Nascimento();
        this.desporto_fav = u.getDesporto_Fav();
        this.atividades = new HashMap<>();
    }

    public Utilizador(String email, String password, LocalDateTime data){ // obrigatórios
        this.email = email;
        this.password = password;
        this.gen = genero.F; //  default
        this.altura = 0; // default
        this.peso = 0.0; // default
        this.data_nascimento = data;
        this.desporto_fav = ""; // default ou não definido
    }

    public Utilizador(String email, String password, genero gen, int altura, double peso, LocalDateTime data, String desporto){
        this.email = email;
        this.password = password;
        this.gen = gen;
        this.altura = altura;
        this.peso = peso;
        this.data_nascimento = data;
        this.desporto_fav = desporto;
    }

    // setters
    public void setEmail(String email) { this.email = email; }
    public void setPassword(String password){ this.password = password; }
    public void setGenero(genero gen){ this.gen = gen; }
    public void setAltura(int altura){ this.altura = altura; }
    public void setPeso(double peso){ this.peso = peso; }
    public void setData_Nascimento(LocalDateTime data){ this.data_nascimento = data; }
    public void setDesporto_Fav(String desporto_fav){ this.desporto_fav = desporto_fav; }
    public void setAtividades(Map<String,List<Atividade>> act) { this.atividades = act; }
    public void setAtividades(Set<Atividade> ativs) { List<Atividade> help = new ArrayList<>(ativs); setAtividades(help); }
    public void setAtividades(List<Atividade> act) { this.atividades.putIfAbsent(act.get(0).getCodigo(),act);}
    public void setAtividade(Atividade act){
            List<Atividade> cena = new ArrayList<>();
            cena.add(act);
            this.atividades.putIfAbsent(act.getCodigo(),cena);
    }

    // getters
    public String getEmail(){ return this.email; }
    public String getPassword(){ return this.password; }
    public genero getGenero(){ return this.gen; }
    public int getAltura(){ return this.altura; }
    public double getPeso(){ return this.peso; }
    public LocalDateTime getData_Nascimento(){ return this.data_nascimento; }
    public String getDesporto_Fav(){ return this.desporto_fav; }

    public Map<String, List<Atividade>> getAtividades(){ return this.atividades; }
    public List<Atividade> getAtividades(String code){ return this.atividades.get(code); }
    public Map<String,Integer> getVezes(){
        Map<String,Integer> vezes = new HashMap<>();
        Set<String> keys = this.atividades.keySet();
        List<String> listKeys = new ArrayList<>(keys);
        for(String obj:listKeys){
            vezes.put(obj,this.atividades.get(obj).size());
        }
        return vezes;
    }

    // equals, clone e toString

    public boolean equals(Object obj){
        if(this==obj) return true;
        if(obj==null||obj.getClass()!=this.getClass()) return false;
        Utilizador u = (Utilizador) obj;
        return (this.email == u.getEmail() && this.password == u.getPassword()
                && this.gen == u.getGenero() && this.altura == u.getAltura()
                && this.peso == u.getPeso() && this.data_nascimento == u.getData_Nascimento()
                && this.desporto_fav == u.getDesporto_Fav());
    }

    public Utilizador clone(){
        return new Utilizador(this);
    }

    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Email do utilizador: \n");
        sb.append(this.email);
        sb.append("Password do utilizador: \n");
        sb.append(this.password);
        sb.append("Genero do utilizador: \n");
        sb.append(this.gen);
        sb.append("Altura do utilizador: \n");
        sb.append(this.altura);
        sb.append("Peso do utilizador: \n");
        sb.append(this.peso);
        sb.append("Data de Nascimento do utilizador (YYYY-MM-DD): \n");
        sb.append(this.data_nascimento);
        sb.append("Desporto favorito do utilizador: \n");
        sb.append(this.desporto_fav);
        return sb.toString();
    }

}
