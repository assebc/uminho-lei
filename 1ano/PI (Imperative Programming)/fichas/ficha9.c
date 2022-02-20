#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodo {
	int valor;
	struct nodo *left, *right;
} * ABin;

ABin newABin (int r, ABin e, ABin d) {
	ABin a = malloc (sizeof(struct nodo));
	if (a!=NULL) a->valor = r; a->left = e; a->right = d;
	return a;
}

ABin RandArvFromArray (int v[], int N) {
   ABin a = NULL;
    int m;
    if (N > 0){
    	m = rand() % N;
    	a = newABin (v[m], RandArvFromArray (v,m), RandArvFromArray (v+m+1,N-m-1));
    }
    return a;	
}

int altura(ABin a){
    if (a == NULL) return -1;
    else {
        int lDepth = altura(a->left);
        int rDepth = altura(a->right);

        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}

int nFolhas(ABin a) {
  if(a == NULL) return 0;
  if(a->left == NULL && a->right==NULL) return 1;           
  else return nFolhas(a->left) + nFolhas(a->right);     
}

ABin maisEsquerda (ABin a){
    
    if (a == NULL) return NULL;
    else if (a->left != NULL) maisEsquerda(a->left);
    return a;
}

/* Print nodes at a given level */
void imprimeNivel(ABin root, int level)
{
    if (level == 1)
        printf("%d ", root->valor);
    else if (level > 1)
    {
        imprimeNivel(root->left, level-1);
        imprimeNivel(root->right, level-1);
    }
}

int procuraE (ABin a, int x){
    
    if(a == NULL) return 0;
    if(a->valor == x) return 1;
    else return (procuraE(a->left,x) || procuraE(a->right,x));
}

struct nodo *procura (ABin a, int x){
    if(a==NULL) return NULL;
    if(a->valor == x) return a;
    else if(a->valor > x) procura(a->left,x);
    else procura(a->right,x);
}


int main (){
  int v1[15] = { 1, 3, 5, 7, 9,11,13,15,17,19,21,23,25,27,29},
      v2[15] = {21, 3,15,27, 9,11,23, 5,17,29, 1,13,25, 7,19},
      N=15;
  ABin a1, a2,r;
  
  srand(time(NULL));
  
  printf ("_______________ Testes _______________\n\n");
  // N = rand() % 16;
  a1 = RandArvFromArray (v2, N);
  printf ("Primeira árvore de teste (%d elementos)\n", N);
  
  printf ("altura = %d\n", altura (a1));
  printf ("numero de folhas: %d\n", nFolhas (a1));
  printf ("Nodo mais à esquerda: ");
  r = maisEsquerda (a1);
  if (r==NULL) printf ("(NULL)\n"); else printf ("%d\n", r->valor);
  printf ("Elementos no nivel 3_______\n");
  imprimeNivel (a1, 3);
  printf ("\n___________________________\n");

  printf ("procura de 2: %d\n", procuraE (a1, 2));
  printf ("procura de 9: %d\n", procuraE (a1, 9));
  
  
  // N = rand() % 16;
  a2 = RandArvFromArray (v1, N);
  printf ("\nSegunda árvore de teste (%d elementos)\n", N);
  
  printf ("procura de 9: ");
  r = procura (a2, 9);
  if (r==NULL) printf ("(NULL)\n"); else printf ("%d\n", r->valor);   
  printf ("procura de 2: ");
  r = procura (a2, 2);
  if (r==NULL) printf ("(NULL)\n"); else printf ("%d\n", r->valor);   
  
  printf ("\n\n___________ Fim dos testes ___________\n\n");

  return 0;

}