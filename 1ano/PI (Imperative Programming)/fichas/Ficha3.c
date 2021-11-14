#include <stdio.h>

// exercício 1
/**/
int main(){
	
	int x [15] = {1, 2, 3, 4, 5,
				  6, 7, 8, 9, 10,
				  11,12,13,14,15}

	int *y, *z, i;
	y = x;
	z = x+3;
	for (i=0;i<5;i++) {
		printf("%d %d %d\n", x[i], *y, *z);
		y = y+1;
	SSS	z = z+2;
	}

	return 0;

}

