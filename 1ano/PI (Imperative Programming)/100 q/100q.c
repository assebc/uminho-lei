#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#define MAXLINE 1024

char buffer[MAXLINE];


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
char* mystrstr (char haystack[], char needle[]) {
    int isContained = 1;
    char* ans = haystack;
    char* needleStart = needle;
    while(*needle && *haystack) {
        if(*haystack != *needle) {
            isContained = 0;
            needle = needleStart;
        }
        if(*haystack == *needle) {
            if(!isContained) {
                isContained = 1;
                ans = haystack;
            }
            needle++;
        }
        haystack++;
    }
    if (isContained && !(*needle)) return ans;
    else return NULL;
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
    int i, j, conta = 0;
    
    for (i = 0, j = 0; t[i]!='\0'; i++){
        if (t[i] == ' ') {
            conta = 0;
            t[j++] = t[i];
        } else if (conta < n) {
            conta++;
            t[j++] = t[i];
        }
    }
    t[j] = '\0';
}

char charMaisfreq(char s[]){
    int maxIdx = 0, maxCount = 0;
    for(int i=0; s[i]; i++){
        int count=0;
        for(int j=i; s[j]; j++)
            if(s[i] == s[j]) count++; 
        if(count > maxCount){
            maxCount = count;
            maxIdx = i;
        }
    }
    printf("%c\n", s[maxIdx]);
    return s[maxIdx];
}

int iguaisConsecutivos(char s[]){
	int max = 0, atm = 1;
	for(int i = 0;s[i];i+=atm){
		atm = 1;
		for(int j = i+1;s[j]&&s[j]==s[i];j++) atm++;
		if(atm>max) max = atm;

	}
	printf("%d\n", max);
	return max;
}

int difConsecutivos(char s[]){
	int max = 0, atm = 1;
	for(int i = 0;s[i];i+=atm){
		atm = 1;
		for(int j = i+1;s[j]&&s[j]!=s[i];j++) atm++;
		if(atm>max) max = atm;
	}
	printf("%d\n", max);
	return max;
}

int maiorPrefixo(char s1[], char s2[]){
	int count = 0;
	for(int i = 0;s1[i]==s2[i];i++) count++;
	printf("%d\n", count);
	return count;
}

int maiorSufixo(char s1[], char s2[]){
	int count = 0;
	char * aux1 = s1;
	char * aux2 = s2;
	mystrrev(aux1);
	mystrrev(aux2);
	for(int i = 0;aux1[i]==aux2[i];i++) count++;
	printf("%d\n", count);
	return count;
}

int sufPref(char s1[], char s2[]){
	int count = 0, j = 0;
	for(int i = 0;s1[i];i++)
		if(s1[i]==s2[j]){count++; j++;}
	printf("%d\n", count);
	return count;
}

int contaPal(char s[]){
	int count = 0;
	for(int i = 0;s[i];i++)
		if(s[i]!= ' '&&(s[i+1] == ' '|| s[i+1]=='\0')) count++;
	printf("%d\n", count);
	return count;
}

// auxiliar to contaVogais
int existsVogal(char a){
	char s1[10] = {'a','e','i','o','u','A','E','I','O','U'};
	for(int i = 0;s1[i];i++) if(a == s1[i]) return 1;
	return 0;
}

int contaVogais(char s[]){
	int count = 0;
	for(int i = 0;s[i];i++)
		if(existsVogal(s[i])) count++;
	printf("%d\n", count);
	return count;
}

int exists(char a, char s[]){
	int i = 0;
	while(s){
		if(a==s[i]) return 1;
		else i++;
	}
	return 0;
}

int contida(char a[], char b[]){
	int i = 0;
	while(a){
		if(exists(a[i],b)) i++;
		else return 0;
	}

	return 1;
}

void inverte(char s[]){
	char * aux = s;
	int i = strlen(s)-1;
	int j = 0;
	while(s){
		aux[j++] = s[i--];
	}
	s = aux;
}
int palindrome(char s[]){
	char * aux = s;
	inverte(aux);
	if(aux == s) return 1;

	return 0;
}

void tail(char* s) {
    for(; *s; s++)
        *s = *(s+1);
}

int remRep (char x[]) {
    if(!(*x)) return 0;
    int i = 1;
    char prev = x[0];
    while(x[i]) {
        if(x[i] == prev) tail(x + i);
        else prev = x[i++];
    }
    return i;
}

int limpaEspacos (char t[]) {
    int i = 0;
    int prevSpace = 0;
    while(t[i]) {
        if(t[i] == ' ') {
            if(prevSpace) {
                tail(t + i);
                continue;
            }
            else prevSpace = 1;
        }
        else prevSpace = 0;
        i++;
    }
    return i;
}

void insere(int v[], int N, int x){
	for(int i = 0;i<N;i++){
		if (v[i]>x){
			for(int j=N;j>1;j--) // shift direita
				v[j]=v[j-1];
			v[i]=x;
			break;
		}
		if(i==N-1)
			v[N] = x;
	}
}

void merge(int r[], int a[], int b[], int na, int nb){
	int j = 0, h = 0;
	for(int i = 0; i<na+nb;i++){
		if(j != na && h != nb){
			if(a[j]>b[h]) r[i] = a[j++];
			else r[i] = b[h++];
		}
		else if (j==na){
			r[i] = a[h++];
		} else if (h==nb){
			r[i] = a[j++];
		}
	}
}

void recursive_merge(int r[], int a[], int b[], int na, int nb) {
    if(na > 0) {
        if(nb > 0) {
            if(*a > *b) {
                *r = *b;
                recursive_merge(r+1, a, b+1, na, nb-1);
            }
            else {
                *r = *a;
                recursive_merge(r+1, a+1, b, na-1, nb);
            }
        }
        else {
            *r = *a;
            recursive_merge(r+1, a+1, b, na-1, nb);
        }
    }
    else if(nb > 0) {
        *r = *b;
        recursive_merge(r+1, a, b+1, na, nb-1);
    }
}

int crescente(int a[], int i, int j){
	for(int k = i; k<=j-1;k++){
		if(a[k]<=a[k+1]) continue;
		else return 0;
	}
	return 1;
}

int retiraNeg (int v[], int N) {
    int i = 0;
    while(i < N) {
        if(v[i] < 0) {
            for(int j = i; j < N - 1; j++) v[j] = v[j + 1];
            N--;
        }
        else i++;
    }
    return N;
}

int menosFreq (int v[], int N) {
    int freq = 1, minFreq = N, ans = v[0], i;
    for(i = 1; i < N; i++) {
        if(v[i] == v[i - 1]) freq++;
        if(v[i] != v[i - 1]) {
            if(freq < minFreq) {
                minFreq = freq;
                ans = v[i - 1];
            }
            freq = 1;
        }
    }
    if(freq < minFreq) {
        minFreq = freq;
        ans = v[i - 1];
    }
    return ans;
}

int maisFreq (int v[], int N) {
    int freq = 1, maxFreq = 0, ans = v[0];
    for(int i = 1; i < N; i++) {
        if(v[i] == v[i - 1]) freq++;
        if(v[i] != v[i - 1]) {
            if(freq > maxFreq) {
                maxFreq = freq;
                ans = v[i - 1];
            }
            freq = 1;
        }
    }
    return ans;
}


int maxCresc (int v[], int N) {
    int ans = 1, currAns = 1;
    for(int i = 1; i < N; i++) {
        if(v[i - 1] > v[i]) {
            ans = currAns > ans ? currAns : ans;
            currAns = 1;
        }
        else {
            currAns++;
        }
    }
    ans = currAns > ans ? currAns : ans;
    return ans;
}

int elimRep (int v[], int n) {
    int i = 1;
    while(i < n) {
        int belongs = 0;
        for(int j = 0; j < i; j++) {
            if(v[i] == v[j]) belongs = 1;
        }
        if(belongs) {
            for(int j = i; j < n; j++) {
                v[j] = v[j + 1];
            }
            n--;
        } else i++;
    }
    return n;
}
int elimRepOrd (int v[], int n) {return elimRep(v,n);}

int comunsOrd (int a[], int na, int b[], int nb) {
    int i = 0, j = 0, ans = 0;
    while(i < na && j < nb) {
        if(a[i++] == b[j++]) {
            ans++;
            i++;
            j++;
        }
        else if(a[i] > b[j]) j++;
        else i++;
    }
    return ans;
}

int comuns (int a[], int na, int b[], int nb) {
    int ans = 0;
    for(int i = 0; i < na; i++) {
        int belongs = 0;
        for(int j = 0; j < nb; j++) if(a[i] == b[j]) belongs = 1;
        if(belongs) ans++;
    }
    return ans;
}

int minInd(int v[], int n){
	int min = v[0], ind = 0;
	for(int i = 1;i<n;i++){
		if(v[i]<min){
			min = v[i];
			ind = i;
		}
	}
	return ind;
}

void somasAc(int v[], int Ac[], int N){
	int prev = 0;
	for(int i = 0; i<N;i++){
		Ac[i] = prev+v[i];
		prev += v[i];
	}
}

int triSup(int N, float m [N][N]){
	int x = 1;
	for(int i = 0;i<N;i++){
		for(int j = 0;j<i;j++){
			 if(m[i][j]) x = 0;
		}
	}
	return x;
}

void swap(float x, float y){
	float tmp = x;
	x = y;
	y = tmp;
}

void transposta (int N, float m[N][N]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < i; j++)
        	swap(m[i][j],m[j][i]);  
    }
}

void addTo(int N, int M, int a[N][M], int b [N][M]){
	for(int i = 0;i<N;i++){
		for(int j = 0;j<M;j++){
			a[i][j] += b[i][j];
		}
	}
}

int unionSet (int N, int v1[N], int v2[N], int r[N]) {
    int len = 0;
    for(int i = 0; i < N; i++) {
        r[i] = v1[i] + v2[i];
        len += r[i]; 
    }
    return len;
}

int intersectSet (int N, int v1[N], int v2[N],int r[N]) {
    int len = 0;
    for(int i = 0; i < N; i++) {
        r[i] = v1[i] && v2[i];
        len += r[i];
    }
    return len;
}

int intersectMSet (int N, int v1[N], int v2[N],int r[N]) {
    int len = 0;
    for(int i = 0; i < N; i++) {
        r[i] = v1[i] < v2[i] ? v1[i] : v2[i];
        len += r[i]; 
    }
    return len;
}

int unionMSet (int N, int v1[N], int v2[N], int r[N]) {
    int len = 0;
    for(int i = 0; i < N; i++) {
        r[i] = v1[i] + v2[i];
        len += r[i]; 
    }
    return len;
}

int cardinalMSet (int N, int v[N]) {
    int len = 0;
    for(int i = 0; i < N; i++) len += v[i];
    return len;
}

typedef enum movimento {Norte, Oeste, Sul, Este} Movimento;
typedef struct posicao{
	int x, y;
} Posicao;

Posicao posFinal(Posicao inicial, Movimento mov[], int N){
	for(int i = 0;i<N;i++){
		Movimento x = mov[i];
		switch(x){
			case Norte:
				inicial.y++;
			break;

			case Sul:
				inicial.y++;
			break;

			case Este:
				inicial.x++;
			break;

			case Oeste:
				inicial.x--;
			break;
		}
	}
	return inicial;
}

int caminho (Posicao inicial, Posicao final, Movimento mov[], int N) {
    int* xi = &inicial.x;
    int* yi = &inicial.y;
    int xf = final.x, yf = final.y, i;
    for(i = 0; i < N; i++) {
        if((*xi) < xf) {
            (*xi)++;
            mov[i] = Este;
        }
        else if ((*xi) > xf) {
            (*xi)--;
            mov[i] = Oeste;
        } 
        else if ((*yi) < yf) {
            (*yi)++;
            mov[i] = Norte;
        }
        else if ((*yi) > yf) {
            (*yi)--;
            mov[i] = Sul;
        }
        else break;
    }
    if(inicial.x != final.x || inicial.y != final.y) return -1;
    else return i;
}

int manDist(int x, int y, int x0, int y0) {return abs(x - x0) + abs(y - y0);}

int maisCentral (Posicao pos[], int N) {
    int minDist = manDist(pos[0].x,pos[0].y,0,0);
    int ans = 0, i;
    for(i = 1; i < N; i++) {
        if(manDist(pos[i].x,pos[i].y,0,0) < minDist) {
            ans = i;
            minDist = manDist(pos[i].x,pos[i].y,0,0);
        }
    }
    return ans;
}

int vizinhos (Posicao p, Posicao pos[], int N) {
    int ans = 0;
    for(int i = 0; i < N; i++) {
        if(manDist(pos[i].x,pos[i].y,p.x,p.y) == 1) ans++;
    }
    return ans;
}

void getLine(char str[]) {
    while(fgets(buffer,MAXLINE,stdin) == NULL)
        puts("Erro a ler input!");
    buffer[strcspn(buffer,"\r\n")] = 0;
    if(str != buffer) strcpy(str, buffer);
}

int getInt() {
    getLine(buffer);
    return atoi(buffer);
}

void getIntArray(int* start, int* end) {
    for( ; start != end; start++) {
        printf("Insere um valor: ");
        assert(scanf("%d", start) == 1);
    }
}

void getIntMatrix(int m, int n, int mat[m][n]) {
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            printf("Linha %d, coluna %d: ",i,j);
            assert(scanf("%d",&mat[i][j]) == 1);
        }
    }
}

void getFloatMatrix(int m, int n, float mat[m][n]) {
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            printf("Linha %d, coluna %d: ",i,j);
            assert(scanf("%f", &mat[i][j]) == 1);
        }
    }
}

void printArray(int arr[], int lim) {
    printf("[");
    for(int i = 0; i < lim; i++) {
        if(i == lim - 1) printf("%d",arr[i]);
        else printf("%d, ",arr[i]);
    }
    printf("]\n");
}

void printFloatMatrix(int m, int n, float mat[m][n]) {
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++)
            printf("%.3f ",mat[i][j]);
        putchar('\n');
    }
}

void printIntMatrix(int m, int n, int mat[m][n]) {
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++)
            printf("%6d ",mat[i][j]);
        putchar('\n');
    }
}

void getPosArray(int N, Posicao poss[N]) {
    for(int i = 0; i < N; i++) {
        printf("Posição %d: ",i);
        assert(scanf("%d %d",&poss[i].x,&poss[i].y) == 2);
    }
}

void getMovs(int len, Movimento movs[len]) {
    for(int i = 0; i < len; i++) {
        printf("Letra correspondente à direção (N,S,E,W): ");
        char c, x;
        while((x = getchar()) != '\n' && x) {}
        switch(c = getchar()) {
            case 'n':
            case 'N': movs[i] = Norte; break;
            case 'e':
            case 'E': movs[i] = Este; break;
            case 's':
            case 'S': movs[i] = Sul; break;
            case 'O':
            case 'o':
            case 'w':
            case 'W': movs[i] = Oeste; break;
        }
    }
}

int main(int argc, char const *argv[])
{
    char* s1 = malloc(MAXLINE * sizeof(char));
    char* s2 = malloc(MAXLINE * sizeof(char));
    int opcao, num, num1, num2, resp, x, y;
    printf("Insere o numero correspondente ao exercicio: ");
    getLine(buffer);
    opcao = atoi(buffer);
    switch (opcao)
    {
        case 1:
            question1();
            break;
        case 2:
            question2();
            break;
        case 3:
            question3();
            break;
        case 4:
            printf("Introduz um valor: ");
            num = getInt();
            int n = bitsUm(num);
            printf("Resposta: %d\n",n);
            break;
        case 5:
            printf("Introduz um valor: ");
            num = getInt();
            printf("Resposta: %d\n",trailingZ(num));
            break;
        case 6:
            printf("Introduz um valor: ");
            assert(scanf("%d",&num) == 1);
            printf("Resposta: %d\n",qDig(num));
            break;
        case 7:
            printf("String 1: ");
            getLine(s1);
            printf("String 2: ");
            getLine(s2);
            mystrcat(s1,s2);
            printf("String concatenada: %s",s1);
            break;
        case 8:
            getLine(s1);
            mystrcpy(s2,s1);
            printf("%s [ORIGINAL] - address %p\n",s1,s1);
            printf("%s [COPIADA] - address %p\n",s2,s2);
            break;
        case 9:
            printf("String 1: ");
            getLine(s1);
            printf("String 2: ");
            getLine(s2);
            num = mystrcmp(s1,s2);
            printf("Resultado: %d", num);
            break;
        case 10:
            printf("Palheiro: ");
            getLine(s1);
            printf("Agulha: ");
            getLine(s2);
            char* ans = mystrstr(s1,s2);
            printf("%s",ans);
            break;
        case 11:
            getLine(s1);
            mystrrev(s1);
            printf("%s",s1);
            break;
        case 12:
            getLine(s1);
            mystrnoV(s1);
            printf("%s",s1);
            break;
        case 13:
            printf("String: ");
            getLine(s1);
            printf("Tamanho para truncar: ");
            assert(scanf("%d",&num) == 1);
            truncW(s1,num);
            printf("%s",s1);
            break;
        case 14:
            getLine(s1);
            printf("%c",charMaisfreq(s1));
            break;
        case 15:
            getLine(s1);
            printf("%d",iguaisConsecutivos(s1));
            break;
        case 16:
            getLine(s1);
            printf("Diferentes consecutivos: %d\n",difConsecutivos(s1));
            break;
        case 17:
            getLine(s1);
            getLine(s2);
            printf("%d\n",maiorPrefixo(s1,s2));
            break;
        case 18:
            getLine(s1);
            getLine(s2);
            printf("%d\n",maiorSufixo(s1,s2));
            break;
        case 19:
            getLine(s1);
            getLine(s2);
            printf("%d\n",sufPref(s1,s2));
            break;
        case 20:
            getLine(s1);
            printf("%d\n",contaPal(s1));
            break;
        case 21:
            getLine(s1);
            printf("%d\n",contaVogais(s1));
            break;
        case 22:
            getLine(s1);
            getLine(s2);
            resp = contida(s1,s2);
            if(resp) printf("Verdadeiro.\n");
            else printf("Falso.\n");
            break;
        case 23:
            getLine(s1);
            resp = palindrome(s1);
            if(resp) printf("Verdadeiro.\n");
            else printf("Falso.\n");
            break;
        case 24:
            getLine(s1);
            resp = remRep(s1);
            printf("%s - length: %d", s1, resp);
            break;
        case 25:
            getLine(s1);
            resp = limpaEspacos(s1);
            printf("%s - length: %d", s1, resp);
            break;
        case 26: {
            printf("Tamanho da lista ordenada: ");
            assert(scanf("%d",&num) == 1);
            int nums[num+1];
            getIntArray(nums,nums + num);
            printf("Valor a inserir: ");
            assert(scanf("%d",&resp) == 1);
            insere(nums,num,resp);
            for(int i = 0; i <= num; i++) printf("%d ", nums[i]);
            break; }
        case 27: {
            printf("Tamanho da lista ordenada 1: ");
            assert(scanf("%d",&num1) == 1);
            int nums1[num1];
            getIntArray(nums1,nums1 + num1);
            printf("Tamanho da lista ordenada 2: ");
            assert(scanf("%d",&num2) == 1);
            int nums2[num2];
            getIntArray(nums2,nums2 + num2);
            int r[num1+num2];
            recursive_merge(r,nums1,nums2,num1,num2);
            for(int i = 0; i < num1 + num2; i++) printf("%d ",r[i]);
            break; }
        case 28: {
            printf("Tamanho da lista: ");
            assert(scanf("%d",&num) == 1);
            int nums[num];
            getIntArray(nums, nums + num);
            printf("Limite mínimo e máximo: ");
            assert(scanf("%d %d",&num1,&num2) == 2);
            resp = crescente(nums,num1,num2);
            if(resp) printf("Verdadeiro.\n");
            else printf("Falso.\n");
            break; }
        case 29: {
            printf("Tamanho da lista: ");
            assert(scanf("%d",&num) == 1);
            int nums[num];
            getIntArray(nums, nums + num);
            resp = retiraNeg(nums,num);
            printArray(nums,resp);
            printf("Resposta: %d", resp);
            break; }
        case 30: {
            printf("Tamanho da lista crescente: ");
            assert(scanf("%d",&num) == 1);
            int nums[num];
            getIntArray(nums, nums + num);
            resp = menosFreq(nums,num);
            printf("Resposta: %d", resp);
            break; }
        case 31: {
            printf("Tamanho da lista crescente: ");
            assert(scanf("%d",&num) == 1);
            int nums[num];
            getIntArray(nums, nums + num);
            resp = maisFreq(nums,num);
            printf("Resposta: %d", resp);
            break; }
        case 32: {
            printf("Tamanho da lista: ");
            assert(scanf("%d",&num) == 1);
            int nums[num];
            getIntArray(nums, nums + num);
            resp = maxCresc(nums,num);
            printf("Resposta: %d", resp);
            break; }
        case 33:
        case 34: {
            printf("Tamanho da lista: ");
            assert(scanf("%d",&num) == 1);
            int nums[num];
            getIntArray(nums, nums + num);
            resp = elimRep(nums,num);
            printArray(nums,resp);
            printf("Resposta: %d", resp);
            break; }
        case 35: {
            printf("Tamanho da lista ordenada 1: ");
            assert(scanf("%d",&num1) == 1);
            int nums1[num1];
            getIntArray(nums1, nums1 + num1);
            printf("Tamanho da lista ordenada 2: ");
            assert(scanf("%d",&num2) == 1);
            int nums2[num2];
            getIntArray(nums2, nums2 + num2);
            resp = comunsOrd(nums1,num1,nums2,num2);
            printf("Resposta: %d", resp);
            break; }
        case 36: {
            printf("Tamanho da lista ordenada 1: ");
            assert(scanf("%d",&num1) == 1);
            int nums1[num1];
            getIntArray(nums1, nums1 + num1);
            printf("Tamanho da lista ordenada 2: ");
            assert(scanf("%d",&num2) == 1);
            int nums2[num2];
            getIntArray(nums2, nums2 + num2);
            resp = comuns(nums1,num1,nums2,num2);
            printf("Resposta: %d", resp);
            break; }
        case 37: {
            printf("Tamanho da lista: ");
            assert(scanf("%d",&num) == 1);
            int nums[num];
            getIntArray(nums, nums + num);
            resp = minInd(nums,num);
            printf("Resposta: %d", resp);
            break; }
        case 38: {
            printf("Tamanho da lista: ");
            assert(scanf("%d",&num) == 1);
            int nums[num];
            getIntArray(nums, nums + num);
            int nums1[num];
            somasAc(nums,nums1,num);
            printArray(nums1,num);
            break; }
        case 39: {
            printf("Número de linhas: ");
            assert(scanf("%d",&num1) == 1);
            float nums[num1][num1];
            getFloatMatrix(num1,num1,nums);
            resp = triSup(num1,nums);
            printFloatMatrix(num1,num1,nums);
            if(resp) printf("Verdadeiro\n");
            else printf("Falso\n");
            break; }
        case 40: {
            printf("Número de linhas: ");
            assert(scanf("%d",&num1) == 1);
            float nums[num1][num1];
            getFloatMatrix(num1,num1,nums);
            transposta(num1,nums);
            printFloatMatrix(num1,num1,nums);
            break; }
        case 41: {
            printf("Número de linhas: ");
            assert(scanf("%d",&num1) == 1);
            printf("Número de colunas: ");
            assert(scanf("%d",&num2) == 1);
            printf("Matriz 1\n");
            int mat1[num1][num2];
            int mat2[num1][num2];
            getIntMatrix(num1,num2,mat1);
            printf("Matriz 2\n");
            getIntMatrix(num1,num2,mat2);
            addTo(num1,num2,mat1,mat2);
            printIntMatrix(num1,num2,mat1);
            break; }
        case 42: {
            printf("Tamanho dos sets:");
            assert(scanf("%d",&num) == 1);
            printf("Set 1\n");
            int set1[num];
            int set2[num];
            getIntArray(set1, set1 + num);
            printf("Set 2\n");
            getIntArray(set2, set2 + num);
            int setx[num];
            resp = unionSet(num,set1,set2,setx);
            printArray(setx,num);
            break; }
        case 43: {
            printf("Tamanho dos sets:");
            assert(scanf("%d",&num) == 1);
            printf("Set 1\n");
            int set1[num];
            int set2[num];
            getIntArray(set1, set1 + num);
            printf("Set 2\n");
            getIntArray(set2, set2 + num);
            int setx[num];
            resp = intersectSet(num,set1,set2,setx);
            printArray(setx,num);
            break; }
        case 44: {
            printf("Tamanho dos sets:");
            assert(scanf("%d",&num) == 1);
            printf("Set 1\n");
            int set1[num];
            int set2[num];
            getIntArray(set1, set1 + num);
            printf("Set 2\n");
            getIntArray(set2, set1 + num);
            int setx[num];
            resp = intersectMSet(num,set1,set2,setx);
            printArray(setx,num);
            break; }
        case 45: {
            printf("Tamanho dos sets:");
            assert(scanf("%d",&num) == 1);
            printf("Set 1\n");
            int set1[num];
            int set2[num];
            getIntArray(set1, set1 + num);
            printf("Set 2\n");
            getIntArray(set2, set2 + num);
            int setx[num];
            resp = unionMSet(num,set1,set2,setx);
            printArray(setx,num);
            break; }
        case 46: {
            printf("Tamanho do set: ");
            assert(scanf("%d", &num) == 1);
            int set[num];
            getIntArray(set, set + num);
            resp = cardinalMSet(num,set);
            printf("Resposta: %d", resp);
            break; }
        case 47: {
            printf("Posição inicial (x , y): ");
            assert(scanf("%d %d",&num1,&num2) == 2);
            printf("Número de movimentos: ");
            assert(scanf("%d",&num) == 1);
            Posicao pi = {num1,num2};
            Movimento movs[num];
            getMovs(num,movs);
            Posicao pf = posFinal(pi,movs,num);
            printf("Posição final: (%d,%d)",pf.x,pf.y);
            break; }
        case 48: {
            printf("Posição inicial (x, y): ");
            assert(scanf("%d %d",&num1,&num2) == 2);
            printf("Posição final (x, y): ");
            assert(scanf("%d %d",&x,&y) == 2);
            printf("Número de movimentos: ");
            assert(scanf("%d",&num) == 1);
            Posicao pi = {num1,num2};
            Posicao pf = {x,y};
            Movimento movs[num];
            int resp = caminho(pi,pf,movs,num);
            if(resp < 0) printf("Caminho não encontrado.");
            else {
                printf("O caminho é: ");
                for(int i = 0; i < resp; i++) {
                    if(movs[i] == Norte) printf("Norte ");
                    if(movs[i] == Sul) printf("Sul ");
                    if(movs[i] == Este) printf("Este ");
                    if(movs[i] == Oeste) printf("Oeste ");
                }
            }
            break; }
        case 49: {
            printf("Número de posições: ");
            assert(scanf("%d", &num) == 1);
            Posicao poss[num];
            getPosArray(num,poss);
            resp = maisCentral(poss,num);
            printf("Resposta: %d",resp);
            break; }
        case 50:
            printf("Posição central: ");
            assert(scanf("%d %d",&num1,&num2) == 2);
            Posicao pc = {num1,num2};
            printf("Número de posições: ");
            assert(scanf("%d", &num) == 1);
            Posicao poss[num];
            getPosArray(num,poss);
            resp = vizinhos(pc,poss,num);
            printf("Resposta: %d",resp);
            break;
    }
    printf("\n");
    return 0;
}
