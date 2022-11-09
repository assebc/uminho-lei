import java.util.concurrent.locks.ReentrantLock;
import java.util.Map;
import java.util.HashMap;
import java.util.concurrent.locks.Condition;

class Votar implements Votacao{

    private int num_escolhas;
    private int[] vote;
    private Map<Integer,Integer> num_votes = new HashMap<>();
    private ReentrantLock lock = new ReentrantLock();
    private Condition condition = lock.newCondition();

    public Votar(int N){
        this.num_escolhas = N;
    }

    class Pessoa{
        private ReentrantLock lockP = new ReentrantLock();
        private int id;

        public Pessoa(int id){
            this.id = id;
        }
    }

    class Cabine{
        private ReentrantLock lockC = new ReentrantLock();
        private int num_cabine;
        private boolean[] ocupado;

        public Cabine(int N){
            this.num_cabine = N;
            this.ocupado = new boolean[N];
            for(int j = 0;j<N;j++) this.ocupado[j] = false;
        }
    }

    public boolean verifica(int identidade){
        this.lock.lock();
        try{
            for(int i=0;i<this.num_escolhas;i++){
                if (this.vote[i]==identidade) return true;
            }
            return false;
        } finally{
            this.lock.unlock();
        }       
    }


    @Override
    public void vota(int escolha){
        this.lock.lock();
        try{
            if (this.num_votes.containsKey(escolha))
                this.num_votes.putIfAbsent(escolha, 1);
            else this.num_votes.put(escolha,this.num_votes.get(escolha)+1);
        } finally{
            this.lock.unlock();
        }
    }

    @Override
    public int esperaPorCabine() {
        
        return 0;
    }

    @Override
    public void desocupaCabine(int i) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public int vencedor(){ // apenas para a alinea de Valorização
        return 0;
    }
}




