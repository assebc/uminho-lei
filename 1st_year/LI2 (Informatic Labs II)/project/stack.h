/**
 * @file stack.h
 * @brief Header que inicializa as funções do ficheiro stack.c
 */
#ifndef ___STACK_H___
#define ___STACK_H___

#include <stdbool.h>
#include <assert.h>


/** Atribuição de constantes aos tipos (masks) */
typedef enum {
	/** long é enumerado como tipo 1 */
	LONG = 1,
	/** long é enumerado como tipo 2 */
	DOUBLE = 2,
	/** long é enumerado como tipo 4 */
	CHAR = 4, 
	/** long é enumerado como tipo 8 */
	STRING = 8,
	/** long é enumerado como tipo 16 */
	ARRAY = 16,
	/** long é enumerado como tipo 32 */
	BLOCO = 32
} TYPE;

/** pré definição da stack */
struct stack;

/** pré definição dos tipos stack */
typedef struct stack STACK;

/** Tipos possíveis de data */
typedef struct data {
	/** forma de identificar um tipo */
	TYPE type;
	/** tipo long */
	long LONG;
	/** tipo double */
	double DOUBLE;
	/** tipo char */
	char CHAR;
	/** tipo string */
	char *STRING;
	/** tipo array */
	STACK *ARRAY;
	/** tipo bloco */
	char *BLOCO;
} DATA;

/** definição da struct e do tipo stack */
typedef struct stack{
	/** array com todos os possíveis chars para atributos (abcedário) */
	DATA *stack;
	/** espaço de memória total que a stack permite */
	int size;
	/** número de elementos dados para a stack */
	int n_elems;
} STACK;

int has_type(DATA elem, int mask);
STACK *new_stack();
void push(STACK *s, DATA elem);
DATA pop(STACK *s);
DATA top(STACK *s);
int is_empty(STACK *s);
void print_stack(STACK *s);
void print_array(STACK *s);
void push_LONG(STACK *s, long val);
void push_DOUBLE(STACK *s, double val);
void push_CHAR(STACK *s, char val);
void push_STRING(STACK *s, char * val);
void push_ARRAY(STACK *s, STACK * val);
void push_BLOCO(STACK *s, char * val);
long pop_LONG(STACK *s);
double pop_DOUBLE(STACK *s);
char pop_CHAR(STACK *s);
char *pop_STRING(STACK *s);
STACK *pop_ARRAY(STACK *s);
void allocvars(DATA *array);

#endif