#include <stdio.h>
#include <stdlib.h>

void swapM(int * x, int *y, int n){

	int * tmp = malloc(sizeof(int)*n);
	for(int i=0;i<n;i++){
		tmp[i] = x[i];
		x[i] = y[i];
		y[i] = tmp[i];
		
	}
	
}

void swap(int v[], int i, int j){

	int tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}

int soma (int v[], int N){

	int r = 0;

	for(int i =0;i<N;i++) r+=v[i];

	return r;
}

void inverteArray1(int v[], int N){

	int j;
	for(int i = 0;i<N/2;i++){
		j = (N-1)-i;
		swap(v,i,j);
	}
}

void inverteArray2(int v[], int N){

	int * tmp = malloc(sizeof(int)*N);
	int j = 0;
	for(int i = N-1;i>=0;i--) tmp[j++] = v[i];
	swapM(v,tmp,N);
	
}

int maximum(int v[], int N, int *m){

	if (N<=0) return 1;

	int max = 0;

	for (int i=0;i<N;i++) if(v[i]>max) max = v[i];

	*m = max;
	
	return 0;
}

void quadrados (int q[], int N){

	int num = 1;

	for(int i=0;i<N;i++){
		q[i] = num * num;
		printf("%d ", q[i]);
		num++;	
	}

}

int main(){

	int x = 3, y = 5;
	swapM(&x,&y,1);
	printf("\nx = %d e y = %d\n\n", x, y);

	int v[5] = {1, 5, 8, 0, 3};
	int h[5] = {3, 2, 1, 4, 7};
	swap(v,0,1);
	printf("1 = %d e 2 = %d\n\n", v[0], v[1]);

	printf("sum = %d\n\n", soma(v,5));

	printf("array before: %d %d %d %d %d\n", v[0], v[1], v[2], v[3], v[4]);
	inverteArray1(v,5);
	printf("array after: %d %d %d %d %d\n\n", v[0], v[1], v[2], v[3], v[4]);
	printf("array before v2: %d %d %d %d %d\n", h[0], h[1], h[2], h[3], h[4]);
	inverteArray2(h,5);
	printf("array after v2: %d %d %d %d %d\n\n", h[0], h[1], h[2], h[3], h[4]);

	printf("array : %d %d %d %d %d\n", v[0], v[1], v[2], v[3], v[4]);
	int * m = malloc(sizeof(int));
	maximum(v,5,m);
	printf("max : %d\n\n", *m);

	int q[10];
	quadrados(q, 10);
	printf("\n\n");

	return 0;
}