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
  
  // public Map<String,Product> getMap(){
  //   return this.map;
  // }

  private Product get(String item) {
    Product p = map.get(item);
    if (p != null) return p;
    p = new Product();
    map.put(item, p);
    return p;
  }

  // public int getAmmount(String item){
  //   return get(item).quantity;
  // }

  public void supply(String item, int quantity) {
    Product p = get(item);
    int quant = p.quantity;
    p.quantity += quantity;
    if(quant==0) condition.signalAll();
  }

  public void consume(Set<String> items) throws InterruptedException {
    this.lock.lock();
    for (String s : items){
      while(get(s).quantity==0){
        condition.await();
      }
      get(s).quantity--; 
    }
    this.lock.unlock();
  }
}

// class Runner implements Runnable{
  
//   private Warehouse w;
//   int n;

//   public Runner(Warehouse ws, int nthreads){
//     this.w = ws;
//     this.n = nthreads;
//   }
  
//   @Override
//   public void run() {
//     for(String s:this.w.getMap().keySet()){

//       if(this.w.getAmmount(s)==0) System.out.println(s + "ran out of products " + "detected by Thread " + Thread.currentThread().getName());
//     }
//   }
// }

// class Warehouse_Main{
//   public static void main(String[] args) throws InterruptedException {
//     final int N = 3;
//     Thread [] ts = new Thread[N];
//     Warehouse w = new Warehouse();

//     // criação N threads
//     for(int i = 0;i<N;i++){
//         ts[i] = new Thread(new Runner(w,N));
//     }

//     // iniciação de N threads
//     for(int j=0;j<N;j++){
//         ts[j].start();
//     }

//     // bloquear main até threads operarem até terminar
//     for(int j=0;j<N;j++){
//         ts[j].join();
//     }

//   }
// }