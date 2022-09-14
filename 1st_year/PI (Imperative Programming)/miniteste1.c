#include <stdio.h>
#include <stdlib.h>

int func(int x) {
  int r = 0;
  while (x > 0) {
    r += 2;
    x = x - r;
  }
  printf("%d\n",r);
  return r;

}

void exercicio2(){
	int x,y;
	for (y=0;y<8;y++) {    
  		for (x=0;x<8;x++) {
    		if (x-y>-1) putchar('#');
   			else putchar('.');
  		}
  		putchar('\n');
	}

}


int main(){

	func(3);
	exercicio2();

}

