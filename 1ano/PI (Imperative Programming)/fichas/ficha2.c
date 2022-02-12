#include <stdio.h>

int abs(int x){

	if (x<0) return (-x);
	else x;
}

float multInt1(int n, float m){

	float r = 0;

	while(n>0){
		r += m;
		n--;
	}

	printf("%.0f\n", r);

	return r;

}

float multInt2(int n, float m){

	float r = 0;

	while(n!=1){

		if (n%2==1) r+=m;
		n /= 2;
		m *= 2;	

	}

	r+=m;

	printf("%.0f\n", r);

	return r;
}

int mdc(int a, int b){

	int mdc = 1, sm, bg;

	if (a<b){
		sm = a;
		bg = b;
	} else {
		sm = b;
		bg = a;
	}

	for(int i = 1;i<=sm;i++){
		if(sm%i==0){
			if(bg%i==0){
				mdc = i;
			}
		}
	}

	printf("%d\n", mdc);

	return mdc;
}


int main(){

	multInt1(5,5);
	multInt2(5,5);
	mdc(12,6);
	return 0;
}

