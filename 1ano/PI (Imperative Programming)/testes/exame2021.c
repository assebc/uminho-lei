#include <stdio.h>
#include <stdlib.h>

typedef struct lligada{
	int valor;
	struct lligada * prox;
} * LInt;

typedef struct nodo{
	int valor;
	struct nodo *pai, *esq, *dir;
}* ABin;

void swap(int v[], int i, int j){
	int tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}

int paresImpares(int v[], int N){
	int pares = 0;
	for(int i = 0;i<N-1;i++){
		for(int j = i+1;j<N;j++){
			if(v[i]%2!=0){
				if(v[j]%2==0){ 
					swap(v,i,j);
					pares++;
				}
			}
		}
	}
	return pares;
}


void merge(LInt *r, LInt a, LInt b){
	(*r) = NULL;
	while(a && b){
		if(a->valor<b->valor){
			(*r) = a;
			a = a->prox;
		}else{
			(*r) = b;
			b = b->prox;
		}
		r = &((*r)->prox);
	}
	if(a) (*r) = a;
	if(b) (*r) = b;
}

void insertOrd(LInt * head, int x){
	LInt add = malloc(sizeof(struct lligada));
	add->valor = x;
	add->prox = NULL;
	if (!(*head)) (*head) = add;
	if((*head)->valor>x) {
		add->prox = (*head);
		(*head) = add;
		return;
	}
	LInt l = *head;	
	while(l->prox){

		if(l->prox->valor >x){
			add->prox = l->prox;
			l->prox = add;
			return;
		}
		l = l->prox;
	}
	l->prox = add;

}

void printL(LInt *r){
	LInt aux = (*r);
	while(aux->prox) { printf("%d ", aux->valor); aux = aux->prox;}
	printf("%d\n",aux->valor);
}

void latino(int N, int m[N][N]){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			m[i][j] = ((j+i)%N)+1;
		}
	}
}

void printM(int N, int m[N][N]){
	for(int x = 0 ; x < N ; x++) {
        printf(" (");
        for(int y = 0 ; y < N ; y++){
            printf("%d     ", m[x][y]);
        }
        printf(")\n");
    }
}

ABin next(ABin a){
	ABin r = NULL;
	if(a){
		if(a->dir){ 
			a = a->dir;
			while(a->esq) a = a->esq;
			r = a;
		}
		else if (a->pai && (a->pai)->esq == a) r = a->pai;
		else if (a->pai && (a->pai)->dir == a){
			while(a && a->pai && (a->pai)->dir == a){
				a = a->pai;
			}
			if(a && a->pai) r = a->pai;
		}
	} else return NULL;

	return r;
}

int main(){

	int v[5] = {1,2,4,3,1};
	int pares = paresImpares(v,5);
	printf("Tem %d pares!\n",pares);
	for(int i = 0;i<5;i++) printf("%d ", v[i]);
	printf("\n\n");

	LInt init = malloc(sizeof(struct lligada));
	LInt * r = &init;
	LInt a = malloc(sizeof(struct lligada));
	a->valor = 1;
	a->prox = NULL;
	LInt b = malloc(sizeof(struct lligada));
	b->valor = 2;
	b->prox = NULL;
	insertOrd(&b,11);
	insertOrd(&a,5);
	insertOrd(&b,7);
	insertOrd(&a,16);
	insertOrd(&b,13);
	insertOrd(&a,12);
	insertOrd(&b,19);
	insertOrd(&a,4);
	insertOrd(&b,3);
	printL(&a); // 1 4 5 12 16 
	printL(&b); // 2 3 11 13 19
	merge(r,a,b);
	printL(r); // 1 2 3 4 5 11 12 13 16 19

	printf("\n");

	int m[3][3];
	latino(3,m);
	printM(3, m);

	return 0;
}