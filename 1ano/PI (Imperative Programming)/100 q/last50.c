#include <stdio.h>
#include <stdlib.h>

typedef struct lligada{
	int valor;
	struct lligada *prox;
} * LInt;

typedef struct node{
	int valor;
	struct node *left, *right;
} * ABin;

int length(LInt l){
	int n = 0;
	while(l){
		n++;
		l = l->prox;
	}
	return n;
}

void freeL(LInt l){
	while(l){
		LInt tmp = l;
		l = l->prox;
		free(tmp);
	}
}

void imprimeL(LInt l){
	while(l){
		printf("%d\n", l->valor);
		l=l->prox;
	}
}

LInt reverseL(LInt l){
	LInt prox = l->prox;
	l->prox = NULL;
	while(prox){
		LInt tmp = prox->prox;
		prox->prox = l;
		l = prox;
		prox = tmp;
	}
	return l;
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

int removeOneOrd(LInt * head, int x){

	if(!(*head)) return 1;
	if((*head)->valor == x) (*head) = (*head)->prox;
	LInt l = (*head);
	while(l->prox){
		if(l->prox->valor == x){
			LInt tmp = l->prox;
			l->prox = l->prox->prox;
			free(tmp);
			return 0;
		}
		if(l->prox->valor>x) return 1;
		l = l->prox;
	}
	return 0;
}

void merge(LInt* r, LInt a, LInt b) {
    if(!a && !b) return;
    if((!b || a) && (a->valor < b->valor)) {
        (*r) = a;
        merge(&((*r)->prox),a->prox,b);
    }
    else {
        (*r) = b;
        merge(&((*r)->prox),a,b->prox);
    }
}

int removeAll(LInt *l, int x) {
    int rem = 0;
    LInt prev = NULL;
    while(*l) {
        if((*l)->valor == x) {
            if(!prev) (*l) = (*l)->prox;
            else prev->prox = (*l)->prox;
            rem++;
        }
        else {
            prev = (*l);
            l = &((*l)->prox);
        }
    }
    return rem;
}

int main(){

	LInt l = malloc(sizeof(struct lligada));
	LInt l2 = malloc(sizeof(struct lligada));
	l->valor = 10;
	l2->valor = 13;
	l2->prox = NULL;
	l->prox = l2;
	LInt * head_red = &l;
	insertOrd(head_red, 12);
	insertOrd(head_red, 9);
	insertOrd(head_red, 15);
	insertOrd(head_red, 15);
	insertOrd(head_red, 15);
	insertOrd(head_red, 15);

	imprimeL(*head_red);

	printf("\n");

	removeOneOrd(head_red, 12);
	removeOneOrd(head_red, 9);
	removeOneOrd(head_red, 15);

	imprimeL(*head_red);

	printf("\n");

	LInt a = malloc(sizeof(struct lligada));
	LInt b = malloc(sizeof(struct lligada));
	LInt start = malloc(sizeof(struct lligada));
	a->valor = 5;
	a->prox = NULL;
	b->valor = 7;
	b->prox = NULL;
	start->valor = 1;
	start->prox = NULL;
	LInt * ref = &start;
	merge(ref,a,b);

	imprimeL(*ref);

	printf("\n");

	imprimeL(*head_red);
	printf("\n");
	int num = removeAll(head_red,15);
	printf("Foram removidos %d números!\n", num);
	imprimeL(*head_red);

	return 0;
}