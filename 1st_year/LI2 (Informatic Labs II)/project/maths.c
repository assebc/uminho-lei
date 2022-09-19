/**
 * @file maths.c
 * @brief Ficheiro com funções relativas a operações matemáticas
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "maths.h"
#include "stack.h"
#include "arrays.h"

/**
 * @brief Soma de dois elementos da stack
 *
 * Inicializada com o token "+"
 */
void soma(STACK *s){ // SOMAR "+"
      
    DATA x = pop(s);
    DATA y = pop(s);
    
    switch(x.type){                                             // switch case para os diferentes tipos de x
        case 1 :                                                // case quando x é long
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é long
                case 1 :                                        // case quando y é long enquanto x é long
                push_LONG(s, y.LONG + x.LONG);
                break;

                case 2 :                                        // case quando y é double enquanto x é long
                push_DOUBLE(s, y.DOUBLE + x.LONG);
                break;

                case 4 :                                        // case quando y é char enquanto x é long
                push_LONG(s, x.LONG);
                break;

                case 8 :                                        // case quando y é string enquanto x é long
                push_LONG(s, x.LONG);
                break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                push_LONG(y.ARRAY, x.LONG);
                push_ARRAY(s, y.ARRAY);
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é long
            break;                                              // fim do case quando x é long

        case 2 :                                                // case quando x é double
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é double
                case 1 :                                        // case quando y é long enquanto x é double
                push_DOUBLE(s,  y.LONG + x.DOUBLE);
                break;

                case 2 :                                        // case quando y é double enquanto x é double
                push_DOUBLE(s,  y.DOUBLE + x.DOUBLE);
                break;

                case 4 :                                        // case quando y é char enquanto x é double
                push_DOUBLE(s, x.DOUBLE);
                break;

                case 8 :                                        // case quando y é string enquanto x é double
                push_DOUBLE(s, x.DOUBLE);
                break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é double
            break;                                              // fim do case quando x é double

        case 4 :                                                // case quando x é char
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é char
                case 1 :                                        // case quando y é long enquanto x é char
                push_LONG(s, y.LONG);
                break;

                case 2 :                                        // case quando y é double enquanto x é char
                push_DOUBLE(s, y.DOUBLE);
                break;

                case 4 :                                        // case quando y é char enquanto x é char
                push_CHAR(s, x.CHAR);
                push_CHAR(s, y.CHAR);
                break;

                case 8 :                                        // case quando y é string enquanto x é char
                strncat(y.STRING, &(x.CHAR), 1);
                push_STRING(s, y.STRING);
                break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é char
            break;                                              // fim do case quando x é char

        case 8 :                                                // case quando x é string
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é string
                case 1 :                                        // case quando y é long enquanto x é string
                    push_STRING(s,concatAny(y, x.STRING));
                break;

                case 2 :                                        // case quando y é double enquanto x é string
                    push_STRING(s,concatAny(y, x.STRING));
                break;

                case 4 :                                        // case quando y é char enquanto x é string
                    push_STRING(s,concatAny(y, x.STRING));
                break;

                case 8 :                                        // case quando y é string enquanto x é string
                    push_STRING(s, concatstr(y.STRING, x.STRING));
                break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é string
            break;                                              // fim do case quando x é string

        case 16 :
            switch(y.type){                                    // case de ser 16, de x ser do tipo array
                case 1 :
                concatSTART(y, x.ARRAY);
                push_ARRAY(s, x.ARRAY);
                break;

                case 2 :
                break;

                case 4 :
                break;

                case 8 :
                break;

                case 16 :
                concatenar(y.ARRAY,x.ARRAY);
                push_ARRAY(s, y.ARRAY);
                break;

                case 32 :
                break;
            }
                break;

        case 32 :
            break;

    }                                                           // fim do switch case para os diferentes tipos de x
}                                                               // fim da função "+"

/**
 * @brief Subtração entre dois elementos da stack
 *
 * Inicializada com o token "-"
 */
void subtrai(STACK *s){ // SUBTRAIR "-"
      
    DATA x = pop(s);
    DATA y = pop(s);
    
    switch(x.type){                                             // switch case para os diferentes tipos de x
        case 1 :                                                // case quando x é long
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é long
                case 1 :                                        // case quando y é long enquanto x é long
                push_LONG(s, y.LONG - x.LONG);
                break;

                case 2 :                                        // case quando y é double enquanto x é long
                push_DOUBLE(s, y.DOUBLE - x.LONG);
                break;

                case 4 :                                        // case quando y é char enquanto x é long                                       
                push_LONG(s, x.LONG);
                break;

                case 8 :                                        // case quando y é string enquanto x é long
                push_LONG(s, x.LONG);
                break;

                case 16 :                                       // case de ser 16, de x ser do tipo array
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é long
            break;                                              // fim do case quando x é long

        case 2 :                                                // case quando x é double                                            
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é double
                case 1 :                                        // case quando y é long enquanto x é double
                push_DOUBLE(s, y.LONG - x.DOUBLE);
                break;

                case 2 :                                        // case quando y é double enquanto x é double
                push_DOUBLE(s, y.DOUBLE - x.DOUBLE);
                break;

                case 4 :                                        // case quando y é char enquanto x é double
                push_DOUBLE(s, x.DOUBLE);
                break;

                case 8 :                                        // case quando y é string enquanto x é double
                push_DOUBLE(s, x.DOUBLE);
                break;

                case 16 :                                       // case de ser 16, de x ser do tipo array
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é double
            break;                                              // fim do case quando x é double

        case 4 :                                                // case quando x é char
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é char
                case 1 :                                        // case quando y é long enquanto x é char
                push_LONG(s, y.LONG);
                break;

                case 2 :                                        // case quando y é double enquanto x é char
                push_DOUBLE(s, y.DOUBLE);
                break;

                case 4 :                                        // case quando y é char enquanto x é char
                push_CHAR(s, x.CHAR);
                push_CHAR(s, y.CHAR);
                break;

                case 8 :                                        // case quando y é string enquanto x é char
                push_DOUBLE(s, x.CHAR);
                break;

                case 16 :                                       // case de ser 16, de x ser do tipo array
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é char
            break;                                              // fim do case quando x é char

        case 8 :                                                // case quando x é string
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é string
                case 1 :                                        // case quando y é long enquanto x é string
                push_LONG(s, y.LONG);
                break;

                case 2 :                                        // case quando y é double enquanto x é string
                push_DOUBLE(s, y.DOUBLE);
                break;

                case 4 :                                        // case quando y é char enquanto x é string
                push_STRING(s, x.STRING);
                break;

                case 8 :                                        // case quando y é string enquanto x é string
                push_STRING(s, x.STRING);
                push_STRING(s, y.STRING);
                break;

                case 16 :                                        // case de ser 16, de x ser do tipo array
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é string
            break;                                              // fim do case quando x é string

        case 16 :                                               // case de ser 16, de x ser do tipo array
                break;

        case 32 :
                break;

    }                                                           // fim do switch case para os diferentes tipos de x
}                                                               // fim da função "-"

/**
 * @brief Multiplicação entre dois elementos da stack
 *
 * Inicializada com o token "*"
 */
void multiplica(STACK *s, DATA *vars){ // MULTIPLICAR "*"

    DATA x = pop(s);
    DATA y = pop(s);
    
    switch(x.type){                                             // switch case para os diferentes tipos de x
        case 1 :                                                // case quando x é long
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é long
                case 1 :                                        // case quando y é long enquanto x é long
                push_LONG(s, x.LONG * y.LONG);
                break;

                case 2 :                                        // case quando y é double enquanto x é long
                push_DOUBLE(s, x.LONG * y.DOUBLE);
                break;

                case 4 :                                        // case quando y é char enquanto x é long
                push_LONG(s, x.LONG);
                break;

                case 8 :                                        // case quando y é string enquanto x é long
                concatvarstr(y.STRING, x.LONG);
                push_STRING(s, y.STRING);
                break;

                case 16 :                                       // case quando y é array enquanto x é long
                concatvar(y.ARRAY, x.LONG);
                push_ARRAY(s, y.ARRAY);         
                break;

                case 32 :

                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é long
            break;                                              // fim do case quando x é long

        case 2 :                                                // case quando x é double
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é double
                case 1 :                                        // case quando y é long enquanto x é double
                push_DOUBLE(s, x.DOUBLE * y.LONG);
                break;

                case 2 :                                        // case quando y é double enquanto x é double
                push_DOUBLE(s, x.DOUBLE * y.DOUBLE);
                break;

                case 4 :                                        // case quando y é char enquanto x é double
                push_DOUBLE(s, x.DOUBLE);
                break;

                case 8 :                                        // case quando y é string enquanto x é double
                push_DOUBLE(s, x.DOUBLE);
                break;

                case 16 :
                push_DOUBLE(s, x.DOUBLE);                       // case quando y é array enquanto x é double
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é double
            break;                                              // fim do case quando x é double

        case 4 :                                                // case quando x é char                                                
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é char
                case 1 :                                        // case quando y é long enquanto x é char
                push_LONG(s, y.LONG);
                break;

                case 2 :                                        // case quando y é double enquanto x é char
                push_DOUBLE(s, y.DOUBLE);
                break;

                case 4 :                                        // case quando y é char enquanto x é char
                push_CHAR(s, x.CHAR);
                push_CHAR(s, y.CHAR);
                break;

                case 8 :                                        // case quando y é string enquanto x é char
                push_CHAR(s, x.CHAR);
                break;

                case 16 :                                       // case quando y é array enquanto x é char
                push_CHAR(s, x.CHAR);
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é char
            break;                                              // fim do case quando x é char

        case 8 :                                                // case quando x é string
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é string
                case 1 :                                        // case quando y é long enquanto x é string
                push_LONG(s, y.LONG);
                break;

                case 2 :                                        // case quando y é double enquanto x é string
                push_DOUBLE(s, y.DOUBLE);
                break;

                case 4 :                                        // case quando y é char enquanto x é string
                push_STRING(s, x.STRING);
                break;

                case 8 :                                        // case quando y é string enquanto x é string
                push_STRING(s, x.STRING);
                push_STRING(s, y.STRING);
                break;

                case 16 :                                       // case quando y é array enquanto x é string
                push_STRING(s, x.STRING);
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é string
            break;                                              // fim do case quando x é string

        case 16 :                                               // case quando x é array
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é array
                case 1 :                                        // case quando y é long enquanto x é array
                concatvar(x.ARRAY, y.LONG);
                push_ARRAY(s, x.ARRAY); 
                break;

                case 2 :                                        // case quando y é double enquanto x é array
                push_ARRAY(s, x.ARRAY);
                break;

                case 4 :                                        // case quando y é char enquanto x é array
                push_ARRAY(s, x.ARRAY);
                break;

                case 8 :                                        // case quando y é string enquanto x é array
                push_ARRAY(s, x.ARRAY);
                break;

                case 16 :
                push_ARRAY(s, x.ARRAY);                         // case quando y é array enquanto x é array
                break;

                case 32 :
                break;                                          
            }
            break;

        case 32 :
            switch(y.type){
                case 1 :
                break;

                case 2 :
                break;

                case 4 :
                break;

                case 8 :
                break;

                case 16 :
                fold(s, x, y.ARRAY, vars);
                break;

                case 32 :
                break;
            }
            break;
            

    }                                                           // fim do switch case para os diferentes tipos de x
}                                                               // fim da função "*"

/**
 * @brief Divisão entre dois elementos da stack
 *
 * Inicializada com o token "/"
 */
void divide(STACK *s){ // DIVIDIR "/"

    DATA x = pop(s);
    DATA y = pop(s);

    switch(x.type){                                             // switch case para os diferentes tipos de x
        case 1 :                                                // case quando x é long
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é long
                case 1 :                                        // case quando y é long enquanto x é long
                push_LONG(s, y.LONG / x.LONG);
                break;

                case 2 :                                        // case quando y é double enquanto x é long
                push_DOUBLE(s, y.DOUBLE / x.LONG);
                break;

                case 4 :                                        // case quando y é char enquanto x é long
                push_LONG(s, x.LONG);
                break;

                case 8 :                                        // case quando y é string enquanto x é long
                push_LONG(s, x.LONG);
                break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é long
            break;                                              // fim do case quando x é long

        case 2 :                                                // case quando x é double
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é double
                case 1 :                                        // case quando y é long enquanto x é double
                push_DOUBLE(s, y.LONG / x.DOUBLE);
                break;

                case 2 :                                        // case quando y é double enquanto x é double
                push_DOUBLE(s, y.DOUBLE / x.DOUBLE);
                break;

                case 4 :                                        // case quando y é char enquanto x é double
                push_DOUBLE(s, x.DOUBLE);
                break;

                case 8 :                                        // case quando y é string enquanto x é double
                push_DOUBLE(s, x.DOUBLE);
                break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é double
            break;                                              // fim do case quando x é double

        case 4 :                                                // case quando x é char
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é char
                case 1 :                                        // case quando y é long enquanto x é char
                push_LONG(s, y.LONG);
                break;

                case 2 :                                        // case quando y é double enquanto x é char

                push_DOUBLE(s, y.DOUBLE);
                break;

                case 4 :                                        // case quando y é char enquanto x é char
                push_CHAR(s, x.CHAR);
                push_CHAR(s, y.CHAR);
                break;

                case 8 :                                        // case quando y é string enquanto x é char
                push_DOUBLE(s, x.CHAR);
                break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é char
            break;                                              // fim do case quando x é char

        case 8 :                                                // case quando x é string                   
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é string
                case 1 :                                        // case quando y é long enquanto x é string
                push_LONG(s, y.LONG);
                break;

                case 2 :                                        // case quando y é double enquanto x é string
                push_DOUBLE(s, y.DOUBLE);
                break;

                case 4 :                                        // case quando y é char enquanto x é string
                push_STRING(s, x.STRING);
                break;

                case 8 :                                        // case quando y é string enquanto x é string
                subarray (s, x.STRING, y.STRING);
                break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é string
            break;                                              // fim do case quando x é string

        case 16 :                                    // case de ser 16, de x ser do tipo array
                break;

        case 32 :
                break;
    }                                                           // fim do switch case para os diferentes tipos de x
}                                                               // fim da função "/"                                                                                              

/**
 * @brief Incrementação do elemento no topo da stack
 *
 * Inicializada com o token ")"
 */
void incrementa(STACK *s){ // INCREMENTAR e remove último de array ou string ")"
    DATA x = pop(s);

    switch(x.type){                                             // switch case para os diferentes tipos de x
        case 1 :                                                // case quando x é long
            push_LONG(s, x.LONG + 1);
            break;                                              // fim do case quando x é long

        case 2 :                                                // case quando x é double
            push_DOUBLE(s, x.DOUBLE + 1);
            break;                                              // fim do case quando x é double

        case 4 :                                                // case quando x é char
            push_CHAR(s, x.CHAR + 1);
            break;                                              // fim do case quando x é char

        case 8 :                                                // case quando x é string
            push_STRING(s, strndup(x.STRING, strlen(x.STRING) - 1));
            push_STRING(s, strndup(x.STRING + strlen(x.STRING) -1, sizeof(char)));
            break;                                              // fim do case quando x é string

        case 16 :                                               // case de ser 16, de x ser do tipo array
            removeUltArray(s, x.ARRAY);
            break;

        case 32 :
            break;
    }                                                           // fim do switch case para os diferentes tipos de x
}                                                               // fim da função ")"

/**
 * @brief Decrementação do elemento no topo da stack
 *
 * Inicializada com o token "("
 */
void decrementa(STACK *s){ // DECREMENTAR e remove primeiro de array ou string "("
    DATA x = pop(s);

    switch(x.type){                                             // switch case para os diferentes tipos de x
        case 1 :                                                // case quando x é long
            push_LONG(s, x.LONG - 1);
            break;                                              // fim do case quando x é long

        case 2 :                                                // case quando x é double
            push_DOUBLE(s, x.DOUBLE - 1);
            break;                                              // fim do case quando x é double

        case 4 :                                                // case quando x é char
            push_CHAR(s, x.CHAR - 1);
            break;                                              // fim do case quando x é char

        case 8 :                                                // case quando x é string
            push_STRING(s, x.STRING + 1);
            push_STRING(s, strndup(x.STRING, sizeof(char)));
            break;                                              // fim do case quando x é string

        case 16 :                                    // case de ser 16, de x ser do tipo array
            removePrimArray(s, x.ARRAY);
            break;

        case 32 :
            break;
    }                                                           // fim do switch case para os diferentes tipos de x
}                                                               // fim da função "("

/**
 * @brief Módulo entre dois elementos da stack
 *
 * Inicializada com o token "%"
 */
void modulo(STACK *s, DATA *vars){ //  MÓDULO "%"
      
    DATA x = pop(s);
    DATA y = pop(s);
    
    switch(x.type){                                             // switch case para os diferentes tipos de x                                                 
        case 1 :                                                // case quando x é long 
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é long
                case 1 :                                        // case quando y é long enquanto x é long
                push_LONG(s, y.LONG % x.LONG);
                break;

                case 2 :                                        // case quando y é double enquanto x é long
                push_DOUBLE(s, fmod(y.DOUBLE, x.LONG));
                break;

                case 4 :                                        // case quando y é char enquanto x é long
                push_LONG(s, x.LONG);
                break;

                case 8 :                                        // case quando y é string enquanto x é long
                push_LONG(s, x.LONG);
                break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é long
            break;                                              // fim do case quando x é long

        case 2 :                                                // case quando x é double
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é double
                case 1 :                                        // case quando y é long enquanto x é double
                push_DOUBLE(s, fmod(y.LONG, x.DOUBLE));
                break;

                case 2 :                                        // case quando y é double enquanto x é double
                push_DOUBLE(s, fmod(y.DOUBLE, x.DOUBLE));
                break;

                case 4 :                                        // case quando y é char enquanto x é double
                push_DOUBLE(s, x.DOUBLE);
                break;

                case 8 :                                        // case quando y é string enquanto x é double
                push_DOUBLE(s, x.DOUBLE);
                break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é double
            break;                                              // fim do case quando x é double

        case 4 :                                                // case quando x é char
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é char
                case 1 :                                        // case quando y é long enquanto x é char
                push_LONG(s, y.LONG);
                break;

                case 2 :                                        // case quando y é double enquanto x é char
                push_DOUBLE(s, y.DOUBLE);
                break;

                case 4 :                                        // case quando y é char enquanto x é char
                push_CHAR(s, x.CHAR);
                push_CHAR(s, y.CHAR);
                break;

                case 8 :                                        // case quando y é string enquanto x é char                                      
                push_DOUBLE(s, x.CHAR);
                break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é char
            break;                                              // fim do case quando x é char

        case 8 :                                                // case quando x é string
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é string
                case 1 :                                        // case quando y é long enquanto x é string
                push_LONG(s, y.LONG);
                break;

                case 2 :                                        // case quando y é double enquanto x é string
                push_DOUBLE(s, y.DOUBLE);
                break;

                case 4 :                                        // case quando y é char enquanto x é string
                push_STRING(s, x.STRING);
                break;

                case 8 :                                        // case quando y é string enquanto x é string
                push_STRING(s, x.STRING);
                push_STRING(s, y.STRING);
                break;                                          // fim do switch case para os diferentes tipos de y enquanto x é string

                case 16 :                                    // case de ser 16, de x ser do tipo array
                break;

                case 32 :
                break;
            }
            break;                                              // fim do case quando x é string 

        case 16 :
            break;  

        case 32 :
            switch(y.type) {                                     // switch case para os diferentes tipos de y enquanto x é string
                case 1 :                                        // case quando y é long enquanto x é string
                
                break;

                case 2 :                                        // case quando y é double enquanto x é string
                
                break;

                case 4 :                                        // case quando y é char enquanto x é string
                break;

                case 8 :                                        // case quando y é string enquanto x é string
                    mapstring(s, x, y.STRING, vars);
                break;                                          // fim do switch case para os diferentes tipos de y enquanto x é string

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    map(s, x, y.ARRAY, vars);
                break;

                case 32 :
                break;
            
            break;                                         

        }                                                           // fim do switch case para os diferentes tipos de x
    }                                                               // fim da função "%"
}

/**
 * @brief Exponenciação de um elemento segundo outro
 *
 * Inicializada com o token "#"
 */
void expoente(STACK *s){ // EXPONENCIAÇÃO "#"
      
    DATA x = pop(s);
    DATA y = pop(s);
    
    switch(x.type){                                             // switch case para os diferentes tipos de x
        case 1 :                                                // case quando x é long
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é long
                case 1 :                                        // case quando y é long enquanto x é long
                push_LONG(s, powl(y.LONG,x.LONG));
                break;

                case 2 :                                        // case quando y é double enquanto x é long
                push_DOUBLE(s, powf(y.DOUBLE,x.LONG));
                break;

                case 4 :                                        // case quando y é char enquanto x é long
                push_LONG(s, x.LONG);
                break;

                case 8 :                                        // case quando y é string enquanto x é long
                push_LONG(s, x.LONG);
                break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é long
            break;                                              // fim do case quando x é long

        case 2 :                                                // case quando x é double
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é double
                case 1 :                                        // case quando y é long enquanto x é double
                push_DOUBLE(s, powf(y.LONG,x.DOUBLE));
                break;

                case 2 :                                        // case quando y é double enquanto x é double
                push_DOUBLE(s, powf(y.DOUBLE,x.DOUBLE));
                break;

                case 4 :                                        // case quando y é char enquanto x é double
                push_DOUBLE(s, x.DOUBLE);
                break;

                case 8 :                                        // case quando y é string enquanto x é double
                push_DOUBLE(s, x.DOUBLE);
                break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é double
            break;                                              // fim do case quando x é double

        case 4 :                                                // case quando x é char
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é char
                case 1 :                                        // case quando y é long enquanto x é char
                push_LONG(s, y.LONG);
                break;

                case 2 :                                        // case quando y é double enquanto x é char
                push_DOUBLE(s, y.DOUBLE);
                break;

                case 4 :                                        // case quando y é char enquanto x é char
                push_CHAR(s, x.CHAR);
                push_CHAR(s, y.CHAR);
                break;

                case 8 :                                        // case quando y é string enquanto x é char
                push_DOUBLE(s, x.CHAR);
                break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                break;

                case 32 :
                break;
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é char
            break;                                              // fim do case quando x é char

        case 8 :                                                // case quando x é string
            switch(y.type){                                     // switch case para os diferentes tipos de y enquanto x é string
                case 1 :                                        // case quando y é long enquanto x é string
                push_LONG(s, y.LONG);
                break;

                case 2 :                                        // case quando y é double enquanto x é string
                push_DOUBLE(s, y.DOUBLE);
                break;

                case 4 :                                        // case quando y é char enquanto x é string
                push_STRING(s, x.STRING);
                break;

                case 8 :                                        // case quando y é string enquanto x é string
                push_LONG(s, strsearch(x.STRING, y.STRING));
                break;  

                case 16 :                                    // case de ser 16, de x ser do tipo array
                break; 

                case 32 :
                break;                                       
            }                                                   // fim do switch case para os diferentes tipos de y enquanto x é string
            break;                                              // fim do case quando x é string

        case 16 :                                    // case de ser 16, de x ser do tipo array
                break;

        case 32 :
            break;

    }                                                           // fim do switch case para os diferentes tipos de x
}                                                               // fim da função "#"