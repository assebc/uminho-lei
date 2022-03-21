#include <stdio.h>

int pronic(int a) {
    for (int i = 1; i <= a; i++) {
        if (i * (i + 1) == a) {
            return 1;
        }
    }
    return 0;
}

void fibonacci(int n) {
	int init = n;
    int pares = 0;
    int oblongos = 0;
    int impares = 0;

    int a = 0, b = 1, aux;
    for (; n > 0; n--) {
        if (a % 2 == 0) pares++;
        else impares++;

        if(pronic(a)) oblongos++;
        

        //printf("%d\n", a);
        aux = a;
        a = b;
        b = (b + aux) % 10000;
    }

    printf("Pares: %d\n", pares);
    printf("Impares: %d\n", impares);
    printf("Oblongos: %d\n", oblongos);
    printf("===============%d==============\n", init);
}



int main(){
	fibonacci(65);
	fibonacci(70);
	return 0;
}