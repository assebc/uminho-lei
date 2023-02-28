import java.util.HashMap;
import java.util.Map;

public class Aluno {

    private String name;
    private String number;
    private Map<String,Integer> notas;

    public Aluno(){
        this.name = "";
        this.number = "";
        this.notas = new HashMap<>();
    }
    public Aluno(String nome){
        this.name = nome;
        this.number = "";
        this.notas = new HashMap<>();
    }

    public Aluno(String nome, String numb){
        this.name = nome;
        this.number = numb;
        this.notas = new HashMap<>();
    }

    public void setNome(String name) {
        this.name = name;
    }

    public String getNome() {
        return this.name;
    }

    public void setNumero(String num){
        this.number = num;
    }
    public String getNumero(){
        return this.number;
    }

    public void setNota(String uc, int plus) throws NotaInvalidaException {
        if(plus >=0 && plus <= 20) this.notas.put(uc,plus);
        else throw new NotaInvalidaException();
    }

    public int getNota(String uc){
        return this.notas.get(uc);
    }
    public void incrementaNota(String uc, int plus) throws NotaInvalidaException {
        if(this.notas.get(uc)+plus<= 20 && this.notas.get(uc)+plus>=0)
            this.notas.put(uc,this.notas.get(uc)+plus);
        else throw new NotaInvalidaException();

    }

    @Override
    public Aluno clone(){
        Aluno a = new Aluno(this.getNome());
        for(String key : this.notas.keySet()){
            a.notas.put(key,this.getNota(key));
        }
        return a;
    }

    public double media() {
        Integer atm = 0;
        for(Integer nota: this.notas.values()){
            atm += nota;
        }
        return atm/this.notas.values().size();
    }
}
