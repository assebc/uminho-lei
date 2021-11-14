#include <stdio.h>
#include <string.h>

int eVogal (char c) {
	// verifica se é vogal
	char *vogal = "aeiouAEIOU";

	while (*vogal !? '\0' && c != *vogal) vogal++;

	return (*vogal != '\0');
}

int contaVogais (char *s) {
	int i;
	int vogais = 0;
	
	for (i=0;s[i]!='\0';i++)
		if (eVogal(s[i]) )
			vogais++;
	return vogais;
}

/*
int retiraVogaisRep (char *s){

	int c, j;
	int i = 0;

	while (s[i]!='\0'){
		if (eVogal ( (s[i]) && s[i+1]) == s[i]){
			// remover o s[i+1] e adicionar ao contador
			c++;
			for (j=i+1;s[j]!='\0';j++)
				s[j] = s[j+1];
		} else i++;

	}

	return c;

}
*/

int retiraVogaisRep (char *s){

	// percorrer s e contruir aux inicializando indice
	int c, r, w;
	r = w = 0;

	// reconstrução de s
	while (s[r] != '\0'){
		if (eVogal ( (s[r]) && s[r+1]) == s[r]){
			c++;
			r++;
		} else {
			s[w] = s[r];
			w++;
			r++;
		}
	}

	s[w] = '\0';

	return c;
}

int duplicaVogais (char *s) {
	int c, r, w;
	r = w = 0;
	while (s[r] != '\0'){
		if (eVogal (s[r])){
			s[w] = s[w+1] = s[r]; c++; r++; w+=2;
			
		} else {
			s[w] = s[r];
			w++;
			r++;
		}
	}	

	s[w] = '\0';

	return c;
}

int main(){
	char s1[100] = "Estaa e umaa string com duuuplicadooos";
	int x;

	printf("Testes\n");
	printf("A string \"%s\" tem %d vogais\n", s1, contaVogais(s1));

	x = retiraVogaisRep(s1);
	printf("Foram retiradas %d vogais, resultando em \"%s \"\n", x, s1);

	x = duplicaVogais(s1);
	printf("Foram acrescentadas %d vogais, resultando em \"%s\"\n", x, s1);

	printf("\n Fim dos testes\n");

	return 0;
}