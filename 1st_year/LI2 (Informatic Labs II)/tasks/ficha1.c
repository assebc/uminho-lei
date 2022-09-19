/*
Soma de quadrados
Escreva um programa que:

leia dois números e
imprima a soma dos seus quadrados


Exemplo
Input
3 4
Output
25

Exemplo
    
    #include <stdio.h>
    #include <assert.h>

    int main() {
        int a, b;

        
        O scanf lê dois inteiros.
        O assert garante que foram lidos dois inteiros.
        %d corresponde a ler um inteiro
        
        assert(scanf("%d%d", &a, &b) == 2);

        // Imprime a soma dos dois valores
        printf("%d\n", a + b);
        return 0;
    }
    
gcc -std=gnu11 -Wall -Wextra -pedantic-errors -O <file.c> -lm   
*/

#include <stdio.h>
#include <assert.h>

void square()
{
    int num1, num2;
    assert(scanf("%d%d", &num1, &num2) == 2);
    num1 = num1*num1;
    num2 = num2*num2;
    printf("%d\n", num1 + num2);
}

int main() 
{
    square();
    return 0;
} 