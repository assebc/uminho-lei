/**
 * @file stack.c
 * @brief Ficheiro que contém as funções relativas ao funcionamento da nossa stack
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "maths.h"
#include "logics.h"
#include "manpln.h"

/**
 * @brief Verifica o tipo de um elemento
 *
 * Recebendo um elemento do tipo DATA e uma mask analisa se o tipo do elemento coincide com o da máscara indicada.
 * 
 * @param elem Elemento que queremos avaliar
 * @param mask Máscara que representa um tipo de dados
 *
 * @returns 0 se o elemento for do tipo da máscara e diferente de 0 caso contrário.
 */
int has_type(DATA elem, int mask){
	return (elem.type & mask) != 0;
}

/**
 * @brief Função que reserva memória para a stack
 *
 * Reserva a memória necessária definindo os parâmetros da capacidade e o topo da stack.
 *
 * @returns uma struct representante da stack
 */
STACK *new_stack(){
	STACK *s = (STACK *) calloc(1, sizeof(STACK));
	s->size = 100;
	s->stack = (DATA *) calloc(s->size, sizeof(DATA));
	return s;
}

/**
 * @brief Faz push de um elemento para a stack
 *
 * Incrementa o indicador do topo da stack e insere o elemento dado.
 * Reserva espaço adicional para a stack caso necessário.
 * 
 * @param *s Struct onde se encontra a stack
 * @param elem Elemento para inserir na stack
 * @returns esta função não devolve nenhum valor
 */
void push(STACK *s, DATA elem){
	if(s->size == s->n_elems){
		s->size += 100;
		s->stack = (DATA *) realloc(s->stack, s->size * sizeof(DATA));
	}
	s->stack[s->n_elems] = elem;
	s->n_elems++;
}

/**
 * @brief Faz pop de um elemento para fora a stack
 *
 * Decrementa o indicador do topo da stack e insere o elemento dado.
 * 
 * @param *s Struct onde se encontra a stack
 * @returns elemento que saiu da stack
 */
DATA pop(STACK *s){
	s->n_elems--;
	return s->stack[s->n_elems];
}

/**
 * @brief Indica o elemento no topo da stack
 * 
 * @param *s Struct onde se encontra a stack
 * @returns o elemento no topo da stack
 */
DATA top(STACK *s){
	return s->stack[s->n_elems -1];
}

/**
 * @brief Indica se a stack está vazia
 * 
 * @param *s Struct onde se encontra a stack
 * @returns 0 se estiver vazia e um nº diferente de zero se não estiver
 */
int is_empty(STACK *s){
	return (s->n_elems == 0);
}

/**
 * @brief Imprime a stack
 * 
 * Percorre a stack e imprime os elementos nela contidos.
 *
 * @param *s Struct onde se encontra a stack
 * @returns esta função não devolve nenhum valor
 */
void print_stack(STACK *s){
	for(int i = 0; i <s->n_elems; i++){
		DATA elem = s->stack[i];
		TYPE type = elem.type;

		switch(type){
			case 1	: 
				printf("%ld", elem.LONG);
				break;

			case 2	:	 
				printf("%g", elem.DOUBLE);
				break;

			case 4	: 
				printf("%c", elem.CHAR);
				break;

			case 8	: 
				printf("%s", elem.STRING);
				break;

			case 16 :
				print_array(elem.ARRAY);
				break;

            case 32 :
            	printf("%s", elem.BLOCO);
                break;
		}
	}
	printf("\n");
}
/**
 * @brief Imprime um array
 * 
 * Percorre a stack correspondente ao array e imprime os elementos nele contidos.
 *
 * @param *s Struct onde se encontra os elementos do array
 * @returns esta função não devolve nenhum valor
 */
void print_array(STACK *s){
	for(int i = 0; i <s->n_elems; i++){
		DATA elem = s->stack[i];
		TYPE type = elem.type;

		switch(type){
			case 1	: 
				printf("%ld", elem.LONG);
				break;

			case 2	:	 
				printf("%g", elem.DOUBLE);
				break;

			case 4	: 
				printf("%c", elem.CHAR);
				break;

			case 8	: 
				printf("%s", elem.STRING);
				break;

			case 16 :
				print_array(elem.ARRAY);
				break;

			case 32 :
				printf("%s", elem.BLOCO);
				break;
		}
	}
}

/**
 * @brief Função push para elementos do tipo LONG
 */
void push_LONG(STACK *s, long val){
		DATA elem;
		elem.type = LONG;
		elem.LONG = val;
		push(s, elem);
}

/**
 * @brief Função push para elementos do tipo DOUBLE
 */
void push_DOUBLE(STACK *s, double val){
		DATA elem;
		elem.type = DOUBLE;
		elem.DOUBLE = val;
		push(s, elem);
	}

/**
 * @brief Função push para elementos do tipo CHAR
 */
void push_CHAR(STACK *s, char val){
		DATA elem;
		elem.type = CHAR;
		elem.CHAR = val;
		push(s, elem);
}

/**
 * @brief Função push para elementos do tipo STRING
 */
void push_STRING(STACK *s, char * val){
		DATA elem;
		elem.type = STRING;
		elem.STRING = val;
		push(s, elem);
}

/**
 * @brief Função push para elementos do tipo ARRAY
 */
void push_ARRAY(STACK *s, STACK * val){
		DATA elem;
		elem.type = ARRAY;
		elem.ARRAY = val;
		push(s, elem);
	}

/**
 * @brief Função push para elementos do tipo bloco
 */
void push_BLOCO(STACK *s, char * val){
		DATA elem;
		elem.type = BLOCO;
		elem.BLOCO = val;
		push(s, elem);
	}

/**
 * @brief Função pop para elementos do tipo LONG
 */
long pop_LONG(STACK *s){
		DATA elem = pop(s);
		assert(elem.type == LONG);
		return elem.LONG;
}

/**
 * @brief Função pop para elementos do tipo DOUBLE
 */
double pop_DOUBLE(STACK *s){
		DATA elem = pop(s);
		assert(elem.type == DOUBLE);
		return elem.DOUBLE;
}

/**
 * @brief Função pop para elementos do tipo CHAR
 */
char pop_CHAR(STACK *s){
		DATA elem = pop(s);
		assert(elem.type == CHAR);
		return elem.CHAR;
}

/**
 * @brief Função pop para elementos do tipo STRING
 */
char * pop_STRING(STACK *s){
		DATA elem = pop(s);
		assert(elem.type == STRING);
		return elem.STRING;
}

/**
 * @brief Função pop para elementos do tipo ARRAY
 */
STACK * pop_ARRAY(STACK *s){
		DATA elem = pop(s);
		assert(elem.type == ARRAY);
		return elem.ARRAY;
	}

/**
 * @brief Define os valores por omissão das variáveis da stack
 */
void allocvars(DATA *array) { // regista os valores das variáveis num array multi-tipo

	
	array[0].LONG = 10; array[0].type= 1;
	
	array[1].LONG = 11; array[1].type= 1;
	
	array[2].LONG = 12; array[2].type= 1;	
	
	array[3].LONG = 13; array[3].type= 1;
	
	array[4].LONG = 14; array[4].type= 1;
	
	array[5].LONG = 15; array[5].type= 1;

		// definição por omissão A a F
	array[13].CHAR = '\n'; array[13].type= 4;
		// definição por omissão N (new line)
	
	array[18].STRING = strdup(" "); array[18].type= 8;							// definição por omissão S (space em forma de string)
	
	array[23].LONG = 0; array[23].type= 1;
	
	array[24].LONG = 1; array[24].type= 1;
	
	array[25].LONG = 2; array[25].type= 1; // definição por omissão N, S, X, Y, Z

}