import java.time.LocalDate;
import java.time.temporal.ChronoUnit;

public class Corrida extends Atividade {
    private int distancia;
    private int altimetria;
    private String percurso;
    private int pontos;

    public Corrida(){
        super();
        this.distancia = 0;
        this.altimetria = 0;
        this.percurso = "";
    }

    public Corrida(String codigo, String descricao, LocalDate data, int duracao, int distancia, int altimetria, String precurso) {
        super(codigo, descricao, data, duracao);
        this.distancia = distancia;
        this.altimetria = altimetria;
        this.percurso = precurso;
    }

    public Corrida(Corrida outro) {
        super(outro);
        this.distancia = outro.getDistancia();
        this.altimetria = outro.getAltimetria();
        this.percurso = outro.getPercurso();
    }

    public int getDistancia() {
        return distancia;
    }

    public void setDistancia(int distancia) {
        this.distancia = distancia;
    }

    public int getAltimetria() {
        return altimetria;
    }

    public void setAltimetria(int altimetria) {
        this.altimetria = altimetria;
    }

    public String getPercurso() {
        return percurso;
    }

    public void setPercurso(String precurso) {
        this.percurso = precurso;
    }

    public double calorias() {
        long idade =  ChronoUnit.YEARS.between(LocalDate.now(), getUser().getData_Nascimento());
        double calorias =distancia*getUser().getPeso()*getDuracao()*idade/50;
        return calorias;
    }


    public Atividade clone() {
        return new Corrida(this);
    }


    public String toString() {
        return "Corrida{" +
                super.toString()+
                "distancia=" + distancia +
                ", altimetria=" + altimetria +
                ", precurso='" + percurso + '\'' +
                '}';
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        Corrida corrida = (Corrida) o;
        return Double.compare(corrida.getDistancia(), getDistancia()) == 0
                && Double.compare(corrida.getAltimetria(), getAltimetria()) == 0
                && this.percurso.equals(corrida.getPercurso());
    }

    @Override
    public void setpontos() {
        this.pontos = this.distancia*10;
    }

    @Override
    public int getpontos() {
        return 0;
    }
}