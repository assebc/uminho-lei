#include <stdio.h>
#include <stdlib.h>

int factorial(int n){

	int r = 0;
	if (n>0) r = n*factorial(n-1);
	else r = 1;
	return r;
}
void swap(int array [] , int i, int j){

	int tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}

void ordena_aux(int array [] , int N){

	for(int i = 0;i<N-1;i++){
		for(int j = 1;j<N;j++){
			if(array[j]<array[i]) swap(array,i,j);
		}
	}

}

void exercicioC(){

	int x = 0,y =0, z=0;
	printf("input?\n");
	scanf("%d %d %d",&x, &y, &z);
	int array[] = {x, y, z};
	ordena_aux(array, 3);
	int result = factorial(array[2]);
	if(result != 1) printf("FACTORIAL\n");
	else for(int i = 0;i<3;i++) printf("%d ", array[i]);
}


void exercicioD(){


}

int main(){

	exercicioC();
	exercicioD();

	return 0;
}