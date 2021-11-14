/**
 * @file logics.c
 * @brief Ficheiro com funções relativas a operações com arrays
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "manpln.h"
#include "logics.h"
#include "stack.h"
#include "eval.h"


/**
 * @brief Função que inverte um array
 *
 * Objetivo de auxiliar outras funções que necessitem inverter um array
 *
*/
void inverteArray(STACK *input, STACK *output) { // função auxiliar para inverter um array

    while(input->n_elems > 0){
    DATA x = pop(input);
                            // case quando x é long
            switch(x.type){                                     
                case 1 :                                        
                push_LONG(output, x.LONG);
                break;

                case 2 :                                        
                push_DOUBLE(output, x.DOUBLE);
                break;

                case 4 :                                                                              
                push_CHAR(output, x.CHAR);
                break;

                case 8 :                                        
                push_STRING(output, x.STRING);
                break;

                case 16 :
                push_ARRAY(output, x.ARRAY);                                   
                break;

                case 32 :
                push_BLOCO(output, x.BLOCO);
                break;
            }
    }
}

/**
 * @brief Função que concatena duas strings
 *
 * Obtendo duas arrays, ou seja duas stacks copia a segunda array e a primeira, invertendo ao fim a primeira array
 *
*/
void concatenar(STACK *pri, STACK *sec){

	STACK *aux = new_stack();

	while(sec->n_elems > 0){
	DATA x = pop(sec);
                            
            switch(x.type){                                     
                case 1 :                       // case quando x é long                                   
                push_LONG(aux, x.LONG);
                break;

                case 2 :                                        
                push_DOUBLE(aux, x.DOUBLE);
                break;

                case 4 :                                                                              
                push_CHAR(aux, x.CHAR);
                break;

                case 8 :                                        
                push_STRING(aux, x.STRING);
                break;

                case 16 :
                push_ARRAY(aux, x.ARRAY);                                   
                break;

                case 32 :
                    break;
            }
    }

    inverteArray(aux, pri);
    free(aux);     
}

/**
 * @brief Função que converte qualquer tipo de dados para string
 *
 * Seja qual for o tipo do elemento introduzido converte para a sua representação em string
 *
*/
char *DATAtoSTR(DATA elem) {
    STACK *store = new_stack();
    char *string = malloc(sizeof(char)*10240);
    memset(string, '\0', strlen(string));   

    switch (elem.type) {

            case 1 :
                sprintf(string, "%ld", elem.LONG);
                break;

            case 2 :
                sprintf(string, "%f", elem.DOUBLE);
                break;

            case 4 :
                string[0] = elem.CHAR;
                break;

            case 8 :
                string = strdup(elem.STRING);
                break;

            case 16 :
                inverteArray(elem.ARRAY, store);
                for (long i = 0;i<elem.ARRAY->n_elems;i++){
                    DATA x = pop(store);
                    DATAtoSTR(x);
                }
                break;

            case 32 :
                string = strdup(elem.BLOCO);
                break;
        }

    return string;
}

/*
    
    Vou meter aqui o que pensei em fazer para a filter:
    -faz-se a função map com o bloco dado (se calhar é melhor ser uma cópia do bloco), 
    o array dado (mais uma vez melhor ser copia) e com um array vazio;

    -esse map vai nos dar um array chamado result com o bloco calculado para cada elemento;

    -com esse tal result podemos verificar que resultados do map dariam 0 ou 
    diferente para cada elemento do array dado e assim retira-se os elementos do array original
    que com bloco deram 0;

    -para isso vai-se dando pop ao resultado e ao array (ao mesmo tempo) e 
    se o pop do resultado der 0 n se volta a dar push ao elemento do array (é melhor dar push para outra
    stack vazia)

    -no fim inverte-se o array e damos push desse array para a stack;
}
*/
/**
 * @brief "Função "," para arrays com ou sem utilizar blocos
 *
 * Função que filtra a posição do input no input caso seja diferente de 0
 *
*/
void filter(STACK *stack, DATA bloco, DATA *vars){

    DATA array = pop(stack);
    STACK *auxmap = new_stack();     // array que irá conter resultado pôs map
    char *cpy = strdup(bloco.BLOCO); // cópia do bloco
    STACK *copia = array.ARRAY;       // cópia do array
    STACK copia2 = *copia;
    STACK *store = new_stack();      // array pre invertido
    inverteArray(&copia2, store);     // array invertido
    STACK *result = new_stack();     // array final

    long vezes = (array.ARRAY)->n_elems;

    for (long i = vezes; i > 0; i--){
        DATA elem = pop(store);
        eval(strcat(DATAtoSTR(elem), strndup(cpy + 1, strlen(cpy) - 1)), auxmap, vars);
        cpy = strdup(bloco.BLOCO);
    }

    for (long j = vezes; j > 0; j--) {
        DATA elem2 = pop(auxmap);
        DATA elemresult = pop(array.ARRAY);
        switch(elem2.type){
            case 1 :
                if (elem2.LONG != 0)
                    push_LONG(result, elemresult.LONG);
                break;

            case 2 :
                if (elem2.DOUBLE != 0)
                    push_DOUBLE(result, elemresult.DOUBLE);
                break;

            case 4 :
                if (elem2.CHAR != '0')
                    push_CHAR(result, elemresult.CHAR);
                break;

            case 8 :
                if (strcmp(elem2.STRING, "0") != 0)
                    push_STRING(result, elemresult.STRING);
                break;

            case 16 :
                break;

            case 32 :               // dentro de arrays não há blocos
                break;   
        }
    }

    STACK copiainvertida = *result;
    STACK *resulta = new_stack();               // array pre invertido
    inverteArray(&copiainvertida, resulta);     // array invertido
    push_ARRAY(stack, resulta);

}

/**
 * @brief Função range e filter ","
 *
 * Caso seja long fará um array com todos os longs entre 0 e x, não inclusivé (range semelhante ao de Python)
 * Caso seja um array devolve o tamanho do array, ou seja, a quantidade de elementos existentes dentro do array
 * Caso seja bloco vai filtrar as posições em que a condição dos blocos é verdade
 * 
*/
void range(STACK *s, DATA *vars){
    DATA x = pop(s);
    STACK *array = new_stack();
    long i;

    switch(x.type){                             // switch case para os diferentes tipos de x
        case 1 :
            for (i = 0;i<x.LONG;i++) {
                push_LONG(array, i);
            }
                push_ARRAY(s, array);

            break;

        case 2 :
            break;

        case 4 :
            break;

        case 8 :
            push_LONG(s, strlen(x.STRING));
            break;

        case 16 :              
            push_LONG(s, x.ARRAY->n_elems);
            break;

        case 32 :
            filter(s, x, vars);
            break;
    }
}

/**
 * @brief Função auxiliar para a função do operador S/
 *
 * Separa a string por whitespaces
 *
*/
void whiteSpaces(STACK *stack, char *string) {
    
    char *delims = " \t\n";
    char *cpy = strdup(string);
    STACK *array = new_stack();
                
    for (char *token = strtok(cpy, delims); token != NULL; token = strtok(NULL, delims)) {
            char *aspeado = malloc(sizeof(char)*strlen(string));
            memset(aspeado, '\0', strlen(aspeado));
            memset(aspeado, '\"', 1);
            strcat(strcat(aspeado, token), "\"");
            push_STRING(array, aspeado);         
    }
    
    push_ARRAY(stack, array);
}

/**
 * @brief Função auxiliar para a função do operador S/
 *
 * Separa a string por whitespaces caso, o topo da stack seja string
 *
*/
void sspace(STACK *s){
    DATA x = pop(s);

    switch(x.type){
        case 1 :
            break;

        case 2 :
            break;

        case 4 :
            break;

        case 8 :
            whiteSpaces(s, x.STRING);            
            break;

        case 16 :
            break;

        case 32 :
            break;
    }
}

/**
 * @brief Função auxiliar para a função do operador N/
 *
 * Separa a string por newlines
 *
*/
void newLines(STACK *stack, char *string) {

    char *delims = "\n";
    char *cpy = strdup(string);
    STACK *array = new_stack();
                
    for (char *token = strtok(cpy, delims); token != NULL; token = strtok(NULL, delims)) {
            push_STRING(array, token);
    }
    
    push_ARRAY(stack, array);
}

/**
 * @brief Função do operador N/
 *
 * Separa a string por newlines caso o topo da stack seja string
 *
*/
void nspace(STACK *s){
    DATA x = pop(s);

    switch(x.type){
        case 1 :
            break;

        case 2 :
            break;

        case 4 :
            break;

        case 8 :
            newLines(s, x.STRING);
            break;

        case 16 :
            break;

        case 32 :
            break;
    
    }
}

/**
 * @brief Função "=" para arrays 
 *
 * Percorre o array em busca de uma array incluida ou igual à outra
 *
*/
void seek(long n, STACK *array, STACK *stack) {

    STACK arraycpy = *array;
    
    DATA nelem; long i = 0;
    long ne = array->n_elems - n;

    while(i < ne) {
        nelem = pop(&arraycpy); 
        i++;
    }

    switch(nelem.type){
        case 1 :
            push_LONG(stack, nelem.LONG);
            break;

        case 2 :
            push_DOUBLE(stack, nelem.DOUBLE);
            break;

        case 4 :
            push_CHAR(stack, nelem.CHAR);
            break;

        case 8 :
            push_STRING(stack, nelem.STRING);
            break;

        case 16 :
            push_ARRAY(stack, nelem.ARRAY);
            break;

        case 32 :
            break;
    
    }
}

/**
 * @brief Função "=" para strings
 *
 * Percorre a string em busca de uma string incluida ou igual à outra
 *
*/
void seeknstring(long n, char *string, STACK *stack) {

    char *ch = strndup(string + n, 1);
    push_STRING(stack, ch);
    
}

/**
 * @brief Função "<" para arrays 
 *
 * Retira do array os elementos menores do que n valor dado ao longo que percorre o array
 *
*/
void takeXstart(long n, STACK *array) { // n <

    long vezes = (array->n_elems) - n;

    for(long i = 0; i < vezes; i++) {
        pop(array);
    }
}

/**
 * @brief Função ">" para arrays 
 *
 * Retira do array os elementos maiores do que n valor dado enquanto que percorre o array invertendo-a ao fim para obter a stack na mesma ordem
 * 
 * @returns Faz return da stack
*/
STACK *takeXend(long n, STACK *array) { // n >

    STACK *store = new_stack();
    STACK *aux = new_stack();

    for(long i = 0; i < n; i++) {
        
        DATA z = pop(array);

        switch (z.type) {

            case 1 :
                push_LONG(aux, z.LONG);
                break;

            case 2 :
                push_DOUBLE(aux, z.DOUBLE);
                break;

            case 4 :
                push_CHAR(aux, z.CHAR);
                break;

            case 8 :
                push_STRING(aux, z.STRING);
                break;

            case 16 :
                push_ARRAY(aux, z.ARRAY);
                break;

            case 32 :
            break;
        }
    }

    inverteArray(aux, store);
    free(aux); 
    return store;
}

/**
 * @brief Função "*" para arrays 
 *
 * Função que concatena n vezes arrays
 *
*/
void concatvar(STACK *s, long i){
    
    STACK *aux = new_stack();
    STACK aux2 = *s;
    i--;

    while(i > 0){

        aux2 = *s;

        concatenar(aux,&aux2);
        
        i--;
    }

    concatenar(s,aux);
}

/**
 * @brief Função "*" para arrays 
 *
 * Função que concatena n vezes strings
 *
*/
void concatvarstr(char *string, long n) {

    char *copia = strdup(string);

    for(long i = 1; i < n; i++) {

        strcat(string, copia);
    }
}

/**
 * @brief Função "+" para strings
 *
 * Função que concatena strings
 *
 * @returns String concatenada não alterando as originais
*/
char *concatstr(char *dest, char *src) {    // devolve as strings concatenadas sem alterar as originais

    long dsize = sizeof(char)*(strlen(dest)+strlen(src));
    char *d = malloc(dsize);
    
    strncpy (d, dest, dsize - 1);
    d[dsize - 1] = '\0';
    size_t n = strlen (d);
    strncat (d, src, dsize - n);
    
    return d;
}

/**
 * @brief Função que remove o ultimo elemento de um array
 *
 * Função "(" para arrays
 *
*/
void removeUltArray(STACK *stack, STACK *array) {
    
    STACK copia = *array;
    STACK *store = new_stack();
    STACK *store2 = new_stack();

    inverteArray(&copia, store);
    inverteArray(store, store2);

    DATA z = pop(store2);
    push_ARRAY(stack, store2);
    
    switch (z.type) {

            case 1 :
                push_LONG(stack, z.LONG);
                break;

            case 2 :
                push_DOUBLE(stack, z.DOUBLE);
                break;

            case 4 :
                push_CHAR(stack, z.CHAR);
                break;

            case 8 :
                push_STRING(stack, z.STRING);
                break;

            case 16 :
                push_ARRAY(stack, z.ARRAY);
                break;

            case 32 :
                break;
        }
}

/**
 * @brief Função que remove o primeiro elemento de um array
 *
 * Função ")" para arrays
 *
*/
void removePrimArray(STACK *stack, STACK *array) {

    STACK copia = *array;
    STACK *store = new_stack();
    STACK *store2 = new_stack();

    inverteArray(&copia, store);

    DATA z = pop(store);

    inverteArray(store, store2);

    push_ARRAY(stack, store2);

    switch (z.type) {

            case 1 :
                push_LONG(stack, z.LONG);
                break;

            case 2 :
                push_DOUBLE(stack, z.DOUBLE);
                break;

            case 4 :
                push_CHAR(stack, z.CHAR);
                break;

            case 8 :
                push_STRING(stack, z.STRING);
                break;

            case 16 :
                push_ARRAY(stack, z.ARRAY);
                break;

            case 32 :
                break;
        }

}

/**
 * @brief Função que transforma um long num array com um elemento
 *
 * Função que concatena um long a um array vazio 
 *
*/
void concatSTART(DATA elem, STACK* array) { // transforma um long num array com um elemento

    STACK *store = new_stack();
    inverteArray(array, store);

    switch (elem.type) {

            case 1 :
                push_LONG(store, elem.LONG);
                break;

            case 2 :
                push_DOUBLE(store, elem.DOUBLE);
                break;

            case 4 :
                push_CHAR(store, elem.CHAR);
                break;

            case 8 :
                push_STRING(store, elem.STRING);
                break;

            case 16 :
                push_ARRAY(store, elem.ARRAY);
                break;

            case 32 :
                break;
    }

    inverteArray(store, array);
}

/**
 * @brief Função que concatena um elemento de tipo DATA no array
 *
 * Concatena um elemento dado como input em um array
 *
 * @return Faz return à string do array mais o elemento concatenado
*/
char *concatAny(DATA elem, char *string) {

    long tamanho = sizeof(char)*(strlen(string)+2);
    char *caratere = malloc(tamanho);
    caratere[tamanho - 1] = '\0';

    switch (elem.type) {

            case 1 :
                caratere[0] = (char)elem.LONG;
                break;

            case 2 :
                caratere[0] = (char)elem.DOUBLE;
                break;

            case 4 :
                caratere[0] = elem.CHAR;
                break;

            case 8 :
                break;

            case 16 :
                break;

            case 32 :
                break;
        }

    strcat(caratere, string);
    return caratere;

}

/**
 * @brief Função que procura substring numa string
 *
 * Percorre a string procurando uma substring de tamanho n
 *
 * @return return = -1 case não exista, caso contrário devolve o indice da substring na string
*/
long strsearch(char *sub, char *string) {
    
    long n = strlen(sub);
    long index = -1;

    for(long i = 0; strcmp(string + i + n - 1, "\0") != 0 ; i++) {
        if (strcmp(strndup(string + i, n), sub) == 0) {
            index = i;
            break;
        }
    }
    
    return index;
}

/**
 * @brief Função que procura um array dentro de um array
 *
 * Percorre o array até encontrar o segundo array, vai printando como string as várias vezes em que o array aparece no input
 * 
*/
void subarray(STACK *stack, char *sub, char *string) {
    
    char *delims = sub;
    char *cpy = strdup(string);
    STACK *array = new_stack();
                
    for (char *token = strtok(cpy, delims); token != NULL; token = strtok(NULL, delims)) {
            push_STRING(array, token);
    }
    
    push_ARRAY(stack, array);
}

/* FUNÇÕES LIGADAS A BLOCOS */

/**
 * @brief Função "~"
 *
 * Função que executa o código de blocos
 *
*/
void aplica(STACK *stack, DATA bloco, DATA *vars) {

    DATA elem = pop(stack);
 
    eval(strcat(DATAtoSTR(elem), strndup(bloco.BLOCO + 1, strlen(bloco.BLOCO) - 1)), stack, vars);

}

/**
 * @brief Função "%"
 *
 * Função que realiza uma espécia de map para strings utilizando o bloco
 *
*/
void mapstring(STACK *stack, DATA bloco, char * string, DATA *vars) {

    char *cpy = strdup(string); // cópia da string
    push_STRING(stack, cpy); // colocar a string numa stack

    STACK copia = *stack; // fazer copia da stack com astring
    STACK *store = new_stack(); // guardar a string na stack
    inverteArray(&copia, store);

    long vezes = strlen(string);

    for (long i = vezes; i > 0; i--){

        DATA elem = pop(store);
        eval(strcat(DATAtoSTR(elem), strndup(cpy + 1, strlen(cpy) - 1)), stack, vars);
        cpy = strdup(bloco.BLOCO);
    }
    push_STRING(stack, cpy);
}

/**
 * @brief Função "%"
 *
 * Função que realiza uma espécia de map para arrays utilizando o bloco
 *
*/
void map(STACK *stack, DATA bloco, STACK *array, DATA *vars) {

    STACK *result = new_stack();
    char *cpy = strdup(bloco.BLOCO); //cópia do bloco
    
    STACK copia = *array;
    STACK *store = new_stack();
    inverteArray(&copia, store);

    long vezes = array->n_elems;

    for (long i = vezes; i > 0; i--){

        DATA elem = pop(store);
        eval(strcat(DATAtoSTR(elem), strndup(cpy + 1, strlen(cpy) - 1)), result, vars);
        cpy = strdup(bloco.BLOCO);
    }
    push_ARRAY(stack, result);
}

/**
 * @brief Função final da "*" para blocos aplicado a arrays
 *
 * Função que faz umas espécie de fold para arrays
 *
*/
void fold(STACK *stack, DATA bloco, STACK *array, DATA *vars){

    long nelems = array->n_elems - 1;

    STACK *store = new_stack();
    inverteArray(array, store);

    char *operator = strndup((bloco.BLOCO + 2), strlen(bloco.BLOCO) - 2); // tira as chavetas do bloco

    for(long i = 0; i < nelems; i++) {

        DATA a = pop(store);
        DATA b = pop(store);

       eval(strcat(strcat(strcat(strcat(DATAtoSTR(a), " "), DATAtoSTR(b)), " "), operator), store, vars); // transforma a e b em string e junta com o bloco na forma de string
    }

    push_ARRAY(stack, store);
}


/**
 * @brief Função que verifica se um array está ordenado por ordem crescente
 *
 * @returns um bool que indica se está ou não organizado
*/
long isSorted (STACK *array) {

    //STACK cpy = *array;
    long n_elems = array->n_elems;
    long result = 0;

    for(long i = 0; i < n_elems; i++) {

        DATA a = pop(array);
        DATA b = pop(array);

        if(a.LONG < b.LONG) result++;

        push_LONG(array, b.LONG);
    }
    return result;
}
/**
 * @brief Função auxiliar da "$" que ordena o array
 *
 * Função que ordena de forma crescente os elementos do array
 *
 * @returns retorna o array ordenado
*/ 
STACK *sortArray (STACK *array) {             // organiza um array de forma crescente

    STACK *sorted = new_stack();
    long nelems = array->n_elems;    
    
    for (long k = 1; k < nelems - 1; k++) {
        
        for (long i = 0; i < nelems - 1; i++) {

            if (array->stack[i].LONG < array->stack[i + 1].LONG) {              // se o que está no array ordenado é maior do que o novo elemento

                DATA temp = array->stack[i];
                array->stack[i] = array->stack[i + 1];
                array->stack[i + 1] = temp;

            } 

        }
    }

    inverteArray(array, sorted);
    return sorted;

}

/**
 * @brief Função auxiliar da "$"
 *
 * Função que ordena os elementos em conjunto com o bloco percorrendo a lista e comparando sempre com o maior elemento
 *
*/
void auxOrdena(STACK *stack, DATA bloco, STACK *array, DATA *vars) {


    char *cpy = strdup(bloco.BLOCO); //cópia do bloco
    
    STACK copia = *array;
    STACK *store = new_stack();
    inverteArray(&copia, store);

    long vezes = array->n_elems;

    for (long i = vezes; i > 0; i--){

        DATA elem = pop(store);
        eval(strcat(DATAtoSTR(elem), strndup(cpy + 1, strlen(cpy) - 1)), stack, vars);
        cpy = strdup(bloco.BLOCO);
    }

}

/**
 * @brief Função final da "$"
 *
 * Função que ordena de forma crescente, os elementos do array, através do uso do bloco
 *
*/
void ordena(STACK *stack, DATA bloco, DATA *vars) {

    DATA elem = pop(stack);
    STACK *mapped = new_stack();    // array resultante do map do bloco com o array

    switch (elem.type) {

            case 16:
                auxOrdena(mapped, bloco, elem.ARRAY, vars);
                push_ARRAY(stack, sortArray(mapped));
                break;

            default:
            break;
        }
}

/**
 * @brief Função "w"
 *
 * Função que vai dando pop dos elementos da stack enquanto o topo for diferente de 0
 *
 *
*/
void trufy(STACK *stack, char *bloco, DATA *vars){

    STACK *result = new_stack();
    char *cpy = strdup(bloco); // cópia do bloco
    
    DATA array = pop(stack);
    STACK *copia = array.ARRAY;       // cópia do array
    STACK copia2 = *copia;
    STACK *store = new_stack();      // array pre invertido
    inverteArray(&copia2, store);     // array invertido
    long truthy = 1;                   // tester

    switch(array.type){
        case 1 :
            break;

        case 2 :
            break;

        case 4 :
            break;

        case 8 :
            break;

        case 16 :
            while (store != NULL && truthy != 0) {
                DATA elem = pop(store);
                eval(strcat(DATAtoSTR(elem), strndup(cpy + 1, strlen(cpy) - 1)), result, vars);
                DATA operation = pop(result);
                switch(operation.type){
                    case 1 :
                        if (operation.LONG == 0)
                            truthy = 0; 
                        break;

                    case 2 :
                        if (operation.DOUBLE == 0)
                            truthy = 0;
                        break;

                    case 4 :
                        if (operation.CHAR == '0')
                            truthy = 0;
                        break;

                    case 8 :
                        if (strcmp(operation.STRING, "0") == 0)
                            truthy = 0;
                        break;

                    case 16 :
                        break;

                    case 32 :
                        break;
                }
                cpy = strdup(bloco);
            }

            copia2 = *store;
            inverteArray(&copia2,result);
            push_ARRAY(stack, result);
            break;

        case 32 :               // não há operações entre blocos
            break;
    }
}