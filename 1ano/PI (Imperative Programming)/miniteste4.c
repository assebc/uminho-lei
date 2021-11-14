#include <stdio.h>

void swap(int v[], int i, int j){
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void maxSort (int v[], int N){
    int m, i, j, count = 0;

    for(j=0; j<N-1 ; j++){
        // descobrir o maior elemento desde j até N
        m=j;
        for(i=j+1; i<N; i++)
            if(v[i] > v[m])
                m = i;
        swap(v,i,m);
        
    }
}
