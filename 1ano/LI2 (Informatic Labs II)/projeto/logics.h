/**
 * @file logics.h
 * @brief Header que inicializa as funções do ficheiro logics.c
 */
#include "stack.h"

void E(STACK *s);
void ou(STACK *s);
void xor(STACK *s);
void not(STACK *s, DATA *vars);
void igual(STACK *s);
void menor(STACK *s);
void maior(STACK *s);
void nono(STACK *s);
void eE(STACK *s);
void eOU(STACK *s);
void emenor(STACK *s);
void emaior(STACK *s);