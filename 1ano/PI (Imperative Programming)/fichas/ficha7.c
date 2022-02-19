#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct celula {
	char *palavra;
	int ocorr;
	struct celula * prox;

} * Palavras;

void libertaLista (Palavras l){
    
    
    while(l!=NULL){
    	free(l->palavra);
    	l->ocorr = 0;
    	l = l->prox;
    }
}

int quantasP (Palavras l){
    
    int count = 0;
    Palavras aux = l;

    while(aux!=NULL){
    	count++;
    	aux = aux->prox;
    }
    
    return count;
}

void listaPal (Palavras l){
    
    Palavras aux = l;

    while(aux!=NULL){
    	printf("%s (%d)\n", aux->palavra, aux->ocorr);
    	aux = aux->prox;
    }
}

char * ultima (Palavras l){
    
	Palavras aux = l;
	char * pal = malloc(sizeof(char)*20);

	while(aux!=NULL){
		pal= aux->palavra;
		aux = aux->prox;
	}
	

    return pal;
}

Palavras acrescentaInicio (Palavras l, char *p){
    
    Palavras aux = malloc(sizeof(struct celula));
    aux->palavra = p;
    aux->ocorr = 1;
    aux->prox = l;
    l = aux;

    return l;
}

Palavras acrescentaFim (Palavras l, char *p){
    
    Palavras aux = malloc(sizeof(struct celula));
    aux->palavra = p;
    aux->ocorr = 1;
    aux->prox = NULL;

    if(quantasP(l) == 0) l = aux;

    while(l->prox!=NULL) l = l->prox;
    l->prox = aux;

    return l;
}

Palavras acrescenta (Palavras l, char *p){
    
    Palavras aux = malloc(sizeof(struct celula));
    Palavras aux2 = l;
    aux->palavra = p;
    aux->ocorr = 1;
    aux->prox = NULL;

    while(l!=NULL){
    	if(strcmp(l->palavra,p) == 0) l->ocorr++;
    	l = l->prox;
    	return l;
    }

    aux2 = acrescentaInicio(aux2,p);
   	

    return aux2;
}

struct celula * maisFreq (Palavras l){
    
    int count = 0;
    struct celula * result = malloc(sizeof(struct celula));

    while(l!=NULL){
    	if(l->ocorr>count){
    		result = l;
    		result->prox = NULL;
    		count = result->ocorr;	
    	}
    	l = l->prox;

    }

    return result;
}

int main () {

    Palavras dic = NULL;

    char * canto1 [45] = {"as", "armas", "e", "os", "baroes", "assinalados",
                          "que", "da", "ocidental", "praia", "lusitana", 
                          "por", "mares", "nunca", "de", "antes", "navegados",
                          "passaram", "ainda", "alem", "da", "taprobana",
                          "em", "perigos", "e", "guerras", "esforcados",
                          "mais", "do", "que", "prometia", "a", "forca", "humana",
                          "e", "entre", "gente", "remota", "edificaram", 
                          "novo", "reino", "que", "tanto", "sublimaram"};

    printf ("\n_____________ Testes _____________\n\n");

    int i; struct celula *p;
    for (i=0;i<45;i++)
        dic = acrescentaInicio (dic, canto1[i]);

    printf ("Foram inseridas %d palavras\n", quantasP (dic));
    printf ("palavras existentes:\n");
    listaPal (dic);
    printf ("última palavra inserida: %s\n", ultima (dic));

    p = maisFreq (dic);
    printf ("Palavra mais frequente: %s (%d)\n", p->palavra, p->ocorr);
    
    printf ("\n_________ Fim dos testes _________\n\n");

    return 0;
}