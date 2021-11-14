/**
 * @file manpln.h
 * @brief Header que inicializa as funções do ficheiro manpln.c
 */
#include "stack.h"

void duplica(STACK *s);
void troca(STACK *s);
void rodar(STACK *s);
void copia(STACK *s, DATA *vars);
void question(STACK *s);

void atributo(STACK *s, char *letra, DATA *array);
void letra(STACK *s, char letra, DATA *array);

long stringToLong(char *string);
void intz(STACK *s);
void charz(STACK *s);
void doublez(STACK *s);
void stringz(STACK *s);

void lerl(STACK *s);
void lert(STACK *s);
void printt(STACK *s);

