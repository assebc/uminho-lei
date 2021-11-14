// gcc -std=gnu11 -Wall -Wextra -pedantic-errors -O ficha4.c -lm

#include <stdio.h>
#include <assert.h>  

int leafs[10][10];

int caule(){

    int x = 0;
    int row, collum;

    
    while (x != (-1)) { // loop condition -1
        
        assert(scanf("%d", &x) > 0); 
        row = x / 10; // 2nd digit
        collum = x % 10; // 1st digit

        if (x != (-1)) leafs[row][collum] = leafs[row][collum] + 1;
    }

    return 0;
} 

void printer(){

    for (int row=0;row<=9;row++) {
        printf("%d|", row); // caule
        for (int collum=0;collum<10;collum++) { 
            int p = leafs[row][collum]; // repeat same numbers using a "pointer" aka pointer dos chineses
            for (int w=0; w<p; w++) printf("%d", collum); // final print of leafs
            
        }

        printf("\n");
    
    }
}

int main() {

    caule();
    printer();
    
    return 0;
}