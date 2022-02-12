#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "define.h"
#include "linkedlist.h"

struct node {
	void *data;
	node *next;
};

void node_push(node **n, void* data) {
	node *new_node = (node *) malloc(sizeof(node));

	new_node->data = data;
	new_node->next = *n;

	*n = new_node;
}


// Elimina uma lista ligada
void node_destroy(node *n, void(*delete_data)(void *)) {
	
	node *temp = NULL;

	while (n != NULL) {

		temp = n;
		n = n->next;
		delete_data(temp->data);
		free(temp);
	}
	n = NULL;
}

// Retorna o data do primeiro nodo que encontra atravez de uma key
void* node_get(node *n, char* key, char*(get_specific_data)(void*)) {
	node *temp = n;
	while (temp != NULL) {
		char* data = get_specific_data(temp->data);
		if (strcmp(key, data) == 0) {
			free (data);
			return temp->data;
		}
		temp = temp->next;
	}

	return NULL;
}

void* node_get_s(node **n) {
	if (*n != NULL) {
		void* data = (*n)->data;
		*n = (*n)->next;
		return data;
	}
	return NULL;
}


// Imprime uma lista ligada
void node_print(node *n, void(*print)(void*)) {
	while (n != NULL) {
		print(n->data);
		n = n->next;
	}
}

// Conta o numero de elementos de uma lista ligada
int node_count(node *n) {
	int i = 0;
	while (n != NULL) {
		n = n->next;
		i++;
	}
	return i;
}

