/**
 * @file manpln.c
 * @brief Ficheiro com funções de manipulação da stack
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "manpln.h"
#include "stack.h"
#include "arrays.h"

/**
 * @brief Duplica o elemento no topo da stack
 *
 * Inicializada com o token "_"
 */
void duplica(STACK *s){ // DUPLICAR "_"

    DATA x = pop(s);

    switch(x.type){
        case 1 :
            push_LONG(s, x.LONG);
            push_LONG(s, x.LONG);
            break;

        case 2 :
            push_DOUBLE(s, x.DOUBLE);
            push_DOUBLE(s, x.DOUBLE);
            break;

        case 4 :
            push_CHAR(s, x.CHAR);
            push_CHAR(s, x.CHAR);
            break;

        case 8 :
            push_STRING(s, x.STRING);
            push_STRING(s, x.STRING);
            break;

        case 16 :                                    // case de ser 16, de x ser do tipo array
            concatvar(x.ARRAY, 2);
            push_ARRAY(s, x.ARRAY);
            break;

        case 32 :
                break;
    }

}

/**
 * @brief Troca os 2 elementos no topo da stack
 *
 * Inicializada com o token "\"
 */
void troca(STACK *s){ // TROCAR DOIS ELEMENTOS DO TOPO DA STACK "\"
    DATA y = pop(s);
    DATA x = pop(s);

    switch(y.type){
        case 1 :
            push_LONG(s, y.LONG);
            break;

        case 2 :
            push_DOUBLE(s, y.DOUBLE);
            break;

        case 4 :
            push_CHAR(s, y.CHAR);
            break;

        case 8 :
            push_STRING(s, y.STRING);
            break;

        case 16 :                                   
            push_ARRAY(s, y.ARRAY);
            break;

        case 32 :
            push_BLOCO(s, y.BLOCO);
            break;
    }

    switch(x.type){
        case 1 :
            push_LONG(s, x.LONG);
            break;

        case 2 :
            push_DOUBLE(s, x.DOUBLE);
            break;

        case 4 :
            push_CHAR(s, x.CHAR);
            break;

        case 8 :
            push_STRING(s, x.STRING);
            break;

        case 16 :                                    // case de ser 16, de x ser do tipo array
            push_ARRAY(s, x.ARRAY);
            break;

        case 32 :
            push_BLOCO(s, x.BLOCO);
            break;
    }
}

/**
 * @brief Roda os 3 elementos no topo da stack
 *
 * Inicializada com o token "@"
 */
void rodar(STACK *s){ // RODAR OS 3 ELEMENTOS NO TOPO DA STACK "@"
    DATA x = pop(s);
    DATA y = pop(s);
    DATA z = pop(s); // a b c -> b c a

    switch(y.type){
        case 1 :
            push_LONG(s, y.LONG);
            break;

        case 2 :
            push_DOUBLE(s, y.DOUBLE);
            break;

        case 4 :
            push_CHAR(s, y.CHAR);
            break;

        case 8 :
            push_STRING(s, y.STRING);
            break;

        case 16 :                                    // case de ser 16, de x ser do tipo array
            push_ARRAY(s, y.ARRAY);
            break;

        case 32 :
            break;
    }


    switch(x.type){
        case 1 :
            push_LONG(s, x.LONG);
            break;

        case 2 :
            push_DOUBLE(s, x.DOUBLE);
            break;

        case 4 :
            push_CHAR(s, x.CHAR);
            break;

        case 8 :
            push_STRING(s, x.STRING);
            break;

        case 16 :                                    // case de ser 16, de x ser do tipo array
            push_ARRAY(s, x.ARRAY);
            break;

        case 32 :
            break;
    }

    switch(z.type){
        case 1 :
            push_LONG(s, z.LONG);
            break;

        case 2 :
            push_DOUBLE(s, z.DOUBLE);
            break;

        case 4 :
            push_CHAR(s, z.CHAR);
            break;

        case 8 :
            push_STRING(s, z.STRING);
            break;

        case 16 :                                    // case de ser 16, de x ser do tipo array
             push_ARRAY(s, z.ARRAY);
            break;

        case 32 :
            break;
    }
}

/**
 * @brief Copia o n-ésimo elemento para o topo da stack
 *
 * Inicializada com os tokens "n $"
 */
void copia(STACK *s, DATA *vars){ // COPIA N-ÉSIMO ELEMENTO PARA O TOPO DA STACK "n $"
    DATA n = pop(s);

    if (has_type(n,32) == 0){
        DATA x = s->stack[(s->n_elems) - n.LONG - 1];

        switch(x.type){
            case 1 :
                push_LONG(s, x.LONG);
                break;

            case 2 :
                push_DOUBLE(s, x.DOUBLE);
                break;

            case 4 :
                push_CHAR(s, x.CHAR);
                break;

            case 8 :
                push_STRING(s, x.STRING);
                break;

            case 16 :                                    // case de ser 16, de x ser do tipo array
                break;

            case 32 :
                break;
        }
    }
    else {

        switch(n.type){
            case 1 :
                break;

            case 2 :
                break;

            case 4 :
                break;

            case 8 :
                break;

            case 16 :                                    // case de ser 16, de x ser do tipo array
                break;

            case 32 :
            ordena(s, n, vars);
                break;

    }

}


    
}

/**
 * @brief Devolve o valor guardado pela variável dada
 *
 * Inicializada por qualquer letra maiúscula 
 */
void letra(STACK *s, char letra, DATA *array){ // variaveis
    long a = letra;
    TYPE x = (array[a-65].type);

    switch(x){
        case 1 :
            push_LONG(s, array[a-65].LONG);
            break;

        case 2 :
            push_DOUBLE(s, (array[a-65]).DOUBLE);
            break;

        case 4 :
            push_CHAR(s, (array[a-65]).CHAR);
            break;

        case 8 :
            push_STRING(s, (array[a-65]).STRING);
            break;

        case 16 :
            push_ARRAY(s, (array[a-65]).ARRAY);
            break;

        case 32 :
            push_BLOCO(s, (array[a-65]).BLOCO);
            break;

        default:
            push_CHAR(s, letra);
    }
}

/**
 * @brief Guarda o elemento no topo da stack na variável dada
 *
 * Inicializada com o token ":" mais uma letra maiúscula
 */
void atributo(STACK *s, char *letra, DATA *array){ // variaveis
    long a = (char)*letra;
    DATA x = pop(s);

    switch(x.type){
        case 1 :
            array[a-65].type = LONG;
            array[a-65].LONG = x.LONG;
            push_LONG(s, x.LONG);
            break;

        case 2 :
            array[a-65].type = DOUBLE;
            array[a-65].DOUBLE = x.DOUBLE;
            push_DOUBLE(s, x.DOUBLE);
            break;

        case 4 :
            array[a-65].type = CHAR;
            array[a-65].CHAR = x.CHAR;
            push_CHAR(s, x.CHAR);
            break;

        case 8 :
            array[a-65].type = STRING;
            array[a-65].STRING = x.STRING;
            push_STRING(s, x.STRING);
            break;

        case 16 :                                    // case de ser 16, de x ser do tipo array
            array[a-65].type = ARRAY;
            array[a-65].ARRAY = x.ARRAY;
            push_ARRAY(s, x.ARRAY);
            break;

        case 32 :
            array[a-65].type = BLOCO;
            array[a-65].BLOCO = x.BLOCO;
            push_BLOCO(s, x.BLOCO);
            break;
    }
}

/**
 * @brief if then else com os 3 elementos anteriores
 *
 * Inicializada com o token "?
 */
void question(STACK *s){ // if then else com os 3 elementos anteriores
    DATA z = pop(s);
    DATA y = pop(s);
    DATA x = pop(s);

    switch(x.type){   
        case 1 :
            if (x.LONG != 0){
                switch(y.type){
                    case 1:
                        push_LONG(s, y.LONG);
                        break;

                    case 2:
                        push_DOUBLE(s, y.DOUBLE);
                        break;

                    case 4:
                        push_CHAR(s, y.CHAR);
                        break;

                    case 8:
                        push_STRING(s, y.STRING);
                        break;

                    case 16 :                                    // case de ser 16, de x ser do tipo array
                        break;

                    case 32 :
                        break;
                }
        
            } else {
                switch(z.type){
                    case 1:
                        push_LONG(s, z.LONG);
                        break;

                    case 2:
                        push_DOUBLE(s, z.DOUBLE);
                        break;

                    case 4:
                        push_CHAR(s, z.CHAR);
                        break;

                    case 8:
                        push_STRING(s, z.STRING);
                        break;

                    case 16 :                                    // case de ser 16, de x ser do tipo array
                        break;

                    case 32 :
                        break;
                }
            }
            break;
    
        case 2 :
            if (x.DOUBLE != 0){
                                switch(y.type){
                    case 1:
                        push_LONG(s, y.LONG);
                        break;

                    case 2:
                        push_DOUBLE(s, y.DOUBLE);
                        break;

                    case 4:
                        push_CHAR(s, y.CHAR);
                        break;

                    case 8:
                        push_STRING(s, y.STRING);
                        break;

                    case 16 :                                    // case de ser 16, de x ser do tipo array
                        break;

                    case 32 :
                        break;
                }
        
            } else {
                switch(z.type){
                    case 1:
                        push_LONG(s, z.LONG);
                        break;

                    case 2:
                        push_DOUBLE(s, z.DOUBLE);
                        break;

                    case 4:
                        push_CHAR(s, z.CHAR);
                        break;

                    case 8:
                        push_STRING(s, z.STRING);
                        break;

                    case 16 :                                    // case de ser 16, de x ser do tipo array
                        break;

                    case 32 :
                        break;
                }
            }
            break;

        case 4 :
            if (x.CHAR != '0'){
                switch(y.type){
                    case 1:
                        push_LONG(s, y.LONG);
                        break;

                    case 2:
                        push_DOUBLE(s, y.DOUBLE);
                        break;

                    case 4:
                        push_CHAR(s, y.CHAR);
                        break;

                    case 8:
                        push_STRING(s, y.STRING);
                        break;

                    case 16 :                                    // case de ser 16, de x ser do tipo array
                        break;

                    case 32 :
                        break;
                }
        
            } else {
                switch(z.type){
                    case 1:
                        push_LONG(s, z.LONG);
                        break;

                    case 2:
                        push_DOUBLE(s, z.DOUBLE);
                        break;

                    case 4:
                        push_CHAR(s, z.CHAR);
                        break;

                    case 8:
                        push_STRING(s, z.STRING);
                        break;

                    case 16 :                                    // case de ser 16, de x ser do tipo array
                        break;

                    case 32 :
                        break;
                }
            }
            break;

        case 8 :
            if (strcmp(x.STRING, "0") != 0){
                switch(y.type){
                    case 1:
                        push_LONG(s, y.LONG);
                        break;

                    case 2:
                        push_DOUBLE(s, y.DOUBLE);
                        break;

                    case 4:
                        push_CHAR(s, y.CHAR);
                        break;

                    case 8:
                        push_STRING(s, y.STRING);
                        break;

                    case 16 :                                    // case de ser 16, de x ser do tipo array
                        break;

                    case 32 :
                        break;
                }
        
            } else {
                switch(z.type){
                    case 1:
                        push_LONG(s, z.LONG);
                        break;

                    case 2:
                        push_DOUBLE(s, z.DOUBLE);
                        break;

                    case 4:
                        push_CHAR(s, z.CHAR);
                        break;

                    case 8:
                        push_STRING(s, z.STRING);
                        break;

                    case 16 :                                    // case de ser 16, de x ser do tipo array
                        break;

                    case 32 :
                        break;
                }
            }

            break;

        case 16 :                                    // case de ser 16, de x ser do tipo array
            if (x.ARRAY->n_elems != 0){
                switch(y.type){
                    case 1:
                        push_LONG(s, y.LONG);
                        break;

                    case 2:
                        push_DOUBLE(s, y.DOUBLE);
                        break;

                    case 4:
                        push_CHAR(s, y.CHAR);
                        break;

                    case 8:
                        push_STRING(s, y.STRING);
                        break;

                    case 16 :                                    // case de ser 16, de x ser do tipo array
                        break;

                    case 32 :
                        break;
                }
        
            } else {
                switch(z.type){
                    case 1:
                        push_LONG(s, z.LONG);
                        break;

                    case 2:
                        push_DOUBLE(s, z.DOUBLE);
                        break;

                    case 4:
                        push_CHAR(s, z.CHAR);
                        break;

                    case 8:
                        push_STRING(s, z.STRING);
                        break;

                    case 16 :                                    // case de ser 16, de x ser do tipo array
                        break;

                    case 32 :
                        break;
                }
            }
                break;
        case 32 :                                    // case de ser 16, de x ser do tipo array
            if (x.ARRAY->n_elems != 0){
                switch(y.type){
                    case 1:
                        push_LONG(s, y.LONG);
                        break;

                    case 2:
                        push_DOUBLE(s, y.DOUBLE);
                        break;

                    case 4:
                        push_CHAR(s, y.CHAR);
                        break;

                    case 8:
                        push_STRING(s, y.STRING);
                        break;

                    case 16 :                                    // case de ser 16, de x ser do tipo array
                        break;

                    case 32 :
                        break;
                }
        
            } else {
                switch(z.type){
                    case 1:
                        push_LONG(s, z.LONG);
                        break;

                    case 2:
                        push_DOUBLE(s, z.DOUBLE);
                        break;

                    case 4:
                        push_CHAR(s, z.CHAR);
                        break;

                    case 8:
                        push_STRING(s, z.STRING);
                        break;

                    case 16 :                                    // case de ser 16, de x ser do tipo array
                        break;

                    case 32 :
                        break;
                }
            }
                break;
    }
}

/**
 * @brief Leitura de uma linha
 *
 * Inicializada com o token "l"
 *
 */
void lerl(STACK *s){
    char aux[10240];
    assert(fgets(aux,10240,stdin)!=NULL);
    assert(aux[strlen(aux)-1]=='\n');
    aux[strlen(aux)-1] = '\0';
    push_STRING(s,aux);
}

/**
 * @brief Leitura de todo o input
 *
 * Inicializada com o token "t"
 *
 */
void lert(STACK *s){ // t
    
    char aux[10240];
    char *string = malloc(sizeof(char)*10240);
    memset( string, '\0', sizeof(char)*10240);

    while (fgets(aux,10240,stdin) != NULL && aux[0] != '\n') {
        aux[strcspn(aux,"\n")] = '\n';
        strcat(string, aux);
    } 

    push_STRING(s,string);
}


/**
 * @brief Imprime o topo da stack
 *
 * Inicializada com o token "p"
 *
 */
void printt(STACK *s){ // IMPRIME TOPO DA STACK "p"
    DATA x = pop(s);
    
    switch(x.type){
        case 1 :
            push_LONG(s,x.LONG);
            break;

        case 2 :
            push_DOUBLE(s,x.DOUBLE);
            break;

        case 4 :
            push_CHAR(s, x.CHAR);
            break;

        case 8 :
            push_STRING(s, x.STRING);
            break;

        case 16 :
            push_ARRAY(s, x.ARRAY);                                   // case de ser 16, de x ser do tipo array
            break;

        case 32 :
            break;        
    }
}


/** CONVERSÕES */

long stringToLong(char *string) {

    long result;

    if (strlen(string) <= 1)
        result = (int)string[0];
    else result = atol(string);
    
    return result;
}

/**
 * @brief Converte o elemento no topo da stack num inteiro
 *
 * Inicializada com o token "i"
 */
void intz(STACK *s){ // CONVERTE O ELEMENTO NO TOPO DA STACK NUM INTEIRO "i"
    DATA x = pop(s);

    switch(x.type){
        case 1 :
            push_LONG(s, x.LONG);
            break;

        case 2 :
            push_LONG(s, (long)x.DOUBLE);
            break;

        case 4 :
            push_LONG(s, (long)x.CHAR);
            break;

        case 8 :      
            push_LONG(s, stringToLong(x.STRING));
            break;

        case 16 :                                    // case de ser 16, de x ser do tipo array
            break;

        case 32 :
            break;
    }
}
/**
 * @brief Converte o elemento no topo da stack num double
 *
 * Inicializada com o token "f"
 */
void doublez(STACK *s){ // CONVERTE O ELEMENTO NO TOPO DA STACK NUM DOUBLE "f"
    DATA x = pop(s);

    switch(x.type){
        case 1 :
            push_DOUBLE(s, (double)x.LONG);
            break;

        case 2 :
            push_DOUBLE(s, x.DOUBLE);
            break;

        case 4 :
            push_DOUBLE(s, (double)x.CHAR);
            break;

        case 8 :      
            push_DOUBLE(s, atof(x.STRING));
            break;

        case 16 :                                    // case de ser 16, de x ser do tipo array
            break;

        case 32 :
            break;
    }
}

/**
 * @brief Converte o elemento no topo da stack num char
 *
 * Inicializada com o token "c"
 */
void charz(STACK *s){ //   CONVERTE O ELEMENTO NO TOPO DA STACK NUM CARATERE "c"
    DATA x = pop(s);

    switch(x.type){
        case 1 :
            push_CHAR(s, (char)x.LONG);
            break;

        case 2 :
            push_CHAR(s, (char)x.DOUBLE);
            break;

        case 4 :
            push_CHAR(s, x.CHAR);
            break;

        case 8 :
            push_STRING(s, x.STRING);
            break;

        case 16 :                                    // case de ser 16, de x ser do tipo array
            break;

        case 32 :
            break;
    }
}

/**
 * @brief Converte o elemento no topo da stack numa string
 *
 * Inicializada com o token "s"
 */
void stringz(STACK *s){ // CONVERTE O ELEMENTO NO TOPO DA STACK NUMA STRING "s"
    DATA x = pop(s);

    switch(x.type){
        case 1 :
            push_LONG(s, x.LONG);
            break;

        case 2 :
            push_DOUBLE(s, x.DOUBLE);
            break;

        case 4 :
            push_STRING(s, x.STRING);
            break;

        case 8 :
            push_STRING(s, x.STRING);
            break;

        case 16 :                                    // case de ser 16, de x ser do tipo array
            break;

        case 32 :
            break;
    }
}