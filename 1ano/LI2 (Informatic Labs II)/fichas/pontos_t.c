#include <stdio.h>

void triangulos(int x, int y){
	int i, count = 0, sum=0, last = 0;
	
	for(int j = x;j<=y;j++){
		if(sum == 0){
			for(i=0;i<=j; i++){
				sum += i;
				if(sum == j){
					count++;
					last = i;
			   		break;
			  	}
			}
		} else{
			for(int a=last;a<=j;a++){
				sum += a;
				if(sum == j){
					count++;
					last = a;
			   		break;
			  	}
			}
		}
	}
	printf("%d ", count);

}

void primos(int x, int y){
	int count = 0;
  	int a,b;
    
  	for (a=2;a<=y;a++){
      	int c=0;
      	for (b=1;b<=a;b++){
          	if (a%b==0) c++;
       }
       if (c==2) count++;
    }

	printf("%d\n", count);
}

int main(){

	int x = 0, y = 0;
	printf("Diga 2 vars\n");
	scanf("%d %d",&x,&y);
	int a = x; int b = y;
	triangulos(x,y); 
	primos(a,b);

	return 0;
}