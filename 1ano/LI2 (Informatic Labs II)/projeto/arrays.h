/**
 * @file logics.h
 * @brief Header que inicializa as funções do ficheiro arrays.c
 */
#include "stack.h"

void inverteArray(STACK *input, STACK *output);
void concatenar(STACK *pri, STACK *sec);
void range(STACK *s, DATA *vars);
void sspace(STACK *s);
void whiteSpaces(STACK *stack, char *string);
void nspace(STACK *s);
void seek(long n, STACK *array, STACK *stack);
void takeXstart(long n, STACK *array);
STACK *takeXend(long n, STACK *array);
void seeknstring(long n, char *string, STACK *stack);
void concatvar(STACK *s, long i);
void concatvarstr(char *string, long n);
char *concatstr(char *dest, char *src);
void removeUltArray(STACK *stack, STACK *array);
void removePrimArray(STACK *stack, STACK *array);
void concatSTART(DATA elem, STACK* array);
char *concatAny(DATA elem, char *string);
long strsearch(char *sub, char *string);
void subarray (STACK *stack, char *sub, char *string);
char *DATAtoSTR(DATA elem);
void aplica (STACK *stack, DATA bloco, DATA *vars);
void map(STACK *stack, DATA bloco, STACK *array, DATA *vars);
void mapstring(STACK *stack, DATA bloco, char * string, DATA *vars);
void filter(STACK *stack, DATA bloco, DATA *vars);
void fold(STACK *stack, DATA bloco, STACK *array, DATA *vars);
STACK *sortArray (STACK *array);
void ordena(STACK *stack, DATA bloco, DATA *vars);
void trufy(STACK *stack, char *bloco, DATA *vars);
