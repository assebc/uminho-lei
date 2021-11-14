#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#define MAXLINE 1024

char buffer[MAXLINE];

char *mystrcat(char s1[], char s2[]) { // concat snd to fst string
    char *cat = s1;
    while (*s1){			// chega ao fim da fst string
    	s1++;
    }
    while((*s1 = *s2)){			// iguala fst string à snd string
    	s1++;					// chega ao fim da fst string
    	s2++;					// chega ao fim da snd string
    }
    *s1 = '\0';					// fst string acaba
    return cat;					// return fst string

}

char* mystrcpy(char *dest, char source[]){
	char *result = dest;
	while((*dest = *source)){
		source++;
		dest++;
	}
	return result;
} 

int mystrcmp(char s1[], char s2[]){
	while (*s1 == *s2 && *s1){
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char *mystrstr(char s1[], char s2[]){
	int position = 1;
	char *aux = s1;
	while(*s2 && *s1){
		if(*s1 != *s2){
			position = 0;
			aux = s1;
		}
		if(*s1 == *s2){
			if(!position){
				position = 1;
				aux = s1;
			}
			s2++;
		}
		s1++;
	}
	
	if (position && !(*s2)) return aux; 
	return NULL; 
}

void strrev(char s[]){
	int len, i;
	for (len = 0; s[len]; len++);
	char rev[len];
	for (i=0;i<len;i++){
		rev[i] = s[len-i-1];
	}
	for (i=0;i<len;i++){
		s[i] = rev[i];
	}
}

void rest(char *s){
	for(;*s;s++)
		*s = *(s+1);
}

void strnoV(char s[]){
	while(*s){
		if (*s == 'a' || *s == 'A' || 
			*s == 'e' || *s == 'E' || 
			*s == 'i' || *s == 'I' ||
			*s == 'o' || *s == 'O' ||
			*s == 'u' || *s == 'U') rest(s);
		else s++;
	}
}

void truncW(char t[], int n){
	int size = 0;
	while(*t){
		if(*t == ' ' || *t == '\n' || *t == '\t'){
			t++;
			size = 0;
		} else {
			if(size++ >= n) 
				rest(t);
			else
				t++;
		}
	}
}

int freqC(char ch, char s[]) {
    int freq = 0;
    int i;
    for(i = 0; s[i]; i++) {
        if(s[i] == ch) freq++;
    }
    return freq;
}

char charMaisfreq(char s[]){
	char maisFreq = 0;
	int freqMax = 0;
	int i, freq;

	for (i=0;s[i];i++){
		if((freq = freqC(s[i],s)) > freqMax){
			freqMax = freq;
			maisFreq = s[i];
		}
	}

	return maisFreq;
}

int iguaisConsecutivos (char s[]){
	int consec = 1;
	int max = 0;
	int i;

	for (i=0;s[i];i++){
		if(s[i] == s[i+1])
			consec++;
		else{
			if (consec>max)
				max = consec;
			consec = 1;
		}
	}
	return max;
}

int not_in_prev(char str[], int k, int n) {
    int ans = 1;
    int i;
    for(i = k; i < n; i++) {
        if(str[i] == str[n]) {
            return 0;
        }
    }
    return ans;
}

int difConsecutivos (char s[]){
	int res = 0;
	int i, j;
	for(i=0;s[i];i++){
		int consec = 0;
		for(j=i;s[j];j++){
			if(not_in_prev(s,i,j)) consec++;
            else break;
        }
        if (consec > res) res = consec;
    }
    return res;
}

int contaVogais (char s[]){
	int count = 0;
	int i;

	for (i=0;s[i];i++){
		switch(s[i]){
			case 'a' :
			case 'e' :
			case 'i' :
			case 'o' :
			case 'u' :
			case 'A' :
			case 'E' :
			case 'I' :
			case 'O' :
			case 'U' :
			count++;
		}
	}
	return count;
}

int contida (char s[], char t[]){
	int cont = 1;
	int i, j;

	for (i=0;s[i];i++){
		int pertence = 0;
		for (j=0;t[j];j++){
			if (s[i] == t[j])
				pertence = 1;
		}
		if (!pertence){
			cont = 0;
			break;
		}
	}
	return cont;
}

int palindrome(char s[]){
	int size = 0;
	int i;
	for (i=0;s[i];i++)
		size++
	for(i=0;s[i];i++){
		if(s[i] != s[size - 1 - i]) //strcmp dos pobres
			return 0;		
	}
	return 1;
}

int main(){
	printf("%s\n", "rei");
	return 0;
}

