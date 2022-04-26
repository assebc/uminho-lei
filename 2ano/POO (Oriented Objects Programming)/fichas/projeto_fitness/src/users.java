//package src;

import java.lang.StringBuilder;
import java.time.LocalDateTime;

public class Users {

    private String email;
    private String password;
    private enum genero{
        M,
        F
    }
    private genero genero;
    private Integer altura;
    private Double peso;
    private LocalDateTime data_nascimento; // YYYY-MM-DD
    private String desporto_fav; // desporto que pratica mais atividades

    // init

    public Users(){ // init por default
        this.email = "";
        this.password = "";
        this.genero = genero.F;
        this.altura = 0;
        this.peso = 0.0;
        this.data_nascimento = LocalDateTime.now();
        this.desporto_fav = "";
    }

    public Users(Users u){ // copia de class
        this.email = u.email;
        this.password = u.password;
        this.genero = u.genero;
        this.altura = u.altura;
        this.peso = u.peso;
        this.data_nascimento = u.data_nascimento;
        this.desporto_fav = u.desporto_fav;
    }

    public Users(String email, String password, LocalDateTime data){ // obrigatórios
        this.email = email;
        this.password = password;
        this.genero = genero.F; //  default
        this.altura = 0; // default
        this.peso = 0.0; // default
        this.data_nascimento = data;
        this.desporto_fav = ""; // default ou não definido
    }

    public Users(String email, String password, genero gen, Integer altura, Double peso, LocalDateTime data, String desporto){
        this.email = email;
        this.password = password;
        this.genero = gen;
        this.altura = altura;
        this.peso = peso;
        this.data_nascimento = data;
        this.desporto_fav = desporto;
    }

    // setters
    public void setEmail(String email) { this.email = email; }
    public void setPassword(String password){ this.password = password; }
    public void setGenero(genero gen){ this.genero = gen; }
    public void setAltura(Integer altura){ this.altura = altura; }
    public void setPeso(Double peso){ this.peso = peso; }
    public void setData_Nascimento(LocalDateTime data){ this.data_nascimento = data; }
    public void setDesporto_Fav(String desporto_fav){ this.desporto_fav = desporto_fav; }

    // getters
    public String getEmail(){ return this.email; }
    public String getPassword(){ return this.password; }
    public genero getGenero(){ return this.genero; }
    public Integer getAltura(){ return this.altura; }
    public Double getPeso(){ return this.peso; }
    public LocalDateTime getData_Nascimento(){ return this.data_nascimento; }
    public String getDesporto_Fav(){ return this.desporto_fav; }

    // equals, clone e toString

    public boolean equals(Object obj){
        if(this==obj) return true;
        if(obj==null||obj.getClass()!=this.getClass()) return false;
        Users u = (Users) obj;
        return (this.email == u.getEmail() && this.password == u.getPassword()
                && this.genero == u.getGenero() && this.altura == u.getAltura()
                && this.peso == u.getPeso() && this.data_nascimento == u.getData_Nascimento()
                && this.desporto_fav == u.getDesporto_Fav());
    }

    public Users clone(){
        return new Users(this);
    }

    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Email do utilizador: \n");
        sb.append(this.email);
        sb.append("Password do utilizador: \n");
        sb.append(this.password);
        sb.append("Genero do utilizador: \n");
        sb.append(this.genero);
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
