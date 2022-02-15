#include <stdio.h>
#include <stdlib.h>

typedef struct aluno{

	int numero;
	char nome[100];
	int miniT[6];
	float teste;
} Aluno;

void swap(Aluno v[], int i, int j){

	Aluno tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;

}

int nota (Aluno a){

	int minit = 0;
	float teste;


	for(int i=0;i<6;i++){
		minit = a.miniT[i];
	}

	teste = a.teste * 0.6 + minit*0.4;

	if (teste>=9.5){
		printf("\n%s com %.2f\n\n", a.nome, teste);
		return teste;
	}

	return 0;
}

int procuraNUM(int num, Aluno t[], int N){

	for(int i=0;i<N;i++){
		if(num==t[i].numero){
			printf("O aluno(a) é %s no indice %d\n\n", t[i].nome, i);
			return i;
		} 
	}

	return -1;
}

void ordenaPorNum(Aluno t[], int N){

	for(int i=0;i<N-1;i++){
		for(int j = i+1;j<N;j++){
			if(t[i].numero>t[j].numero) swap(t,i,j);
		}
	}
}

void criaIndPorNum(Aluno t[], int N, int ind[]){

	int inds = 0, count = 0;

	for(int i=0;i<N-1;i++){
		for(int j=i+1;j<N;j++){
			if(t[i].numero>t[j].numero) count = j;
		}

		if(count>0) ind[inds++] = count;
		else ind[inds++] = i;
		
		count = 0;
		
	}
}

int main(){

	Aluno andre = {4444, "Andre", {2,1,0,2,2,2}, 10.5};
	Aluno joana = {2222, "Joana", {2,2,2,1,0,0}, 14.5};
	Aluno maria = {7777, "Maria", {2,2,2,2,2,1}, 18.5};
	Aluno paulo = {3333, "Paulo", {0,0,2,2,2,1}, 8.7};

	Aluno as[4] = {andre, joana, maria, paulo};

	nota(andre);
	nota(joana);
	nota(maria);
	nota(paulo);

	procuraNUM(2222,as,4);

	ordenaPorNum(as,4);
	for(int i=0;i<4;i++) printf("%d ", as[i].numero);
	printf("\n\n");

	int ind[4];
	criaIndPorNum(as,4,ind);
	for(int j=0;j<4;j++) printf("%d ", ind[j]);
	printf("\n\n");
	

	return 0;
}