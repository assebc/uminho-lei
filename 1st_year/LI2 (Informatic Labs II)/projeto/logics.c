/**
 * @file logics.c
 * @brief Ficheiro com funções relativas a operações lógicas
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "logics.h"
#include "stack.h"
#include "arrays.h"

/**
 * @brief E lógico entre dois elementos da stack
 *
 * Inicializada com o token "&"
 */
void E(STACK *s){ // E "&"
      
    DATA x = pop(s);
    DATA y = pop(s);
    
    if(has_type(x, 1) && has_type(y, 1))
        push_LONG(s, y.LONG & x.LONG);
}                                                   // fim do "&"

/**
 * @brief OU lógico entre dois elementos da stack
 *
 * Inicializada com o token "|"
 */
void ou(STACK *s){ // OU "|"
      
    DATA x = pop(s);
    DATA y = pop(s);
    
    if(has_type(x, 1) && has_type(y, 1))
        push_LONG(s, y.LONG | x.LONG);
    
}                                                   // fim do "|"

/**
 * @brief OU Exclusivo (aka XOR) entre dois elementos da stack
 *
 * Inicializada com o token "^"
 */
void xor(STACK *s){ // XOR "^"
      
    DATA x = pop(s);
    DATA y = pop(s);
    
    if(has_type(x, 1) && has_type(y, 1))
        push_LONG(s, y.LONG ^ x.LONG);
     
}                                                   // fim do "^"

/**
 * @brief Negação de um elemento da stack
 *
 * Inicializada com o token "~"
 */
void not(STACK *s, DATA *vars){ // NOT "~"
    DATA x = pop(s);

    switch(x.type){                                 // switch case para os diferentes tipos de x
        case 1 :                                    // case de ser 1, de x ser do tipo long 
            push_LONG(s, ~(x.LONG));
            break;

        case 2 :                                    // case de ser 2, de x ser do tipo double
            if (fmod(x.DOUBLE, 1) == 0)
                push_LONG(s, ~((long)x.DOUBLE));
            break;

        case 4 :                                    // case de ser 4, de x ser do tipo char
            break;

        case 8 :                                    // case de ser 8, de x ser do tipo string
            break;

        case 16 :                                    // case de ser 16, de x ser do tipo array
            concatenar(s, x.ARRAY);
            break;

        case 32 :
            aplica(s, x, vars);    
            break;
    }                                               // fim do switch case dos tipos de x
}                                                   // fim do "~"

/**
 * @brief Teste de igualdade entre os 2 elementos no topo da stack
 *
 * Inicializada com o token "="
 */
void igual(STACK *s){ // "=" 
    DATA x = pop(s);
    DATA y = pop(s);

    switch(x.type){                                 // switch case para os tipos de x
        case 1 :                                    // case de x ser long
            switch(y.type){                         // switch case para os tipos de y quando x é do tipo long
                case 1 :                            // case de y ser long enquanto x é long
                    if (x.LONG == y.LONG)           
                        push_LONG(s, 1);
                    else
                        push_LONG(s,0);
                    break;

                case 2 :                            // case de y ser double enquanto x é long
                    if ((fmod(y.DOUBLE, 1) == 0) && (x.LONG == (long)y.DOUBLE))
                        push_LONG(s, 1);
                    else
                        push_LONG(s,0);
                    break;

                case 4 :                            // case de y ser char enquanto x é long
                    if (x.LONG >= 0 && x.LONG < 9)
                        if (y.CHAR == (char)x.LONG)
                            push_LONG(s, 1);
                        else
                            push_LONG(s, 0);
                    else
                        push_LONG(s, 0);
                    break;

                case 8 :                           // case de y ser string enquanto x é long
                    seeknstring(x.LONG, y.STRING, s);
                    break;

                case 16 :
                    seek(x.LONG, y.ARRAY, s);
                    break;

                case 32 :
                    break;
            }                                      // fim do switch case dos tipos de y para quando x é long
            break;                                 // fim do case quando x é long

        case 2 :                                   // case quando x é double
            switch(y.type){                        // switch case do y para os diferentes tipos enquanto que x é double
                case 1 :                           // case quando y é long enquanto que x é double
                    if ((fmod(x.DOUBLE, 1) == 0) && ((long)x.DOUBLE == y.LONG))
                        push_LONG(s, 1);
                    else
                        push_LONG(s, 0);
                    break;
            
                case 2 :                           // case quando y é double enquanto x é double
                    if (y.DOUBLE == x.DOUBLE)
                        push_LONG(s, 1);
                    else
                        push_LONG(s, 0);
                    break;

                case 4 :                           // case quando y é char enquanto x é double
                    if ((fmod(x.DOUBLE, 1) == 0) && (x.DOUBLE >= 0 && x.DOUBLE < 9))
                        if (x.DOUBLE == y.CHAR)
                            push_LONG(s, 1);
                        else
                            push_LONG(s, 0);
                    else
                        push_LONG(s, 0);
                    break;

                case 8 :                           // case quando y é string enquanto x é double
                    push_LONG(s, 0);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                      // fim do switch case dos tipos de y para quando x é double
            break;                                 // fim do case quando x é double

        case 4 :                                   // case quando x é char
            switch(y.type){                        // switch case do y para os diferentes tipos enquanto x é char
                case 1:                            // case quando y é long enquanto x é char
                    if (y.LONG >= 0 && y.LONG < 9)
                        if (x.CHAR == (char)y.LONG)
                           push_LONG(s, 1);
                        else
                            push_LONG(s, 0);
                    else
                        push_LONG(s, 0);
                    break;

                case 2 :                            // case quando y é double enquanto x é char
                    if ( (y.DOUBLE >= 0 && y.DOUBLE < 9) && fmod(y.DOUBLE, 1) == 0)
                        if (x.CHAR == (char)y.DOUBLE)
                            push_LONG(s, 1);
                        else
                            push_LONG(s, 0);
                    else
                        push_LONG(s, 0);
                    break;

                case 4 :                            // case quando y é char enquanto x é char
                    if (x.CHAR == y.CHAR)
                        push_LONG(s, 1);
                    else
                        push_LONG(s, 0);
                    break;

                case 8 :                            // case quando y é string enquanto x é char
                    push_LONG(s, 0);
                    break;
                
                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case dos tipos de y para quando x é char
            break;                                  // fim do case quando x é char

        case 8 :                                    // case quando x é string
            switch(y.type){                         // switch case dos tipos de y enquando x é string
                case 1 :                            // case quando y é long enquanto x é string
                    push_LONG(s, 0);
                    break;

                case 2 :                            // case quando y é double enquanto x é string
                    push_LONG(s, 0);
                    break;

                case 4 :                            // case quando y é char enquanto x é string
                    push_LONG(s, 0);
                    break;

                case 8 :                            // case quando y é string enquanto x é string
                    if (strcmp(x.STRING,y.STRING) == 0)
                        push_LONG(s, 1);
                    else
                        push_LONG(s, 0);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case dos tipos de y para quando x é string
            break;                                  // fim do case quando x é string

        case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

        case 32 :
                break;
    }                                               // fim do switch case dos tipos de x
}                                                   // fim da função "="

/**
 * @brief Verifica se o 2º elemento no topo da stack é menor que o 1º  elemento no topo da stack
 *
 * Inicializada com o token "<"
 */
void menor(STACK *s){ // <
    DATA x = pop(s);
    DATA y = pop(s);

        switch(x.type){                              // switch case para os diferentes tipos de x
        case 1 :                                     // case quando x é long
            switch(y.type){                          // switch case para os diferentes tipos de y enquanto x é long
                case 1 :                             // case quando y é long enquanto x é long
                    if (y.LONG < x.LONG)
                        push_LONG(s, 1);
                    else
                        push_LONG(s,0);
                    break;

                case 2 :                             // case quando y é double enquanto x é long
                    if (y.DOUBLE < x.LONG)
                        push_LONG(s, 1);
                    else
                        push_LONG(s,0);
                    break;

                case 4 :                             // case quando y é char enquanto x é long
                    if (y.CHAR < x.LONG)
                        push_LONG(s, 1);
                    else
                        push_LONG(s, 0);
                    break;

                case 8 :                             // case quando y é string enquanto x é long
                    push_STRING(s, strndup(y.STRING, sizeof(char) * x.LONG));
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    takeXstart(x.LONG, y.ARRAY);
                    push_ARRAY(s, y.ARRAY);
                    break;

                case 32 :
                break;
            }                                        // fim do switch case para os diferentes tipos de y enquanto x é long
            break;                                   // fim do case quando x é long

        case 2 :                                     // case quando x é double                               
            switch(y.type){                          // switch case para os diferentes tipos de y enquanto x é double
                case 1 :                             // case quando y é long enquanto x é double
                    if (y.LONG < x.DOUBLE)
                        push_LONG(s, 1);
                    else
                        push_LONG(s, 0);
                    break;
            
                case 2 :                             // case quando y é double enquanto x é double
                    if (y.DOUBLE < x.DOUBLE)
                        push_LONG(s, 1);
                    else
                        push_LONG(s, 0);
                    break;

                case 4 :                             // case quando y é char enquanto x é double
                    if ((fmod(x.DOUBLE, 1) == 0) && (x.DOUBLE >= 0 && x.DOUBLE < 9))
                        if (y.CHAR < (char)x.DOUBLE)
                            push_LONG(s, 1);
                        else
                            push_LONG(s, 0);
                    else
                        push_LONG(s, 0);
                    break;

                case 8 :                             // case quando y é string enquanto x é double
                    push_LONG(s, 0);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                        // fim do switch case para os diferentes tipos de y enquanto x é double
            break;                                   // fim do case quando x é double

        case 4 :                                     // case quando x é char
            switch(y.type){                          // switch case para os diferentes tipos de y enquanto x é char
                case 1:                              // case quando y é long enquanto x é char
                    if (y.LONG >= 0 && y.LONG < 9)
                        if (y.LONG < x.CHAR)
                           push_LONG(s, 1);
                        else
                            push_LONG(s, 0);
                    else
                        push_LONG(s, 0);
                    break;

                case 2 :                             // case quando y é double enquanto x é char
                    if ( (y.DOUBLE >= 0 && y.DOUBLE < 9) && fmod(y.DOUBLE, 1) == 0)
                        if ((char)y.DOUBLE < x.CHAR)
                            push_LONG(s, 1);
                        else
                            push_LONG(s, 0);
                    else
                        push_LONG(s, 0);
                    break;

                case 4 :                             // case quando y é char enquanto x é char
                    if (y.CHAR < x.CHAR)
                        push_LONG(s, 1);
                    else
                        push_LONG(s, 0);
                    break;

                case 8 :                             // case quando y é string enquanto x é char
                    push_LONG(s, 0);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                        // fim do switch case para os diferentes tipos de y enquanto x é char
            break;                                   // fim do case quando x é char

        case 8 :                                     // case quando x é string
            switch(y.type){                          // switch case para os diferentes tipos de y enquanto x é string
                case 1 :                             // case quando y é long enquanto x é string
                    push_LONG(s, 0);
                    break;

                case 2 :                             // case quando y é double enquanto x é string
                    push_LONG(s, 0);
                    break;

                case 4 :                             // case quando y é char enquanto x é string
                    push_LONG(s, 0);
                    break;

                case 8 :                             // case quando y é string enquanto x é string
                    if (strlen(y.STRING) < strlen(x.STRING))
                        push_LONG(s, 1);
                    else if (strlen(y.STRING) == strlen(x.STRING))
                        if (strcmp(y.STRING, x.STRING) < 0)
                            push_LONG(s, 1);
                        else if (strcmp(y.STRING, x.STRING) >= 0)
                            push_LONG(s, 0);
                        else
                            push_LONG(s, 0);
                    else
                        push_LONG(s,0);
                    break;

                case 16 :                            // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                        // fim do switch case para os diferentes tipos de y enquanto x é string
            break;                                   // fim do case quando x é string

        case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

        case 32 :
                break;

    }                                                // fim do switch case para os diferentes tipos de x
}                                                    // fim da função "<"

/**
 * @brief Verifica se o 2º elemento no topo da stack é maior que o 1º  elemento no topo da stack
 *
 * Inicializada com o token ">"
 */
void maior(STACK *s){ // >
    DATA x = pop(s);
    DATA y = pop(s);

        switch(x.type){                             // switch case para os diferentes tipos de x
        case 1 :                                    // case quando x é long
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é long 
                case 1 :                            // case quando y é long enquanto x é long
                    if (y.LONG > x.LONG)
                        push_LONG(s, 1);
                    else
                        push_LONG(s, 0);
                    break;

                case 2 :                            // case quando y é double enquanto x é long
                    if (y.DOUBLE > x.LONG)
                        push_LONG(s, 1);
                    else 
                        push_LONG(s, 0);
                    break;

                case 4 :                            // case quando y é char enquanto x é long
                    if (x.LONG >= 0 && x.LONG < 9)
                        if (y.CHAR > (char)x.LONG)
                            push_LONG(s, 1);
                        else
                            push_LONG(s, 0);
                    else
                        push_LONG(s, 0);
                    break;

                case 8 :                            // case quando y é string enquanto x é long                   
                    push_STRING(s, strdup(y.STRING + strlen(y.STRING) - x.LONG));
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array                    
                    push_ARRAY(s , takeXend(x.LONG, y.ARRAY));
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é long
            break;                                  // fim do case quando x é long

        case 2 :                                    // case quando x é double
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é double
                case 1 :                            // case quando y é long enquanto x é double
                    if (y.LONG > x.DOUBLE)
                        push_LONG(s, 1);
                    else
                        push_LONG(s, 0);
                    break;
            
                case 2 :                            // case quando y é double enquanto x é double
                    if (y.DOUBLE > x.DOUBLE)
                        push_LONG(s, 1);
                    else
                        push_LONG(s, 0);
                    break;

                case 4 :                            // case quando y é char enquanto x é double
                    if ((fmod(x.DOUBLE, 1) == 0) && (x.DOUBLE >= 0 && x.DOUBLE < 9))
                        if (y.CHAR > x.DOUBLE)
                            push_LONG(s, 1);
                        else
                            push_LONG(s, 0);
                    else
                        push_LONG(s, 0);
                    break;

                case 8 :                            // case quando y é string enquanto x é double
                    push_LONG(s, 0);
                    break;

                case 16 :                           // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é double
            break;                                  // fim do case quando x é double

        case 4 :                                    // case quando x é char                  
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é char
                case 1:                             // case quando y é long enquanto x é char
                    if (y.LONG >= 0 && y.LONG < 9)
                        if ((char)y.LONG > x.CHAR)
                           push_LONG(s, 1);
                        else
                            push_LONG(s, 0);
                    else
                        push_LONG(s, 0);
                    break;

                case 2 :                            // case quando y é double enquanto x é char
                    if ( (y.DOUBLE >= 0 && y.DOUBLE < 9) && fmod(y.DOUBLE, 1) == 0)
                        if ((char)y.DOUBLE > x.CHAR)
                            push_LONG(s, 1);
                        else
                            push_LONG(s, 0);
                    else
                        push_LONG(s, 0);
                    break;

                case 4 :                            // case quando y é char enquanto x é char
                    if (y.CHAR > x.CHAR)
                        push_LONG(s, 1);
                    else
                        push_LONG(s, 0);
                    break;

                case 8 :                            // case quando y é string enquanto x é char
                    push_LONG(s, 0);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é char
            break;                                  // fim do case quando x é char                                      

        case 8 :                                    // case quando x é string
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é string
                case 1 :                            // case quando y é long enquanto x é string
                    push_LONG(s, 0);
                    break;

                case 2 :                            // case quando y é double enquanto x é string
                    push_LONG(s, 0);
                    break;

                case 4 :                            // case quando y é char enquanto x é string
                    push_LONG(s, 0);
                    break;

                case 8 :                            // case quando y é string enquanto x é string
                    if (strlen(y.STRING) > strlen(x.STRING))
                        push_LONG(s, 1);
                    else if (strlen(y.STRING) == strlen(x.STRING))
                        if (strcmp(y.STRING, x.STRING) <= 0)
                            push_LONG(s, 0);
                        else if (strcmp(y.STRING, x.STRING) > 0)
                            push_LONG(s, 1);
                        else
                            push_LONG(s, 0);
                    else
                        push_LONG(s,0);

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é string
            break;                                  // fim do case quando x é string

        case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

        case 32 :
            break;

    }                                               // fim do switch case para os diferentes tipos de x
}                                                   // fim da função ">"

/**
 * @brief Negação do elemento no topo da stack
 *
 * Inicializada com o token "!"
 */
void nono(STACK *s){ // !
    DATA x = pop(s);

    switch(x.type){                                 // switch case para os diferentes tipos de x
        case 1 :                                    // case quando x é long
            if (x.LONG == 0)
                push_LONG(s, 1);
            else
                push_LONG(s, 0);
            break;                                  // fim do case quando x é long

        case 2 :                                    // case quando x é double
            if (x.DOUBLE == 0)
                push_LONG(s, 1);
            else
                push_LONG(s, 0);
            break;                                  // fim do case quando x é double

        case 4 :                                    // case quando x é char
            if (x.CHAR == (char)0)
                push_LONG(s, 1);
            else
                push_LONG(s, 0);
            break;                                  // fim do case quando x é char

        case 8 :                                    // case quando x é string
            if (strcmp(x.STRING,"0") == 0)
                push_LONG(s, 1);
            else
                push_LONG(s, 0);
            break;                                  // fim do case quando x é string

        case 16 :                                    // case de ser 16, de x ser do tipo array
            break;

        case 32 :
            break;

    }                                               // fim do switch case para os diferentes tipos de x
}                                                   // fim da função "!"

/**
 * @brief E lógico entre dois elementos da stack
 *
 * Inicializada com o token "e&"
 */
void eE(STACK *s){ // e&
    DATA x = pop(s);
    DATA y = pop(s);

    switch(x.type){                                 // switch case para os diferentes tipos de x
        case 1 :                                    // case quando x é long
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é long
                case 1 :                            // case quando y é long enquanto x é long
                    if (y.LONG == 0 || x.LONG == 0)
                        push_LONG(s, 0);
                    else if (y.LONG > x.LONG)
                        push_LONG(s, y.LONG);
                    else 
                        push_LONG(s, x.LONG);
                    break;

                case 2 :                            // case quando y é double enquanto x é long
                    if (y.DOUBLE == 0 || x.LONG == 0)
                        push_LONG(s, 0);
                    else if (y.DOUBLE > x.LONG)
                        push_DOUBLE(s, y.DOUBLE);
                    else
                        push_LONG(s, x.LONG);
                    break;

                case 4 :                            // case quando y é char enquanto x é long
                    if (y.CHAR == '0' || x.LONG == 0)
                        push_LONG(s, 0);
                    else
                        push_DOUBLE(s, x.LONG);
                    break;

                case 8 :                            // case quando y é string enquanto x é long
                    push_LONG(s, x.LONG);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é long
            break;                                  // fim do case quando x é long

        case 2 :                                    // case quando x é double
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é double
                case 1 :                            // case quando y é long enquanto x é double
                    if (y.LONG == 0 || x.DOUBLE == 0)
                        push_LONG(s, 0);
                    else if (y.LONG > x.DOUBLE)
                        push_LONG(s, y.LONG);
                    else
                        push_DOUBLE(s, x.DOUBLE);
                    break;

                case 2 :                            // case quando y é double enquanto x é double
                    if (y.DOUBLE == 0 || x.DOUBLE == 0)
                        push_LONG(s, 0);
                    else if (y.DOUBLE > x.DOUBLE)
                        push_DOUBLE(s, y.DOUBLE);
                    else
                        push_DOUBLE(s, x.DOUBLE);
                    break;

                    case 4 :                        // case quando y é char enquanto x é double
                    if (y.CHAR == '0' || x.DOUBLE == 0)
                        push_LONG(s, 0);
                    else
                        push_DOUBLE(s, x.DOUBLE);
                    break;

                case 8 :                            // case quando y é string enquanto x é double
                    push_DOUBLE(s, x.DOUBLE);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é double
            break;                                  // fim do case quando x é double

        case 4 :                                    // case quando x é char
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é char
                case 1 :                            // case quando y é long enquanto x é char
                    push_LONG(s, y.LONG);
                    break;

                case 2 :                            // case quando y é double enquanto x é char                           
                    push_DOUBLE(s, y.DOUBLE);
                    break;

                case 4 :                            // case quando y é char enquanto x é char
                    if (y.CHAR > x.CHAR)
                        push_CHAR(s, y.CHAR);
                    else
                        push_CHAR(s, x.CHAR);
                    break;

                case 8 :                            // case quando y é string enquanto x é char
                    if ((char)(strlen(y.STRING)) > x.CHAR )
                        push_STRING(s, y.STRING);
                    else 
                        push_CHAR(s, x.CHAR);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é char
            break;                                  // fim do case quando x é char

        case 8 :                                    // case quando x é string
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é string
                case 1 :                            // case quando y é long enquanto x é string
                    push_LONG(s, y.LONG);
                    break;

                case 2 :                            // case quando y é double enquanto x é string
                    push_DOUBLE(s, y.DOUBLE);
                    break;

                case 4 :                            // case quando y é char enquanto x é string
                    if ( (y.CHAR) > (char)(strlen(x.STRING)) )
                        push_CHAR(s, y.CHAR);
                    else
                        push_STRING(s, x.STRING);
                    break;

                case 8 :                            // case quando y é string enquanto x é string
                    if (strlen(y.STRING) > strlen(x.STRING)) 
                        push_STRING(s, y.STRING);
                    else
                        push_STRING(s , x.STRING);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é string
            break;                                  // fim do case quando x é string

        case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

        case 32 :
                break;

    }                                               // fim do switch case para os diferentes tipos de x
}                                                   // fim da função "e&"

/**
 * @brief OU lógico entre dois elementos da stack
 *
 * Inicializada com o token "e|"
 */
void eOU(STACK *s){ // e|
    DATA x = pop(s);
    DATA y = pop(s);

    switch(x.type){                                 // switch case para os diferentes tipos de x
        case 1:                                     // case quando x é long
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é long
                case 1 :                            // case quando y é long enquanto x é long
                    if (y.LONG == 0)
                        if (x.LONG == 0)
                            push_LONG(s, 0);
                        else 
                            push_LONG(s, x.LONG);
                    else
                        push_LONG(s, y.LONG);
                    break;

                case 2 :                            // case quando y é double enquanto x é long
                    if (y.DOUBLE == 0)
                        if (x.LONG == 0)
                            push_LONG(s, 0);
                        else 
                            push_LONG(s, x.LONG);
                    else
                        push_DOUBLE(s, y.DOUBLE);
                    break;

                case 4 :                            // case quando y é char enquanto x é long
                    if (y.CHAR == '0')
                        if (x.LONG == 0)
                            push_LONG(s, 0);
                        else 
                            push_LONG(s, x.LONG);
                    else
                        push_CHAR(s, y.CHAR);
                    break;

                case 8 :                            // case quando y é string enquanto x é long
                    if (strcmp(y.STRING, "0") == 0) 
                        if (x.LONG == 0)
                            push_LONG(s, 0);
                        else 
                            push_LONG(s, x.LONG);
                    else
                        push_STRING(s, y.STRING);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é long
            break;                                  // fim do case quando x é long

        case 2 :                                    // case quando x é double
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é double
                case 1 :                            // case quando y é long enquanto x é double
                    if (y.LONG == 0)
                        if (x.DOUBLE == 0)
                            push_LONG(s, 0);
                        else 
                            push_DOUBLE(s, x.DOUBLE);
                    else
                        push_LONG(s, y.LONG);
                    break;

                case 2 :                            // case quando y é double enquanto x é double
                    if (y.DOUBLE == 0)
                        if (x.DOUBLE == 0)
                            push_LONG(s, 0);
                        else 
                            push_DOUBLE(s, x.DOUBLE);
                    else
                        push_DOUBLE(s, y.DOUBLE);
                    break;

                case 4 :                            // case quando y é char enquanto x é double
                    if (y.CHAR == '0')
                        if (x.DOUBLE == 0)
                            push_LONG(s, 0);
                        else 
                            push_DOUBLE(s, x.DOUBLE);
                    else
                        push_CHAR(s, y.CHAR);
                    break;

                case 8 :                            // case quando y é string enquanto x é double
                    if (strcmp(y.STRING, "0") == 0)
                        if (x.DOUBLE == 0)
                            push_LONG(s, 0);
                        else 
                            push_DOUBLE(s, x.DOUBLE);
                    else
                        push_STRING(s, y.STRING);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é double
            break;                                  // fim do case quando x é double

        case 4 :                                    // case quando x é char
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é char
                case 1 :                            // case quando y é long enquanto x é char
                    if (y.LONG == 0)
                        if (x.CHAR == '0')
                            push_LONG(s, 0);
                        else 
                            push_CHAR(s, x.CHAR);
                    else
                        push_CHAR(s, y.CHAR);
                    break;

                case 2 :                            // case quando y é double enquanto x é char
                    if (y.DOUBLE == 0)
                        if (x.CHAR == 0)
                            push_LONG(s, 0);
                        else 
                            push_CHAR(s, x.CHAR);
                    else
                        push_DOUBLE(s, y.DOUBLE);
                    break;

                case 4 :                            // case quando y é char enquanto x é char
                    if (y.CHAR == '0')
                        if (x.CHAR == '0')
                            push_LONG(s, 0);
                        else 
                            push_CHAR(s, x.CHAR);
                    else
                        push_CHAR(s, y.CHAR);
                    break;

                case 8 :                            // case quando y é string enquanto x é char
                    if (strcmp(y.STRING, "0") == 0)
                        if (x.CHAR == '0')
                            push_LONG(s, 0);
                        else 
                            push_CHAR(s, x.CHAR);
                    else
                        push_STRING(s, y.STRING);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é char
            break;                                  // fim do case quando x é char

        case 8 :                                    // case quando x é string
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é string
                case 1 :                            // case quando y é long enquanto x é string
                    if (y.LONG == 0)
                        if (strcmp(x.STRING, "0")== 0)
                            push_LONG(s, 0);
                        else 
                            push_STRING(s, x.STRING);
                    else
                        push_CHAR(s, y.CHAR);
                    break;

                case 2 :                            // case quando y é double enquanto x é string
                    if (y.DOUBLE == 0)
                        if (strcmp(x.STRING, "0")== 0)
                            push_LONG(s, 0);
                        else 
                            push_STRING(s, x.STRING);
                    else
                        push_DOUBLE(s, y.DOUBLE);
                    break;

                case 4 :                            // case quando y é char enquanto x é string
                    if (y.CHAR == '0')
                        if (strcmp(x.STRING, "0")== 0)
                            push_LONG(s, 0);
                        else 
                            push_STRING(s, x.STRING);
                    else
                        push_CHAR(s, y.CHAR);
                    break;

                case 8 :                            // case quando y é string enquanto x é string
                    if (strcmp(y.STRING, "0") == 0)
                        if (strcmp(x.STRING, "0")== 0)
                            push_LONG(s, 0);
                        else 
                            push_STRING(s, x.STRING);
                    else
                        push_STRING(s, y.STRING);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é string
            break;                                  // fim do case quando x é string

        case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

        case 32 :
                break;

    }                                               // fim do switch case para os diferentes tipos de x
}                                                   // fim da função "e|"

/**
 * @brief Coloca o menor de 2 valores no topo da stack
 *
 * Inicializada com o token "e<"
 */
void emenor(STACK *s){ // e<
    DATA x = pop(s);
    DATA y = pop(s);

    switch(x.type){                                 // switch case para os diferentes tipos de x
        case 1:                                     // case quando x é long
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é long
                case 1:                             // case quando y é long enquanto x é long
                    if (y.LONG < x.LONG)
                        push_LONG(s, y.LONG);
                    else
                        push_LONG(s, x.LONG);
                    break;

                case 2 :                             // case quando y é double enquanto x é long
                    if (y.DOUBLE < x.LONG)
                        push_DOUBLE(s, y.DOUBLE);
                    else
                        push_LONG(s, x.LONG);
                    break;

                case 4 :                             // case quando y é char enquanto x é long
                    if (x.LONG >= 0 && x.LONG < 9)
                        if (y.CHAR < (char)x.LONG)
                            push_CHAR(s, y.CHAR);
                        else
                            push_LONG(s, x.LONG);
                    else
                        push_LONG(s, x.LONG); 
                    break;

                case 8 :                            // case quando y é string enquanto x é long
                    push_LONG(s, x.LONG);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é long
            break;                                  // fim do case quando x é long

        case 2 :                                    // case quando x é double
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é double
                case 1:                             // case quando y é long enquanto x é double
                    if (y.LONG < x.DOUBLE)
                        push_LONG(s, y.LONG);
                    else
                        push_DOUBLE(s, x.DOUBLE);
                    break;

                case 2 :                            // case quando y é double enquanto x é double
                    if (y.DOUBLE < x.DOUBLE)
                        push_DOUBLE(s, y.DOUBLE);
                    else
                        push_DOUBLE(s, x.DOUBLE);
                    break;

                case 4 :                            // case quando y é char enquanto x é double
                    if ((fmod(x.DOUBLE, 1) == 0) && (x.DOUBLE >= 0 && x.DOUBLE < 9))
                        if (x.DOUBLE < y.CHAR)
                            push_DOUBLE(s, x.DOUBLE);
                        else
                            push_CHAR(s, y.CHAR);
                    else
                        push_LONG(s, y.DOUBLE);
                    break;

                case 8 :                            // case quando y é string enquanto x é double
                    push_DOUBLE(s, x.DOUBLE);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é double
            break;                                  // fim do case quando x é double

        case 4 :                                    // case quando x é char
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é char
                case 1:                             // case quando y é long enquanto x é char
                    if (y.LONG >= 0 && y.LONG < 9)
                        if (x.CHAR < (char)y.LONG)
                           push_CHAR(s, x.CHAR);
                        else
                            push_LONG(s, y.LONG);
                    else
                        push_LONG(s, y.LONG);
                    break;

                case 2 :                            // case quando y é double enquanto x é char
                    if ( (y.DOUBLE >= 0 && y.DOUBLE < 9) && fmod(y.DOUBLE, 1) == 0)
                        if (x.CHAR < (char)y.DOUBLE)
                            push_CHAR(s, x.CHAR);
                        else
                            push_DOUBLE(s, y.DOUBLE);
                    else
                        push_DOUBLE(s, y.DOUBLE);
                    break;

                case 4 :                           // case quando y é char enquanto x é char
                    if (y.CHAR < x.CHAR)
                        push_CHAR(s, y.CHAR);
                    else
                        push_CHAR(s, x.CHAR);
                    break;

                case 8 :                            // case quando y é string enquanto x é char
                    if ((char)(strlen(y.STRING)) < x.CHAR )
                        push_STRING(s, y.STRING);
                    else 
                        push_CHAR(s, x.CHAR);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é char
            break;                                  // fim do case quando x é char

        case 8 :                                    // case quando x é string
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é string
                case 1:                             // case quando y é long enquanto x é string
                    push_LONG(s, y.LONG);
                    break;

                case 2 :                            // case quando y é double enquanto x é string
                    push_DOUBLE(s, y.DOUBLE);
                    break;

                case 4 :                            // case quando y é char enquanto x é string
                    if ( (y.CHAR) < (char)(strlen(x.STRING)) )
                        push_CHAR(s, y.CHAR);
                    else
                        push_STRING(s, x.STRING);
                    break;

                case 8 :                            // case quando y é string enquanto x é string
                    if (strlen(y.STRING) < strlen(x.STRING)) 
                        push_STRING(s, y.STRING);
                    else
                        push_STRING(s , x.STRING);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é string
            break;                                  // fim do case quando x é string

        case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

        case 32 :
                break;

    }                                               // fim do switch case para os diferentes tipos de x
}                                                   // fim da função "e<"


/**
 * @brief Coloca o maior de 2 valores no topo da stack
 *
 * Inicializada com o token "e>"
 */
void emaior(STACK *s){ // e>
    DATA x = pop(s);
    DATA y = pop(s);

    switch(x.type){                                 // switch case para os diferentes tipos de x
        case 1:                                     // case quando x é long
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é long
                case 1:                             // case quando y é long enquanto x é long
                    if (y.LONG > x.LONG)
                        push_LONG(s, y.LONG);
                    else
                        push_LONG(s, x.LONG);
                    break;

                case 2 :                            // case quando y é double enquanto x é long
                    if (y.DOUBLE > x.LONG)
                        push_DOUBLE(s, y.DOUBLE);
                    else
                        push_LONG(s, x.LONG);
                    break;

                case 4 :                            // case quando y é char enquanto x é long
                    if (x.LONG >= 0 && x.LONG < 9)
                        if (y.CHAR > (char)x.LONG)
                            push_CHAR(s, y.CHAR);
                        else
                            push_LONG(s, x.LONG);
                    else
                        push_LONG(s, x.LONG); 
                    break;

                case 8 :                            // case quando y é string enquanto x é long
                    push_LONG(s, x.LONG);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é long
            break;                                  // fim do case quando x é long

        case 2 :                                    // case quando x é double
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é double
                case 1:                             // case quando y é long enquanto x é double
                    if (y.LONG > x.DOUBLE)
                        push_LONG(s, y.LONG);
                    else
                        push_DOUBLE(s, x.DOUBLE);
                    break;

                case 2 :                            // case quando y é double enquanto x é double
                    if (y.DOUBLE > x.DOUBLE)
                        push_DOUBLE(s, y.DOUBLE);
                    else
                        push_DOUBLE(s, x.DOUBLE);
                    break;

                case 4 :                            // case quando y é char enquanto x é double
                    if ((fmod(x.DOUBLE, 1) == 0) && (x.DOUBLE >= 0 && x.DOUBLE < 9))
                        if (x.DOUBLE > y.CHAR)
                            push_DOUBLE(s, x.DOUBLE);
                        else
                            push_CHAR(s, y.CHAR);
                    else
                        push_LONG(s, y.DOUBLE);
                    break;

                case 8 :                            // case quando y é string enquanto x é double
                    push_DOUBLE(s, x.DOUBLE);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é double  
            break;                                  // fim do case quando x é double

        case 4 :                                    // case quando x é char
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é char
                case 1:                             // case quando y é long enquanto x é char
                    if (y.LONG >= 0 && y.LONG < 9)
                        if (x.CHAR > (char)y.LONG)
                           push_CHAR(s, x.CHAR);
                        else
                            push_LONG(s, y.LONG);
                    else
                        push_LONG(s, y.LONG);
                    break;

                case 2 :                            // case quando y é double enquanto x é char
                    if ( (y.DOUBLE >= 0 && y.DOUBLE < 9) && fmod(y.DOUBLE, 1) == 0)
                        if (x.CHAR > (char)y.DOUBLE)
                            push_CHAR(s, x.CHAR);
                        else
                            push_DOUBLE(s, y.DOUBLE);
                    else
                        push_DOUBLE(s, y.DOUBLE);
                    break;

                case 4 :                            // case quando y é char enquanto x é char
                    if (y.CHAR > x.CHAR)
                        push_CHAR(s, y.CHAR);
                    else
                        push_CHAR(s, x.CHAR);
                    break;

                case 8 :                            // case quando y é string enquanto x é char
                    if ((char)(strlen(y.STRING)) > x.CHAR )
                        push_STRING(s, y.STRING);
                    else 
                        push_CHAR(s, x.CHAR);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é char
            break;                                  // fim do case quando x é char

        case 8 :                                    // case quando x é string
            switch(y.type){                         // switch case para os diferentes tipos de y enquanto x é string
                case 1:                             // case quando y é long enquanto x é string
                    push_LONG(s, y.LONG);
                    break;

                case 2 :                            // case quando y é double enquanto x é string
                    push_DOUBLE(s, y.DOUBLE);
                    break;

                case 4 :                            // case quando y é char enquanto x é string
                    if ( (y.CHAR) > (char)(strlen(x.STRING)) )
                        push_CHAR(s, y.CHAR);
                    else
                        push_STRING(s, x.STRING);
                    break;

                case 8 :                            // case quando y é string enquanto x é string
                    if ((strlen(y.STRING) > strlen(x.STRING)) == 0)
                        push_STRING(s, y.STRING);
                    else
                        push_STRING(s , x.STRING);
                    break;

                case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

                case 32 :
                break;
            }                                       // fim do switch case para os diferentes tipos de y enquanto x é string
            break;                                  // fim do case quando x é string

        case 16 :                                    // case de ser 16, de x ser do tipo array
                    break;

        case 32 :
                break;

    }                                               // fim do switch case para os diferentes tipos de x
}                                                   // fim da função "e>"