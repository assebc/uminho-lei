#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<math.h>

int ntriangular (int x,int y){
    int i,a=0,b=0;
    for(i=1;a<=y;i+=1){
        a+=i;
        if (a<x || a>y);
        else b+=1;
    }
    return b;
}

int nprimo (int x,int y){
    if (y==1 || y==2)
    y+=1;
    bool *p=(bool*) calloc(y,sizeof(bool));
    p[0] = false;
    int z=0,a=0;
    while ((pow(a,2))<=y){
        if (p[a-1]==false){
            for (int b=a+a;b<y;b+=a){
                if (b==0){
                    p[0]=true;
                    break;
                }
                p[b-1]=true;
            }
        }
        a++;
    }
    for (a=x;a<=y;a+=1) if (p[a-1]==0) z+=1;
    return (z-1);
}

int main(){
    int x,y,nt=0,np=0;
    assert(scanf("%d %d",&x,&y)==2);
        nt=ntriangular (x,y); np=nprimo (x,y);
        printf("%d %d\n",nt,np);
    return 0;
}