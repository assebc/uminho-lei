#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lligada {
    int valor;
    struct lligada *prox;
} *LInt;

// 1

int length(LInt l) {
    if(l == NULL) return 0;
    else return (1 + length(l->prox));
}

// 2

void freeL(LInt l) {
    while(l) {
        LInt temp = l;
        l = l->prox;
        free(temp);
    }
}

// 3

void imprimeL(LInt l) {
    while(l != NULL) {
        printf("%d\n",l->valor);
        l = l->prox;
    }
}

// 4

LInt reverseL(LInt l) {
    int len = length(l);
    LInt array[len];
    for(int i = 0; i < len; l = l->prox) array[i++] = l;
    for(int i = len - 1; i > 0; i--) array[i]->prox = array[i-1];
    array[0]->prox = NULL;
    return array[len - 1];
}

LInt reverseL2(LInt l) {
    LInt prox = l->prox;
    l->prox = NULL;
    while(prox) {
        LInt temp = prox->prox;
        prox->prox = l;
        l = prox;
        prox = temp;
    }
    return l;
}

// 5

void insertOrd (LInt* l, int x) {
    LInt new = malloc(sizeof(struct lligada));
    new->valor = x;
    new->prox = NULL;
    LInt prev = NULL;
    for(;*l && (*l)->valor < x; prev = (*l), l = &((*l)->prox));
    if(prev) {
        new->prox = (*l);
        prev->prox = new;
    }
    else {
        new->prox = (*l);
        *l = new;
    }
}

// 6

int removeOneOrd(LInt *l, int x) {
    LInt prev = NULL;
    for(;*l && x != (*l)->valor; prev = *l, l = &((*l)->prox));
    if(!(*l)) return 1;
    if(!prev) (*l) = (*l)->prox;
    else prev->prox = (*l)->prox;
    return 0;
}

int removeOneOrd2(LInt* l, int x) {
    if((*l)->valor == x) {
        LInt temp = (*l);
        (*l) = (*l)->prox;
        free(temp);
        return 0;
    }
    LInt prev = (*l);
    while(prev->prox) {
        LInt list = prev->prox;
        if(list->valor == x) {
            prev->prox = list->prox;
            free(list);
            return 0;
        }
        prev = prev->prox;
    }
    return 1;
}

// 7

void merge(LInt* r, LInt a, LInt b) {
    if(!a && !b) return;
    if((b == NULL || a != NULL) && (a->valor < b->valor)) {
        (*r) = a;
        merge(&((*r)->prox),a->prox,b);
    }
    else {
        (*r) = b;
        merge(&((*r)->prox),a,b->prox);
    }
}

// 8

void splitQS(LInt l, int x, LInt *mx, LInt *Mx) {
    if(!l) return;
    if(l->valor < x) {
        (*mx) = l;
        (*Mx) = NULL;
        splitQS(l->prox, x, &((*mx)->prox), Mx);
    }
    else {
        (*Mx) = l;
        (*mx) = NULL;
        splitQS(l->prox, x, mx, &((*Mx)->prox));
    }
}

// 9

LInt parteAmeio (LInt *l){
    int meio = length(*l)/2;
    if(meio == 0) return NULL;
    LInt y = (*l);
    LInt prev = NULL;
    for(int i = 0; i < meio; i++) {
        prev = (*l);
        (*l) = (*l)->prox;
    }
    prev->prox = NULL;
    return y;
}

// 10

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

// 11

int removeDups(LInt *l) {
    int rem = 0;
    for(;*l; l = &((*l)->prox)) {
        LInt prevAux = (*l), aux = (*l)->prox;
        for(; aux; aux = prevAux->prox) {
            if(aux->valor == (*l)->valor) {
                prevAux->prox = aux->prox;
                rem++;
                free(aux);
            }
            else prevAux = aux;
        }
    }
    return rem;
}

// 12

int removeMaiorL(LInt *l) {
    int max = (*l)->valor;
    LInt prev = NULL;
    LInt maxPrev = NULL;
    LInt maxL = (*l);
    LInt list = (*l);
    for(;list; list = list->prox) {
        if(list->valor > max) {
            maxPrev = prev;
            maxL = list;
            max = list->valor;
        }
        prev = list;
    }
    if(!maxPrev) (*l) = (*l)->prox;
    else maxPrev->prox = maxL->prox;
    return max;
}

// 13

void init (LInt *l) {
    LInt prev = NULL;
    for(;(*l)->prox;prev = *l, l = &((*l)->prox));
    if(!prev) {
        free(*l);
        *l = NULL;
    }
    else {
        prev->prox = NULL;
        free(*l);
    }
}

// 14

void appendL (LInt *l, int x) {
    LInt new = malloc(sizeof(struct lligada));
    new->valor = x;
    new->prox = NULL;
    if(!(*l)) (*l) = new;
    else {
        for(;(*l)->prox; l = &((*l)->prox));
        (*l)->prox = new;
    }
}

// 15

void concatL (LInt *a, LInt b) {
    if(*a) concatL(&((*a)->prox),b);
    else (*a) = b;
}

// 16

LInt cloneL(LInt l){
	if(!l) return NULL;
	LInt new = malloc(sizeof(struct lligada));
	new->valor = l->valor;
	new->prox = cloneL(l->prox);
	return new;
}

// 17

LInt cloneRev(LInt l){
	return reverseL(cloneL(l));
}

// 18

int maximo(LInt l){
	int max = l->valor;
	for(;l->prox;l=l->prox)
		if(l->valor>max) max = l->valor;
	return max;
}

int take (int n, LInt *l) {
    int i = 0;
    for(;i < n && *l; i++, l = &((*l)->prox));
    if(!(*l)) return i;
    for(;*l;) {
        LInt temp = (*l)->prox;
        free(*l);
        *l = temp;
    }
    return n;
}

// 20

int drop (int n, LInt *l) {
    int i;
    for(i = 0; i < n && (*l); i++) {
        LInt temp = (*l);
        (*l) = (*l)->prox;
        free(temp);
    }
    return i;
}

// 21

LInt Nforward(LInt l, int N){
	for(int i = 0;i<N;i++){
		l = l->prox;
	}
	return l;
}

// 22

int listToArray(LInt l, int v[], int N){
	int i;
	for(i = 0;i<N && l;i++, l = l->prox){
		v[i] = l->valor;
	}
	return i-1;
}

// 23

LInt arrayToList(int v[], int N){
	if(N==0)return NULL;
	LInt new = malloc(sizeof(struct lligada));
	new->valor = (*v);
	new->prox=arrayToList(v+1,N-1);
	return new;
}

// 24

LInt somasAcL(LInt l){
	if(!l) return NULL;
	int total = 0;
	LInt list = NULL, temp = NULL;
	for(;l;l=l->prox){
		LInt new = malloc(sizeof(struct lligada));
		total += l->valor;
		new->valor = total;
		new->prox = NULL;
		if(!list) list = temp = new;
		else temp = temp->prox = new;
	}
	return list;
}

// 25

void remreps(LInt l) {
    if(l) {
        while(l->prox) {
            if(l->prox->valor == l->valor) {
                LInt temp = l->prox;
                l->prox = temp->prox;
                free(temp);
            }
            else l = l->prox;
        }
    }
}

// 26

LInt rotateL (LInt l) {
    if(!l || !l->prox) return l;
    int len = length(l);
    LInt array[len];
    for(int i = 0; i < len; i++, l = l->prox) array[i] = l;
    array[0]->prox = NULL;
    array[len - 1]->prox = array[0];
    return array[1];
}

// 27

LInt parte(LInt l) {
    if(!l || !l->prox) return NULL;
    LInt newL = l->prox;
    l->prox = l->prox->prox;
    newL->prox = parte(l->prox);
    return newL;
}

// Parte 2

typedef struct nodo{
	int valor;
	struct nodo *esq, *dir;
}nodo;
typedef struct nodo *ABin;

// 28

int altura(ABin a){
	if(!a) return 0;
	int l = 1+altura(a->esq);
	int r = 1+altura(a->dir);
	if(l>r) return l;
	else return r;
}

// 29

ABin cloneAb(ABin a){
	if(!a) return NULL;
	ABin new = malloc(sizeof(struct nodo*));
	new->valor = a->valor;
	new->esq = cloneAb(a->esq);
	new->dir = cloneAb(a->dir);
	return new;

}

// 30

void mirror(ABin * a){
	if(*a){
		ABin tmp = (*a)->esq;
		(*a)->esq = (*a)->dir;
		(*a)->dir = tmp;
		mirror(&((*a)->dir));
		mirror(&((*a)->esq));
	}
}

// 31

void inorder_aux(ABin a, LInt * l){
	LInt aux = malloc(sizeof(struct lligada));
	if(a){
		inorder_aux(a->dir,l); // fim
		aux->valor = a->valor;
		aux->prox = (*l);
		(*l) = aux;
		inorder_aux(a->esq,l);// inicio
	}
}

void inorder(ABin a, LInt * l){ // E R D
	*l = NULL;
	inorder_aux(a,l);
}

// 32

void preorder_aux(ABin a, LInt *l){
	LInt aux = malloc(sizeof(struct lligada));
	if(a){
		preorder_aux(a->dir,l);
		preorder_aux(a->esq,l);

		aux->valor = a->valor;
		aux->prox = (*l);
		(*l) = aux;
	}
}

void preorder(ABin a, LInt * l){ // R E D
	*l = NULL;
	preorder_aux(a,l);
}

// 33

void posorder_aux(ABin a, LInt * l){
	LInt aux = malloc(sizeof(struct lligada));
	if(a){
		aux->valor = a->valor;
		aux->prox = (*l);
		(*l) = aux;
		posorder_aux(a->dir,l);
		posorder_aux(a->esq,l);

	}
}

void posorder(ABin a, LInt * l){ // E D R
	*l = NULL;
	posorder_aux(a,l);
}

// 34

int depth(ABin a, int x){
	if(!a) return -1;
	if (a->valor == x) return 1;

	int esq = depth(a->esq,x);
	int dir = depth(a->dir,x);

	if(esq == -1 && dir == -1) return -1;
	else if(esq == -1) return 1 + dir;
	else if (dir == -1) return 1 + esq;

	return esq<dir ? 1+esq : 1 + dir; 
}

// 35

int freeAB(ABin a){
	if(!a) return 0;
	int n = 1 + freeAB(a->esq) + freeAB(a->dir);
	free(a);
	return n;

}

// 36

int pruneAB(ABin * a, int l){
	if((*a) == NULL) return 0;
	int n = 0;
	if(l==0){
		n = 1 + pruneAB(&(*a)->esq,0) + pruneAB(&(*a)->dir,0);
		free(*a);
		(*a) = NULL;
	} else n = 1+pruneAB(&(*a)->esq,l-1)+pruneAB(&(*a)->dir,l-1);
	return n;

}

// 37

int iguaisAB(ABin a, ABin b){
	if((!a && b) || (a && !b)) return 0;
	if((!a && !b) || (a && b)) return 1;	

	return a->valor==b->valor && iguaisAB(a->esq,b->esq) && iguaisAB(a->dir,b->dir);
}

// 38

LInt concat(LInt a, LInt b){
	if(!a) return b;
	LInt tmp = a;
	while(tmp->prox) tmp = tmp->prox;
	tmp->prox = b;
	return a;
}

LInt nivelL(ABin a, int n){
	LInt new = malloc(sizeof(struct lligada));
	if(n<1 || !a) return NULL;
	if(n==1){
		new->valor = a->valor;new->prox = NULL;
		return new;
	}
	else return concat(nivelL(a->esq,n-1),nivelL(a->dir,n-1));
}

// 39

int nivelV (ABin a, int n, int v[]) {
    if(!a || n < 1) return 0;
    if(n == 1) {
        *v = a->valor;
        return 1;
    }
    else {
        int e = nivelV(a->esq,n - 1,v);
        int d = nivelV(a->dir,n - 1,v+e);
        return e + d;
    }
}

// 40

int dumpAbin(ABin a, int v[], int N){
	int e;
    if(a && N) {
        e = dumpAbin(a->esq,v,N);
        if(e < N) {
            v[e] = a->valor;
            return 1 + e + dumpAbin(a->dir,v+e+1,N-e-1);
        }
        else return N;
    }
    else return 0;
}

// 41

ABin somasAcA (ABin a) {
    if(!a) return NULL;
    ABin new = malloc(sizeof(struct nodo));
    new->esq = somasAcA(a->esq);
    new->dir = somasAcA(a->dir);
    new->valor = a->valor + (new->esq ? new->esq->valor : 0) + (new->dir ? new->dir->valor : 0);
    return new;
}

// 42

int contaFolhas(ABin a){
	if(a->esq==NULL&&a->dir==NULL) return 1;
	else return contaFolhas(a->esq) + contaFolhas(a->dir);	
}

// 43

ABin cloneMirror(ABin a){
	if(!a) return NULL;
    ABin new = malloc(sizeof(struct nodo));
    new->valor = a->valor;
    new->esq = cloneMirror(a->dir);
    new->dir = cloneMirror(a->esq);
    return new;
}

// 44

int addOrd (ABin *a, int x) {
    while(*a) {
        if((*a)->valor == x) return 1;
        if((*a)->valor > x) a = &((*a)->esq);
        else a = &((*a)->dir);
    }
    ABin new = malloc(sizeof(struct nodo));
    new->valor = x;
    new->esq = new->dir = NULL;
    (*a) = new;
    return 0;
}

// 45

int lookupAB(ABin a, int x) {
    while(a) {
        if(a->valor == x) return 1;
        if(a->valor > x) a = a->esq;
        else a = a->dir;
    }
    return 0;
}

// 46

int depthOrd (ABin a, int x) {
    if(!a) return -1;
    if(a->valor == x) return 1;
    int d = depthOrd((a->valor < x ? a->dir : a->esq),x);
    return d == -1 ? d : 1 + d;
}

// 47

int maiorAB (ABin a) {
    while(a->dir) a = a->dir;
    return a->valor;
}

// 48

void removeMaiorA (ABin *a) {
    if(!(*a)->dir) {
        ABin temp = (*a);
        free(*a);
        (*a) = temp->esq;
    }
    else removeMaiorA(&((*a)->dir));
}

// 49

int quantosMaiores (ABin a, int x) {
    if(!a) return 0;
    if(a->valor <= x) return quantosMaiores(a->dir,x);
    else return 1 + quantosMaiores(a->esq,x) + quantosMaiores(a->dir,x);
}

// 50

void listToBTree (LInt l, ABin *a) {
    if(!l) return;
    ABin new = malloc(sizeof(struct nodo));
    int meio = length(l) / 2;
    LInt temp = l, prev = NULL;
    int i;
    for(i = 0; i < meio; i++) {
        prev = temp;
        temp = temp->prox;
    }
    new->valor = temp->valor;
    new->esq = new->dir = NULL;
    if(prev) prev->prox = NULL;
    
    if(l != temp) listToBTree(l,&(new->esq));
    if(temp->prox) listToBTree(temp->prox,&(new->dir));
    (*a) = new;
}

// 51

int deProcuraAux(ABin a, int x, int maior) {
    if(!a) return 1;
    if((maior && a->valor < x) || (!maior && a->valor > x)) return 0;
    return deProcuraAux(a->esq,x,maior) && deProcuraAux(a->dir,x,maior);
}

int deProcura (ABin a) {
    if(!a) return 1;
    int b = deProcuraAux(a->esq,a->valor, 0) && deProcura(a->esq);
    int c = deProcuraAux(a->dir,a->valor, 1) && deProcura(a->dir);
    return b && c;
}


int main(){

	return 0;
}