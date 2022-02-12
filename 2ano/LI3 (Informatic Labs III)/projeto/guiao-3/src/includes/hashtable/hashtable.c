/**
 * @file hashtable.c
 * @brief Ficheiro que contém as funções para criação e manuseamento das hashtables
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../parser.h"
#include "../define.h"
#include "hashtable.h"
//#include "../linkedlist.h"

/** 
 * Definição dos slots
 * 
 * Tem uma key, data, e o próximo elemento
 * 
 */
struct ht_entry {
	char *key;
	void *data;
	ht_entry *next;
};

/** 
 * Definição da struct hashtable
 * 
 * Tem uma parcela que são os slots (linked lists)
 * 
 */
struct ht {
	ht_entry **entries;  // hash slots
};

/**
 * @brief Função ht_create
 *
 * Função que cria hashtable
 * 
 * @returns hashtable
 */
ht* ht_create(int size) {
	ht *ht = malloc(sizeof ht);

	if (!ht) {
		printf("Erro ao criar hashtable.");
		return NULL;
	}
	ht->entries = calloc(size, sizeof(ht_entry));

	//printf("A table was created\n");
	return ht;
}

/**
 * @brief Função ht_pair
 *
 * Função que cria um par de determinada key
 * 
 * @returns entry da hashtable (nodo)
 */
static ht_entry* ht_pair(char *key, void *d) {
	ht_entry *entry = malloc(sizeof(ht_entry));

	if (entry == NULL) {
		printf("Erro ao criar entry na hashtable\n");
		return NULL;
	}

	entry->key = strdup(key);
	entry->data = d;
	entry->next = NULL;

	return entry; 
}

/**
 * @brief Função ht_get
 *
 * Função que obtem determinada slot
 * 
 * @returns data do slot
 */
void* ht_get(ht *ht, char *key, void*(*create_data)(void),void(*copy_data)(void*, void*)) {
	int slot = hash(key);

	ht_entry *entry = ht->entries[slot];

	if (entry == NULL)
		return NULL;

	while (entry != NULL) {
		if (strcmp(entry->key, key) == 0) {
			void* d = create_data();
			copy_data(d, entry->data);
			return d;
		}

		entry = entry->next;
	}

	return NULL;
}

/**
 * @brief Função ht_get_no_mem_cpy
 *
 * Função que obtem determinado elemento dentro de uma slot 
 * 
 * @returns devolve o endereco desse elemento dentro da hashtable
 */
void* ht_get_no_mem_cpy(ht *ht, char *key) {
	int slot = hash(key);

	ht_entry *entry = ht->entries[slot];

	if (entry == NULL)
		return NULL;

	while (entry != NULL) {
		if (strcmp(entry->key, key) == 0) {
			return entry->data;
		}

		entry = entry->next;
	}

	return NULL;
}

/**
 * @brief Função ht_get_s
 *
 * Função que devolve o proximo elemento na tabela por ordem de slots
 * e nodos das listas ligadas dentro de cada slot
 *
 * @returns endereco do proximo elemento
 */
char* ht_get_s(ht *ht, int *slot, int *node, void** d) {

	ht_entry *entry = ht->entries[*slot];
	while (entry == NULL) {
		(*slot)++;
			if (*slot  >= TABLE_SIZE-1)
				return NULL;
			
		entry = ht->entries[++(*slot)];
	}

	if (*slot  >= TABLE_SIZE-1)
		return NULL;

	for (int i = 0; i < *node; i++)
		entry = entry->next;
	
	if (entry == NULL) {
		*node = 0;
		(*slot)++;
		return ht_get_s(ht, slot, node, d);
	}

	(*node)++;
	*d = entry->data;
	return entry->key; 
}

/**
 * @brief Função ht_del
 *
 * Função que remove um slot de uma hashtable
 * 
 */
void ht_del(ht *ht, char *key) {
	int slot = hash(key);

	ht_entry *entry = ht->entries[slot];

	if (entry == NULL)
		return;

	ht_entry *prev;
	int idx = 0;

	while (entry != NULL) {
		if (strcmp(entry->key, key) == 0){
			// ser o primeiro item e nao haver next
			if (entry->next == NULL && idx == 0){
				ht->entries[slot] = NULL;
			}

			// ser o primeiro item mas haver next
			if (entry->next != NULL && idx == 0){
				ht->entries[slot] = entry->next;
			}

			// ser o ultimo item
			if (entry->next == NULL && idx != 0){
				prev->next = NULL;
			}

			// item do meio
			if (entry->next != NULL && idx != 0){
				prev->next = entry->next;
			}
		
			free(entry->key);
			free(entry->data);
			free(entry);

			return;
		}
		prev = entry;
		entry = prev->next;

		idx++;
	}
}

/**
 * @brief Função ht_insert
 *
 * Função que insere um elemento na hashtable 
 * (mesma hash e keys diferentes => insere no proximo nodo da lista ligada)
 * (mesma hash e mesma key => substitui o nodo)
 * (diferentes hash => insere noutro slot)
 *
 */
void ht_insert(ht *ht, char *key, void *d) {
	int slot = hash(key);

	ht_entry *entry = ht->entries[slot];

	if (entry == NULL) {
		ht->entries[slot] = ht_pair(key, d);
		return;
	}

	ht_entry *prev;
	while (entry != NULL) {
		if (strcmp(entry->key, key) == 0) {
			free(entry->data);
			entry->data = d;
			return;
		}

		prev = entry;
		entry = prev->next;
	}
	prev->next = ht_pair(key, d);
}

/**
 * @brief Função ht_insert_2
 *
 * Função que insere o elemento na hashtable
 * (mesma hash e mesma key => insere no proximo nodo)
 * (mesma hash e keys diferentes => procura um proximo slot vazio)
 * 
 */
void ht_insert_2(ht *ht, char *key, void* data) {
	int slot = hash(key);

	ht_entry *entry = ht->entries[slot];

	while (entry != NULL) {
		if (strcmp(entry->key, key) == 0) {

			ht_entry *prev;

			while (entry != NULL) { 
				prev = entry;
				entry = prev->next;
			}
			prev->next = ht_pair(key, data);
			return;
		}
		slot++;
		entry = ht->entries[slot];

		if (slot >= TABLE_SIZE)
			printf("ERRO SLOT > TABLE_SIZE");
	}

	ht->entries[slot] = ht_pair(key, data);
}

/**
 * @brief Função ht_insert_3
 *
 * Função que insere o elemento na hashtable
 * 
 * 
 */
void ht_insert_3(ht *ht, char *key, void *data) {
	int slot = hash(key);

	ht_entry *entry = ht->entries[slot];

	while (entry != NULL) {
		if (strcmp(entry->key, key) == 0) {

			ht_entry *prev;

			while (entry != NULL) {
				if (strcmp(data, entry->data) == 0)
					return;

				prev = entry;
				entry = prev->next;
			}

			prev->next = ht_pair(key, data);
			return;
		}
		slot++;
		if (slot >= TABLE_SIZE)
			printf("Erro, SLOT > TABLE_SIZE");
		entry = ht->entries[slot];
	}
	if (entry == NULL) {
		ht->entries[slot] = ht_pair(key, data);
	}
}

/**
 * @brief Função ht_incrementation_pair
 *
 * Função que cria um nodo e inicializa o seu data a 1
 * 
 * @returns entry da hashtable
 */
static ht_entry* ht_incrementation_pair(char *key) {
	ht_entry *entry = malloc(sizeof(ht_entry));
	entry->key = strdup(key);
	entry->data = malloc(sizeof(int));
	*((int*)entry->data) = 1;
	entry->next = NULL;

	return entry; 
}

/**
 * @brief Função ht_incrementation_insert
 *
 * Função que insere o elemento na hash key a seguir
 * Utilizado para o catálogo dos commits
 * 
 */
void ht_incrementation_insert(ht *ht, char* key) {
	int slot = hash(key);
	
	ht_entry * entry = ht->entries[slot];

	if (entry == NULL) {
		ht->entries[slot] = ht_incrementation_pair(key);
		return;
	}

	ht_entry *prev;
	while (entry != NULL) {
		if (strcmp(entry->key, key) == 0) {
			*((int*)entry->data) = *((int*)entry->data) + 1 ;
			return;
		}
		prev = entry;
		entry = prev->next;
	}
	prev->next = ht_incrementation_pair(key);
}

struct commit_size {
	char *row;
	int size;
};

/*void ht_top_insertion(ht *ht, char *key, commit_size *c_s) {
	int slot = hash(key);

	ht_entry *current;

	ht_entry *entry = ht->entries[slot];	

	if (entry == NULL) {
		ht->entries[slot] = //Pair
		return;
	}

	current = entry;
	while (entry->next != NULL) {
		if (strcmp(entry->key, key) == 0) {
			
			commit_size *c_st = (*commit_size) entry->data;
			
			if (c_s->size > c_st->size)	
		
		}
		else {
			slot++;
			entry = ht->entries[slot];
		}
	}
}*/

/**
 * @brief Função ht_destroy
 *
 * Função que liberta a memória utilizada pela hashtable
 * 
 */
void ht_destroy(ht *ht, void(*delete_data)(void*)) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (ht->entries[i] != NULL) {
			ht_entry *entry = ht->entries[i];
			while (entry != NULL) {
				
				ht_entry *temp = entry;
				entry = entry->next;

				free(temp->key);
				if (delete_data == NULL)
					free(temp->data);
				else
					delete_data(temp->data);
				free(temp);
			}
		}
	}
	free(ht->entries);
	free(ht);

	//printf("A table was released\n");
}

/**
 * @brief Função ht_destroy_no_mem_cpy
 *
 * Função que destroi a hashtable sem perdér os dados
 * 
 */
void ht_destroy_no_mem_cpy(ht *ht) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (ht->entries[i] != NULL) {
			ht_entry *entry = ht->entries[i];
			while (entry != NULL) {
				
				ht_entry *temp = entry;
				entry = entry->next;

				free(temp->key);
				free(temp);
			}
		}
	}
	free(ht->entries);
	free(ht);

	//printf("A table was released\n");
}

/**
 * @brief Função ht_count
 *
 * Função que conta o número de entradas de uma hashatable
 * 
 * @returns número de entradas da hashtable
 */
int ht_count(ht *ht) {
	int j = 0;
	for (int i = 0; i < TABLE_SIZE; i++) {
		ht_entry *temp = ht->entries[i];
		while (temp != NULL) {
			temp = temp->next;
			j++;
		}
	}
	return j;
}

/**
 * @brief Função ht_print_table
 *
 * Função que printa a hashtable
 * 
 */
void ht_print_table(ht *ht) {
	for (int i = 0; i < TABLE_SIZE; i++) {

		ht_entry *temp = ht->entries[i];

		while (temp != NULL) {
			printf("REPO_ID: %s X: %d\n",temp->key, *(int*)temp->data);
			temp = temp->next;
		}
	}
}

/*

TO DO

função interior itera dentro da hashtable 
e retira os dados para fora e não a estrutura

filter or smth, mas tudo dentro do catálogo

aumentar tamanho da hash não vai funcionar: 
hashtable de ficheiros?
hashtable de hashtable?
2 hashtables por ficheiros?


*/
