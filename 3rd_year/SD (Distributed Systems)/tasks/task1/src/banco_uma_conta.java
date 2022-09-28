import java.util.concurrent.locks.ReentrantLock;

class Bank {
    private static class Account {
        private int balance;
        Account(int balance) { this.balance = balance; }
        int balance() { return balance; }
        boolean deposit(int value) {
            balance += value;
            return true;
        }
    }

    // Our single account, for now
    private Account savings = new Account(0);

    // Account balance
    public int balance() {
        return savings.balance();
    }

    // Deposit
    boolean deposit(int value) {
        return savings.deposit(value);
    }
}

class Deposits implements Runnable{
    final int I = 1000;
    final int V = 100;

    Bank b = new Bank();

    public int balance(){ return b.balance();}

    public void run(){
        for(int i = 0;i<I;i++){
            b.deposit(V);
        }
    }
}

class MainEx2{

    public static void main(String [] args) throws InterruptedException {
        final int N = 10;
        Thread [] ts = new Thread[N];
        Deposits d = new Deposits();
        for(int i = 0;i<N;i++){
            ts[i] = new Thread(d);
        }

        for(int i = 0;i<N;i++){
            ts[i].start();
        }

        for(int i=0;i<N;i++){
            ts[i].join();
        }

        System.out.println("balance: " + d.balance());


    }
}