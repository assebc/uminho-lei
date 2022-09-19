#include <stdio.h>

int capicua(char str[], int n){
	int count = 1, j = n-1;
	for(int i = 0;i<n/2;i++)
		if(str[i]==str[j]){
			count+=2;
			j--;
		}
		else j--;
	if(count>1&&n%2==0) count--;
	
	printf("%d\n", count);
	return count;
}

int main(){
	int n = 0;
	printf("Tamanho\n");
	scanf("%d",&n);
	char str[n];
	printf("String\n");
	scanf("%s",str);
	mergeSort(str,0,n);
	return 0;
}