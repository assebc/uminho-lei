#include <stdio.h>
#include <stdlib.h>

int contaVogais(char *s){

	int count = 0;

	for(int i = 0;s[i]!='\0';i++){
		if(s[i] == 'a' || s[i] == 'e' 
					   || s[i] == 'i' 
					   || s[i] == 'o' 
					   || s[i] == 'u') count++;
	}
	
	return count;
}

int retiraVogaisRep(char *s){

	int amais = 0;
	char * frase = malloc(sizeof(s));
	int i, j = 0;
	for(i = 0;s[i+1]!='\0';i++){

		if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u'){
			while (s[i+1] == s[i]) i++;
		}
		frase[j] = s[i];
		j++;
	}

	amais = i-j;
	printf("%s, ",frase);

	return amais;
}

int ordenado (int v[],int N){

	for(int i=0;i<N-1;i++)
		if(v[i]>v[i+1]) return 0;
	return 1;
}

void merge(int a[], int na, int b[], int nb, int r[]){

	int j = 0, h = 0;
	for(int i=0;i<na+nb;i++){

		if(j == na)r[i] = b[h++];
		else if(h == nb)r[i] = a[j++];

		if(a[j]<=b[h]) r[i] = a[j++];
		else r[i] = b[h++];
	}

}

void swap(int v[], int i, int j){

	int tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;

}

int partition(int v[], int N, int x){

	int nums = 0;
	int * aux = v;

	if(!ordenado(aux,N)) {

		for(int j=0;j<N-1;j++){
			for(int h=j;h<N;h++){
				if(aux[h]<aux[j]) swap(v,h,j);
			}
		}
	}

	for(int i=0;i<N;i++){
		if(aux[i]<x) nums++;
	}

	return nums;
}

int main(){

	char * palavra = "arroz"; // 2
	printf("\nExiste %d vogais na palavra %s!\n\n", contaVogais(palavra),palavra);

	char * frase = "Estaa e umaa string coom duuuplicadoos";
	printf("onde existira %d letras a mais!\n\n", retiraVogaisRep(frase));

	int v[5] = {1,5,2,3,4};
	int h[5] = {1,2,3,4,5};
	int h1[7] = {1,3,5,7,9,11,15};
	int h2[9] = {2,4,6,8,10,12,13,14,16};
	if (!ordenado(v,5)) printf("O array v não está ordenado!\n");
	else printf("O array v está ordenado!\n");
	if (!ordenado(h,5)) printf("O array h não está ordenado!\n\n");
	else printf("O array h está ordenado!\n\n");
	
	int r[15];
	merge(h1,7,h2,9,r); //
	for(int i = 0;i<15;i++) printf("%d ",r[i]);
	printf("\n\n");
	
	int h3[10] = {1,10,30,4,2,40,3,0,9,32};
	printf("Na função partition existe um total de %d numeros menores que %d!\n\n", partition(h3,10,5), 5);

	return 0;
}