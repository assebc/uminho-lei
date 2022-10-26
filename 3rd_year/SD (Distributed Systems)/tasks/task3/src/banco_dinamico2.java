import java.util.*;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

class Bank2 {

    private ReentrantReadWriteLock lockBanco = new ReentrantReadWriteLock();
    private ReentrantReadWriteLock.WriteLock writeLock = lockBanco.writeLock();
    private ReentrantReadWriteLock.ReadLock readLock = lockBanco.readLock();

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
        this.writeLock.lock();
        Account c = new Account(balance);
        int id = nextId;
        nextId += 1;
        map.put(id, c);
        this.writeLock.unlock();
        return id;
    }

    // close account and return balance, or 0 if no such account
    public int closeAccount(int id) {
        this.writeLock.lock();
        Account c = map.remove(id);
        if (c == null) return 0;
        c.lock.lock();
        this.writeLock.unlock();
        try{
            return c.balance();
        } finally {
            c.lock.unlock();
        }
    }

    // account balance; 0 if no such account
    public int balance(int id) {
        this.readLock.lock();
        Account c = map.get(id);
        if (c == null) return 0;
        c.lock.lock();
        this.readLock.unlock();
        try {
            return c.balance();
        }finally {
            c.lock.unlock();
        }
    }

    // deposit; fails if no such account
    public boolean deposit(int id, int value) {
        this.readLock.lock();
        Account c = map.get(id);
        if (c == null) return false;
        c.lock.lock();
        this.readLock.unlock();
        try {
            return c.deposit(value);
        } finally {
            c.lock.unlock();
        }
    }

    // withdraw; fails if no such account or insufficient balance
    public boolean withdraw(int id, int value) {
        this.readLock.lock();
        Account c = map.get(id);
        if (c == null) return false;
        c.lock.lock();
        this.readLock.lock();

        try {
            return c.withdraw(value);
        } finally {
            c.lock.unlock();
        }
    }

    // transfer value between accounts;
    // fails if either account does not exist or insufficient balance
    public boolean transfer(int from, int to, int value) {
        this.readLock.lock();
        Account cfrom = map.get(from), cto = map.get(to);
        if (cfrom == null || cto == null) return false;
        cfrom.lock.lock();
        cto.lock.lock();
        this.readLock.unlock();
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
        this.readLock.lock();
        Account c;
        for(int i : ids) {
            c = map.get(i);
            if (c == null) return 0;
            c.lock.lock();
        }
        this.readLock.unlock();

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