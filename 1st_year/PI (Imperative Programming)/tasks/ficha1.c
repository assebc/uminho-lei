#include <stdio.h>

void quadrado (int n){
    
    char matriz[n][n];
    int i, j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            matriz[i][j] = '#';
            if (i!=0 && j==0) printf("\n%c",matriz[i][j]);
            else printf("%c",matriz[i][j]);
        }
    }

    printf("\n\n");
    
}

void xadrez (int n){
    
    char matriz[n][n];
    int accum = 0;
    int i, j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if (accum%2 == 0) matriz[i][j] = '#';
            else matriz[i][j] = '_';
            accum++;
            if (i!=0 && j==0) printf("\n%c",matriz[i][j]);
            else printf("%c",matriz[i][j]);
        }
    }

    printf("\n\n");
}

void printsadf(int n, char h){

    while(n>0){
        if (n==1) printf("%c\n", h);
        else printf("%c", h);
        n--;
    }

}  

void printsadsf(int n, char h){

    while(n>0){
        printf("%c", h);
        n--;
    }

}

void trianguloH (int n){
    
    int i, prints;

    for(i=0;i<(2*n)-1;i++){
        if (i<=n-1) prints = i+1;
        else prints -= 1;
        printsadf(prints,'#');
    } 

    printf("\n\n"); 
}

void trianguloV (int n){
    
    int i, prints, spaces = n-1;

    for(i=0;i<n;i++){
        prints = (2*i)+1;
        printsadsf(spaces,' ');
        spaces--;
        printsadf(prints,'#');
        
    }

}

int circulo (int raio){
    
    return 0;
}

int main(){

    printf("\n");

    quadrado (5); 
    xadrez (5); 
    trianguloH (5); 
    trianguloV (5); 
    printf("\n");
    return 0;
}
