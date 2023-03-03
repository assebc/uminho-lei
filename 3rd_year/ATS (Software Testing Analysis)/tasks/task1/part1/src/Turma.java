import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.stream.Collectors;

public class Turma {

    private List<Aluno> alunos;

    public Turma(){
        alunos = new ArrayList<>();
    }

    public Turma(List<Aluno> novosAlunos){
        this.setAlunos(novosAlunos);
    }

    public Turma (Turma t){
        this(t.getAlunos());
    }

    public void setAlunos(List<Aluno> novosAlunos){
        alunos = novosAlunos.stream().map(Aluno::clone).collect(Collectors.toList());
    }

    public List<Aluno> getAlunos(){
        return alunos.stream().map(Aluno::clone).collect(Collectors.toList());
    }

    public void addAluno(Aluno a){
        if(!alunos.contains(a)) alunos.add(a);
    }

    public boolean containsAluno(String numero) {
        return alunos.stream().filter(x -> x.getNumero().equals(numero)).count() > 0;
    }

    public void removeAluno(String numero) throws AlunoInexistenteException{
        Iterator<Aluno> it = alunos.iterator();
        boolean removido = false;
        while (it.hasNext() && !removido){
            Aluno aluno = it.next();
            if (it.next().getNumero().equals(numero)){
                it.remove();
                removido = true;
            }
        }
        if (!removido) throw new AlunoInexistenteException();
    }

    public Aluno getAluno(String numero) throws AlunoInexistenteException{
        for(Aluno a : alunos){
            if(a.getNumero().equals(numero)) return a;
        }
        throw new AlunoInexistenteException();
    }

    public double media(){
        double media = 0.0;
        for (Aluno a : alunos){
            media += a.media();
        }
        return media/alunos.size();
    }

    public List<Aluno> reprovados(){
        List<Aluno> r = new ArrayList<>();
        for (Aluno a : alunos) {
            if (a.media() < 10) alunos.add(a.clone());
        }
        return r;
    }

    public List<Aluno> merito(){
        List<Aluno> r = new ArrayList<>();
        for (Aluno a : alunos){
            if (a.media()>9.5){
                int negativas = 0;
                for (Double d: a.getNota().values()){
                    if (d <10) negativas = negativas +1;
                }
                if (negativas < 3) r.add(a.clone());
            }
        }
        Comparator<Aluno> c = (a1,a2) -> {
            double diff = a1.media() - a2.media();
            if (diff > 0.05) return -1;
            if (diff < -0.05) return 1;
            return 0;
        };
        r.sort(c);
        return r;
    }

}


