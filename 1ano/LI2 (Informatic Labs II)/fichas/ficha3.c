/*
leia um número inteiro e
imprima o padrão mostrado no exemplo.
Input
O seu programa deve ler um valor inteiro que indica o tamanho do padrão.

Output
O seu programa deve imprimir o padrão do tamanho dado.

Exemplo
Input
3
Output
*....*
**..**
******
**..**
*....*
Input
5
Output
*........*
**......**
***....***
****..****
**********
****..****
***....***
**......**
*........*

-------
int i,j,rows;

scanf("%d", &rows)
for (i=1; i <=rows; i++) {
    for (j=1;j<=i;j++){
        printf('*');
    }
    printf("\n")
}

for (i=1; i <=rows; i++) {
    for (j=rows;j<=i;j--){
        printf('*');
    }
    printf("\n")
}

return 0;
------
    *
   **
  ***
 ****
*****
 ****
  ***
   **
    *
------

gcc -std=gnu11 -Wall -Wextra -pedantic-errors -O ficha3.c -lm

*/

#include <stdio.h>
#include <assert.h>

void replicate(int a, char b) 
{
    for (int i=0; i<a; i++){
    	putchar(b);
    }
}

void pattern1(int rows) 
{
    // up part
    int n, obj;

    for(n=1; n<=rows; n++) {
        obj = rows*2 - n*2;

        replicate(n,'*'); // left
        replicate(obj,'.'); // middle
        replicate(n,'*'); // right
        putchar('\n'); // change line
    }
}

void pattern2(int rows) 
{
    // down part
    int n, collum, obj;

    collum = rows-1; // inicial size 
    for(n=1; n<rows; n++) {
        obj = n*2;

        replicate(collum,'*'); // left
        replicate(obj,'.'); // middle
        replicate(collum,'*'); // right
        putchar('\n'); // change line

        collum = collum - 1;
    }
}

int main() 
{
    int rows;
    assert(scanf("%d", &rows) == 1); // read row size
    pattern1(rows); // superior pattern
    pattern2(rows); // lower pattern

    return 0;
}

