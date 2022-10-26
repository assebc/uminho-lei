import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Barrier {
    private int n;
    private int counter;

    private int wave;
    private ReentrantLock l = new ReentrantLock();
    private Condition condition = l.newCondition();

    Barrier (int N){
        this.n = N;
        this.counter = 0;
        this.wave = 0;
    }

    void await() throws InterruptedException{
        l.lock();
        this.counter++;

        if(this.counter < this.n){
            int atm_wave = this.wave;
            while(this.wave==atm_wave)
                condition.await();
        } else{
            condition.signalAll();
            this.wave++;
            this.counter = 0;
        }

        l.unlock();
    }
    // .await() ALL
    // .signalAll() go
}
class Runner implements Runnable{

    private Barrier b;
    private int n;

    public Runner(Barrier b, int nThreads){
        this.b = b;
        this.n = nThreads;
    }

    @Override
    public void run() {
        try{
            Thread.sleep(1000+this.n);
        } catch(InterruptedException e){
            e.printStackTrace();
        }
        System.out.println(Thread.currentThread().getName() + " Yupi");
    }
}
class BarrierMain {
    public static void main(String[] args) {
        int nThreads = 10;
        Barrier b = new Barrier(nThreads);
        Runner r = new Runner(b,nThreads);
        Thread[] threads = new Thread[nThreads];
        Thread t = new Thread(() -> {
            System.out.println("Doing my stuff...");
            try{
                Thread.sleep(100);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            try {
                b.await();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }

        });


    }
}
