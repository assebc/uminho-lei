#include <stdio.h>
#include <stdlib.h>

/* BUBBLE SORT || order a list min to max */

/* changing positions */

void swap(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
/* implement bubble sort */

void bubbleSort(int arr[], int n){
  int i, j;
  for (i=0;i<n-1;i++){   
    // Last i elements are already in place  
    for (j=0;j<n-i-1;j++){
      if (arr[j]>arr[j+1])
        swap(&arr[j], &arr[j+1]);
    }
  }
}

/* TEST 20/21 */

/*
1.
Relembre a seguinte função que calcula um somatório. Modifique-a por forma a que, para um n
arbitrário, em vez da soma, devolva a 100ª menor parcela do somatório ou -1 caso haja menos do
que 100 parcelas
*/
int sumhtpo(int n){
  int r = 0;
  while (n != 1) {
    r += n;
    if (n%2 == 0) n = n/2; 
    else n = 1+(3*n);
  }
  return r;
}

int mysumhtpo(int n){
  int r = 0;
  int array[10000];
  int conta = 0;

  while (n != 1){
    array[conta] = n;
    conta++;
    if (n%2 == 0) n = n/2;
    else n = 1+(3*n);     
  }
  bubbleSort(array, conta);
  if(conta < 100) r = -1;
  else r = array[99];

  return r;
}

/*
2.
A moda de um (multi-)conjunto é o valor que ocorre mais frequentemente nesse conjunto. Se
houver mais do que um valor com a mesma frequência mais elevada, o conjunto diz-se multimodal.
Implemente uma função int moda(int v[], int N, int *m) por forma a calcular (em *m) a
moda de um conjunto de N inteiros armazenado no array v, devolvendo a respectiva frequência. Se
não for possível determinar univocamente a moda, quando o conjunto é vazio ou multimodal, deve
devolver 0.
*/

int moda(int v[], int N, int *m){
  int maxValue = 0, maxCount = 0, i, j, r = 1;

  for (i=0;i<N;i++){
    int count = 0;
    for (j=0;j<N;j++){
      if (v[j] == v[i])
      count++;
    }

    if (count > maxCount){
      maxCount = count;
      maxValue = v[i];
      m[0] = maxCount;
      r = maxValue;
    }
    else if (count == maxCount)
      r = 0;
  }
  if (r == 0) return r;
  else return maxValue;
}

/*
3.
Defina uma função int procura (LInt *l, int x) que procura um inteiro numa lista de
inteiros. A função deve retornar 0 se o elemento não existir. Se o elemento existir, a função deve
retornar 1 e passar esse elemento para o início da lista.
*/

typedef struct slist {
    int valor;
    struct slist * prox;
} *LInt;

int procura(LInt *l, int x){
  int r = 0, count = 0;
  LInt aux = *l;
  LInt aux2 = *l;
  while (aux->prox != NULL){
    if (aux->valor == x){
      r = 1;
      count++;
      (*l)->valor = x;
      while((*l)->prox->valor != x){
        (*l) = (*l)->prox;
      }
      (*l)->prox->valor = aux2->valor;
      return r;
    }
    else count ++;
    aux = aux->prox;
  }

  return r;
}

/*
4.
Defina uma função int freeAB(ABin a) que dado um apontador para a raiz da árvore liberta todo
o espaço de memória ocupado pela mesma, retornando o número de nodos libertados
*/

typedef struct nodo {
  int valor;
  struct nodo *pai, *esq, *dir;
} *ABin;

int freeAB(ABin a){
  int c = 0;
  if (a == NULL)
    return c;
  else {
    c = 1;
    while(a->pai != NULL){
      a = a->pai;
    }
    c += freeAB(a->esq);
    c += freeAB(a->dir);
    
  }
  return c;
  free(a);
}

/*
5.
Defina uma função void caminho(ABin a) que dado um apontador para um nodo qualquer de
uma árvore binária com pais (tal como definida na questão anterior) imprime qual o caminho a
seguir para ir da raiz até esse nodo (uma sequência de direções, “esq” ou “dir”, uma por linha)
*/

void caminho(ABin a){
  int x = a->valor;
  while(a->pai != NULL){
      a = a->pai;
  }
  if (a->valor < x){
    a = a->dir; printf("%s\n", "dir\0");
  } else if (a->valor > x) {
    a = a->esq; printf("%s\n", "esq\0");
  } else caminho(a);
}

/* MAIN */
int main(){

  return 0;
} 