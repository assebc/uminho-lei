class Increment implements Runnable {
    public void run() {
        final long I=100;

        for (long i = 0; i < I; i++)
            System.out.println(i);
    }
}

class MainEx1{

    public static void main(String[] args) throws InterruptedException {
        final int N = 10;
        Thread [] ts = new Thread[N];

        // criação N threads
        for(int i = 0;i<N;i++){
            ts[i] = new Thread(new Increment());
        }

        // iniciação de N threads
        for(int j=0;j<N;j++){
            ts[j].start();
        }

        // bloquear main até threads operarem até terminar
        for(int j=0;j<N;j++){
            ts[j].join();
        }

        // main thread
        System.out.println("Fim");
    }
}