/*
Triângulos
Escreva um programa que leia três inteiros, que são o tamanho dos lados de um triângulo e que imprima:

INVALIDO, caso o triângulo não possa existir, ou

Os seguintes valores, separados por um espaço:
O tipo, que pode ser um dos seguintes:

EQUILATERO
ISOSCELES
RETANGULO
ESCALENO

O perímetro
A sua área, com duas casas decimais

Input
O seu programa deverá ler três inteiros, separados por espaços.

Output

O seu programa deverá imprimir uma linha com a palavra INVALIDO ou o tipo, 
tal como explicado acima, um espaço, o perímetro, como um inteiro e a área com duas casas decimais.

Exemplos

Input
3
2
6

Output

INVALIDO

Input
8
7
9

Output

ESCALENO 24  26.83

gcc -std=gnu11 -Wall -Wextra -pedantic-errors -O ficha2.c -lm
*/

#include <stdio.h>
#include <assert.h>
#include <math.h>

void typeT()
{   
    char* type;
    float num1, num2, num3, perimetro, n1, n2, n3, max, c1, c2, s, area, areai;

    // recolha de lados
    assert(scanf("%f\n%f\n%f\n", &num1, &num2, &num3) == 3);
    num1 = num1;
    num2 = num2;
    num3 = num3;

    // lados ao quadrado
    n1 = num1*num1;
    n2 = num2*num2;
    n3 = num3*num3;

    if (n1 >= n2 && n1 >= n3) {
        max = n1; c1 = n2; c2 = n3;
    } else if (n2 >= n1 && n2 >= n3) {
        max = n2; c1 =n1; c2 = n3;
    } else {
        max = n3; c1 = n1; c2 = n2; 
    } 

    // perimetro
    perimetro = num1 + num2 + num3;

    // area
    s = perimetro / 2;
    areai = s*(s-num1)*(s-num2)*(s-num3);
    area = sqrt(areai);

    // triangle type
    if (num1 == num2 && num2 == num3) {
        type = "EQUILATERO";
    } else if (max == c1 + c2) {
        type = "RETANGULO";
    } else if (num1 == num2 || num1 == num3 || num2 == num3) {
        type = "ISOSCELES";
    } else {
        type = "ESCALENO";
    }

    // print final
    if ( (num1 + num2 <= num3) || (num1 + num3 <= num2) || (num2 + num3 <= num1) ) {
        printf("INVALIDO\n");
    } else {
    printf("%s %.0f %.2f\n", type, perimetro, area);
    }

}

int main()
{   
    typeT();
    return 0;
}