import java.util.concurrent.locks.ReentrantLock;

class Bank {

    private static class Account {
        private int balance;

        private ReentrantLock lock = new ReentrantLock();
        Account(int balance) { this.balance = balance; }
        int balance() { return balance; }
        boolean deposit(int value) {
            try{
                lock.lock();
                balance += value;
                return true;
            } finally {
                lock.unlock();
            }
        }
        boolean withdraw(int value) {
            try {
                lock.lock();
                if (value > balance)
                    return false;
                balance -= value;
                return true;
            } finally {
                lock.unlock();
            }
        }
    }

    // Bank slots and vector of accounts
    private int slots;
    private Account[] av;

    public Bank(int n)
    {
        slots=n;
        av=new Account[slots];
        for (int i=0; i<slots; i++) av[i]=new Account(0);
    }

    // Account balance
    public int balance(int id) {
        try{
            if (id < 0 || id >= slots) {
                return 0;
            }
            av[id].lock.lock();
            return av[id].balance();
        } finally {
            av[id].lock.unlock();
        }
    }

    // Deposit
    boolean deposit(int id, int value) {
        try{
            if (id < 0 || id >= slots)
                return false;
            av[id].lock.lock();
            return av[id].deposit(value);
        } finally {
            av[id].lock.unlock();
        }
    }

    // Withdraw; fails if no such account or insufficient balance
    public boolean withdraw(int id, int value) {
        try {
            if (id < 0 || id >= slots)
                return false;
            av[id].lock.lock();
            return av[id].withdraw(value);
        } finally {
            av[id].lock.unlock();
        }
    }

    public boolean transfer(int from, int to, int value){
        boolean b = false, b1 = true;
        if (from > to){
            av[from].lock.lock();
            b = withdraw(from, value);
            av[to].lock.lock(); // diminuir tempo entre libertação de locks
            av[from].lock.unlock();
            b1 = deposit(to, value);
            av[to].lock.unlock();
        } else{
            av[to].lock.lock();
            b = deposit(from, value);
            av[from].lock.lock();
            av[to].lock.unlock();
            b1 = withdraw(to, value);
            av[from].lock.unlock();
        }
        return b && b1;
    }

    public int totalBalance(){
        // lock needed
        int tot = 0;
        try{
            for(int i = 0;i<slots;i++){
                av[i].lock.lock();
            }
            for(int i = 0;i<slots;i++){
                tot += balance(i);
            }
            return tot;

        }finally {
            for(int i = 0;i<slots;i++){
                av[i].lock.unlock();
            }
        }
    }
}