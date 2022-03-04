#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void question1(){

	int x, count = 50;
	int * array = malloc(sizeof(int)*count);

	for(int i = 0;i<count;i++){
		scanf("%d",&x);
		if(x==0){
			count = i+1;
			break;
		}
		array[i] = x;
		if(i==count-2) {
			count *= 2;
			array = (int *)realloc(array, sizeof(int)*count);
		}
	}

	int max = 0;
	for(int i = 0;i<count;i++) if(array[i]>max) max = array[i];
	
	printf("O maior elemento é %d\n", max);
}


void question2(){

	int x, count = 50;
	int * array = malloc(sizeof(int)*count);

	for(int i = 0;i<count;i++){
		scanf("%d",&x);
		if(x==0){
			count = i;
			break;
		}
		array[i] = x;
		if(i==count-2) {
			count *= 2;
			array = (int *)realloc(array, sizeof(int)*count);
		}
	}

	int all = 0;
	for(int i = 0;i<count;i++) all += array[i];
	
	printf("A média é %d\n", all/count);
}

void question3(){

	int x, count = 50;
	int * array = malloc(sizeof(int)*count);

	for(int i = 0;i<count;i++){
		scanf("%d",&x);
		if(x==0){
			count = i+1;
			break;
		}
		array[i] = x;
		if(i==count-2) {
			count *= 2;
			array = (int *)realloc(array, sizeof(int)*count);
		}
	}

	int max = 0;
	int snd = 0;
	for(int i = 0;i<count;i++) 
		if(array[i]>max){
			snd = max;
			max = array[i];
		}
	printf("O segundo maior elemento é %d\n", snd);
}

int bitsUm(unsigned int n){
	int num = n;
	int r = 0;
	int a[10],i;    
 
	for(i=0;n>0;i++){    
		a[i]=n%2;
		if(a[i]==1) r++;    
		n=n/2;    
	}    

	printf("Utilizado %d bits para representar %d em binário\n",r,num);
	return r;
}

int trailingZ(unsigned int n){
	int num = n;
	int r = 0;
	int a[10],i; 
	for(i=0;n>0;i++){    
		a[i]=n%2;
		if(a[i]==0) r=i;    
		n=n/2;    
	}    

	printf("Maior expoente com bit a 0 é %d no número %d\n",r,num);
	return r;
}

int qDig(unsigned int n){
	int num = n;
	int r = 0;
	int a[10], i;
	for(i = 0;n>0;i++){
		a[i] = n%10;
		n = n/10;
		if(a[i]>0) r++;
	}
	printf("É necessário %d digitos para representar %d\n", r, num);

	return r;
}

char * mystrcat(char s1[], char s2[]){

	if(s1 == NULL && s2 == NULL) return NULL;
	char *string = malloc(strlen(s1) + strlen(s2) + 1);
	char *res = string;
	for (; *s1 ; *string++ = *s1++);
	for (; *s2 ; *string++ = *s2++);
	*string = '\0';
	s1 = res;
	printf("%s\n", s1);
	return s1;
}

char * mystrcpy(char *dest, char source[]){

	dest = source;
	printf("%s\n",dest);
	return dest;
}

int mystrcmp(char s1[], char s2[]){
	int total = 0;
	while(*s1!='\0' || *s2!='\0'){
		if(*s1++ > *s2++) total++;
		else if (*s1++ < *s2++) total--;
	}
	printf("%d\n", total);
	return total;
}

int compare(const char *X, const char *Y)
{
    while (*X && *Y)
    {
        if (*X != *Y) {
            return 0;
        }
 
        X++;
        Y++;
    }
 
    return (*Y == '\0');
}
 
// Function to implement `strstr()` function
const char * mystrstr(const char* X, const char* Y)
{
    while (*X != '\0')
    {
        if ((*X == *Y) && compare(X, Y)) {
            return X;
        }
        X++;
    }
 
    return NULL;
}

void mystrrev(char s[]){

	printf("%s\n",s);
	char aux[strlen(s)];
	int j = 0;
	for(int i = strlen(s)-1;i>=0;i--)
		aux[j++] = s[i];
	s = aux;
	printf("%s\n",s);
}

void mystrnoV (char s[]){

	printf("%s\n",s);
	char aux[strlen(s)];
	int j = 0;
	for(int i = 0;i<strlen(s);i++){
		if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') continue;
		else aux[j++] = s[i];
	}
	s = aux;

	printf("%s\n",s);	
}

void truncW (char t[], int n){

	//while()

}

int main(){

	//question1();
	//question2();
	//question3();
	//bitsUm(31);
	//trailingZ(30);
	//qDig(11);	
	//mystrcat("ar","roz");
	//mystrcpy(NULL,"arroz");
	//mystrcmp("araa","ara");
	//mystrstr("ara", "araabarcar");
	//mystrrev("zorra");
	//mystrnoV("arox");
	//truncW("pai natal", 2);
	
	return 0;
}