#include <stdio.h>
#include <stdlib.h>

typedef struct lligada{
  int valor;
  struct lligada * prox;
} * LInt;

typedef struct nodo{
  int valor;
  struct nodo *pai, *esq, *dir;
} * ABin;

void swap_shift(int tmp,int val[],int ind,int N){
    for(int i=N-1;i>ind;i--)
		val[i]=val[i-1];
    val[ind]=tmp;
}

void insertOrd(int n, int val[], int N){
	for(int i = 0;i<N;i++){
		if(val[i]==0){
			val[i] = n;
			return;
		}

		if(n<val[i]){
			int tmp = val[i];
			val[i] = n;
			swap_shift(tmp,val,i+1,N);
			return;
		}
	}
	
}

void printArray(int val[], int N){ 
	for(int i = 0;i<N;i++){
		if(i!=N-1) printf("%d, ", val[i]);
		else printf("%d\n", val[i]);
	}
}

int sumhtpo2(int n){
	int val[100];
	if(n==1) return -1;
	int num = 0;
	while(n!=1){
		insertOrd(n,val,100);
		//printf("%d\n", n); 
		if(n%2 == 0) n = n/2; 
		else n = 1+(3*n);
		num++;
	}
	//printf("\n%d\n",num);
	//for(int i = 0;i<100;i++) printf("%d, ", val[i]);
	if(num<100) return -1;
	return val[99];
	
}

int moda(int v[], int N, int *m){
	if(!v) return 0;
	int mode, max =0,k=0;
	for (int i = 0; i < N - 1; i++){
        mode = 1;
        for (int j = i + 1; j < N; j++){
            if (v[i] == v[j]) {
                mode++;
            }
        }
        if ((mode > max)) {
            k = 1;
            max = mode;
        }
        else if (mode == max) k++;   
    }
    *m = max;
    if(k>1) return 0;
    return max;
}

int procura(LInt * l, int x){
	LInt aux = *l;
	LInt prev;
	while(aux->prox){
		if(aux->prox->valor==x){
			prev = aux->prox;
			aux->prox = aux->prox->prox;
			prev->prox = (*l);
			(*l) = prev;
			return 1;
		}
		aux = aux->prox;
	}
	return 0;
}

int freeABaux(ABin a, int num){
	if(!a->esq && a->dir){
		ABin aux = a;
		a = a->dir;
		a->pai = NULL;
		free(aux); num++;
		num = freeABaux(a,num);
	} else if(a->esq && !a->dir){
		ABin aux = a;
		a = a->esq;
		a->pai = NULL;
		free(aux); num++;
		num = freeABaux(a,num);
	} else{
		ABin aux = a;
		free(aux); num++;
		a->esq->pai = NULL; a->dir->pai = NULL;
		num = freeABaux(a->esq,num) + freeABaux(a->dir,num);
	}
	return num;
}

int freeAB(ABin a){
	if(!a) return 0;
	if(!a->esq && !a->dir){ABin aux = a; a = NULL; free(aux); return 1;} 
	int num = 0;
	return freeABaux(a,num);
}

void caminho(ABin a){
	while(a->pai){
		int tmp = a->valor;
		a = a->pai;
		if(a->esq->valor == tmp) printf("esq\n");
		else printf("dir\n");
	}
	
}

int main(){

	int n = sumhtpo2(10);
	if(n!=(-1))printf("A 100º parcela é %d!\n",n);
	else printf("Não existe 100º parcela!\n");
	int * m = malloc(sizeof(int));
	int v[5];
	v[0] = 10;
	v[1] = 10;
	v[2] = 11;
	v[3] = 5;
	v[4] = 12;
	printf("%d\n", moda(v, 5,m));

	return 0;
}