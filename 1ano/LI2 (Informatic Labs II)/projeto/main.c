/**
 * @file main.c
 * @brief Ficheiro que contém a função principal do programa
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "stack.h"
#include "maths.h"
#include "logics.h"
#include "manpln.h"
#include "eval.h"

// gcc -std=gnu11 -Wall -pedantic-errors -O *.c -lm

/**
 * @brief Função main
 *
 * Ponto de partida da execução do nosso programa.
 *
 * @param line Array onde serão armazenados os caracteres inseridos no programa.
 * @returns 0
 */
int main(void){

	STACK *s = new_stack();
    char line[10240];
    DATA *vars[26];
    for(int i = 0; i < 26; i++) vars[i] = (DATA *)malloc(sizeof(DATA));
    allocvars(*vars);//DATA array[26];

    assert(fgets(line, 10240, stdin) != NULL);
    assert(line[strlen(line) - 1] == '\n');
    
    s = eval(line, s, *vars);
    print_stack(s); // print result
	free(s);

    return 0;
}