import java.util.*;
import java.util.concurrent.locks.ReentrantLock;

class Bank {

    private ReentrantLock lockBanco = new ReentrantLock();
    private static class Account {

        private ReentrantLock lock = new ReentrantLock();
        private int balance;
        Account(int balance) { this.balance = balance; }
        int balance() { return balance; }
        boolean deposit(int value) {
            balance += value;
            return true;
        }
        boolean withdraw(int value) {
            if (value > balance)
                return false;
            balance -= value;
            return true;
        }
    }

    private Map<Integer, Account> map = new HashMap<Integer, Account>();
    private int nextId = 0;

    // create account and return account id
    public int createAccount(int balance) {
        this.lockBanco.lock();
        Account c;
        int id;
        try{
            c = new Account(balance);
            id = nextId;
            nextId += 1;
            map.put(id, c);
        } finally {
            this.lockBanco.unlock();
        }
        return id;
    }

    // close account and return balance, or 0 if no such account
    public int closeAccount(int id) {
        this.lockBanco.lock();
        Account c;
        try {
            c = map.remove(id);
            if (c == null)
                return 0;
            c.lock.lock();
        } finally {
            this.lockBanco.unlock();
        }
        try{
            return c.balance();
        } finally {
            c.lock.unlock();
        }
    }

    // account balance; 0 if no such account
    public int balance(int id) {
        this.lockBanco.lock();
        Account c;
        try {
            c = map.get(id);
            if (c == null)
                return 0;
            c.lock.lock();
        }finally{
            this.lockBanco.unlock();
        }
        try {
            return c.balance();
        }finally {
            c.lock.unlock();
        }
    }

    // deposit; fails if no such account
    public boolean deposit(int id, int value) {
        this.lockBanco.lock();
        Account c;
        try {
            c = map.get(id);
            if (c == null) {
                return false;
            }
            c.lock.lock();
        } finally {
            this.lockBanco.unlock();
        }
        try {
            return c.deposit(value);
        } finally {
            c.lock.unlock();
        }
    }

    // withdraw; fails if no such account or insufficient balance
    public boolean withdraw(int id, int value) {
        this.lockBanco.lock();
        Account c;
        try{
            c = map.get(id);
            if (c == null)
                return false;
            c.lock.lock();
        } finally {
            this.lockBanco.lock();
        }
        try {
            return c.withdraw(value);
        } finally {
            c.lock.unlock();
        }
    }

    // transfer value between accounts;
    // fails if either account does not exist or insufficient balance
    public boolean transfer(int from, int to, int value) {
        this.lockBanco.lock();
        Account cfrom, cto;
        try {
            cfrom = map.get(from);
            cto = map.get(to);
            if (cfrom == null || cto == null)
                return false;
            cfrom.lock.lock();
            cto.lock.lock();
        } finally {
            this.lockBanco.unlock();
        }
        try {
            return cfrom.withdraw(value) && cto.deposit(value);
        }finally {
            cfrom.lock.unlock();
            cto.lock.unlock();
        }
    }

    // sum of balances in set of accounts; 0 if some does not exist
    public int totalBalance(int[] ids) {
        int total = 0;
        this.lockBanco.lock();
        Account c;
        try{
            for(int i : ids) {
                c = map.get(i);
                if (c == null)
                    return 0;
                c.lock.lock();
            }
        } finally {
            this.lockBanco.unlock();
        }
        for(int i:ids){
            c = map.get(i);
            try{
                total += c.balance();
            } finally {
                c.lock.unlock();
            }
        }
        return total;
    }
}