package src;

import java.util.*;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

class Warehouse {
  private Map<String, Product> map =  new HashMap<String, Product>();
  private ReentrantLock lock = new ReentrantLock();
  private Condition condition = lock.newCondition();
  private class Product {
    int quantity = 0; 
  }

  private Product get(String item) {
    Product p = map.get(item);
    if (p != null) return p;
    p = new Product();
    map.put(item, p);
    return p;
  }

  public void supply(String item, int quantity) {
    Product p = get(item);
    int quant = p.quantity;
    p.quantity += quantity;
    if(quant==0) condition.signalAll();
  }

  public void consume(Set<String> items) throws InterruptedException {
    this.lock.lock();
    while(items.iterator().next()!=null){
      Product p = get(items.iterator().next());
      while(p.quantity==0) condition.await();
      p.quantity--;
    }
    this.lock.unlock();
  }
}