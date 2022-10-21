import java.util.Random;

class Mover implements Runnable {
    Bank b;
    int s; // Number of accounts
    int [] id;
    public Mover(Bank b, int s) { this.b=b; this.s=s; for(int i=0;i<s;i++) id[i] = i;}

    public int [] getIds() {
        return id;
    }

    public void run() {
        final int moves=100000;
        int from, to;
        Random rand = new Random();

        for (int m=0; m<moves; m++)
        {
            from=rand.nextInt(s); // Get one
            while ((to=rand.nextInt(s))==from); // Slow way to get distinct
            b.transfer(from,to,1);
        }
    }
}

class Observer implements Runnable {
    private Bank b;
    private int expectedBalance;

    public Observer(Bank b, int expectedBalance) {
        this.b = b;
        this.expectedBalance = expectedBalance;
    }

    @Override
    public void run() {
        final int balanceOperations = 100000;
        Bank b = new Bank();
        Mover m = new Mover(b,10);
        for (int i = 0; i < balanceOperations; i++) {
            int currentBalance = b.totalBalance(m.getIds());
            if (currentBalance != this.expectedBalance) {
                throw new RuntimeException("Unexpected balance: " + currentBalance);
            }
        }
    }
}

class BankTest {
    public static void main(String[] args) throws InterruptedException {
        final int N = 10;

        Bank b = new Bank();
        Mover m = new Mover(b,N);
        for (int i = 0; i < N; i++){
            b.createAccount(1000);
            b.deposit(i, 1000);
        }
        
        int initialBalance = b.totalBalance(m.getIds());
        System.out.println(initialBalance);

        Thread t1 = new Thread(new Mover(b, 10));
        Thread t2 = new Thread(new Mover(b, 10));
        Thread t3 = new Thread(new Observer(b, initialBalance));

        t1.start();
        t2.start();
        t3.start();

        t1.join();
        t2.join();
        t3.join();

        System.out.println(b.totalBalance(m.getIds()));
    }
}