#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "define.h"
#include "eval.h"
#include "user.h"
#include "commit.h"
#include "repo.h"

struct ht_entry {
	char *key;
	void *data;
	struct ht_entry *next;
};

// struct da hashtable
struct ht {
	struct ht_entry **entries;  // hash slots
};

/**
 * @brief Função hash
 *
 * Função que através de determinada key calcula um valor para a sua hash, para a futura inserção na hashtable
 * 
 * @returns valor de hash
 */
int hash(char *key) {
    unsigned int value = 0;
    int i = 0;
    int key_len = strlen(key);

    for (; i < key_len; ++i) {
        value = value * 37 + key[i];
    }

    // 0 <= value < TABLE_SIZE
    value = value % TABLE_SIZE;

    return value;
}

struct ht* ht_create(int size) {
	struct ht *ht = malloc(sizeof ht);

	if (!ht) {
		printf("Erro ao criar hashtable.");
		return NULL;
	}
	ht->entries = calloc(size, sizeof(struct ht_entry));

	return ht;
}

struct ht_entry* ht_pair(char *key, void *d) {
	struct ht_entry *entry = malloc(sizeof(struct ht_entry));
	entry->key = strdup(key);
	entry->data = d;
	entry->next = NULL;

	return entry; 
}

void* ht_get(struct ht *ht, char *key, void*(*create_data)(void),void(*copy_data)(void*, void*)) {
	int slot = hash(key);

	struct ht_entry *entry = ht->entries[slot];

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

void ht_del(struct ht *ht, char *key) {
	int slot = hash(key);

	struct ht_entry *entry = ht->entries[slot];

	if (entry == NULL)
		return;

	struct ht_entry *prev;
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

void ht_insert(struct ht *ht, char *key, void *d) {
	int slot = hash(key);

	struct ht_entry *entry = ht->entries[slot];

	if (entry == NULL) {
		ht->entries[slot] = ht_pair(key, d);
		return;
	}

	struct ht_entry *prev;
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

void ht_destroy(struct ht *ht, void(*delete_data)(void*)) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (ht->entries[i] != NULL) {
			struct ht_entry *entry = ht->entries[i];
			while (entry != NULL) {
				
				struct ht_entry *temp = entry;
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
}


void ht_init(struct ht *ht, char *file, void*(*create_type)(void), void(*set_type)(void*, char*), char*(*get_key)(void*)) {
	char line[LINE_BUFFER];

	FILE *f = fopen(file, "r");

	fgets(line, LINE_BUFFER, f);
	
	int j = 0;
	
	while(fgets(line, LINE_BUFFER, f) != NULL) {
		removePossibleNewLine(line);
		
		void* data = create_type();
		set_type(data, line);
		char* key = get_key(data);

		ht_insert(ht, key, data);

		free(key);
		j++;
	}
	fclose(f);
}

int ht_count(struct ht *ht) {
	int j = 0;
	for (int i = 0; i < TABLE_SIZE; i++) {
		struct ht_entry *temp = ht->entries[i];
		while (temp != NULL) {
			temp = temp->next;
			j++;
		}
	}
	return j;
}

void ht_print_table(struct ht *ht) {
	for (int i = 0; i < TABLE_SIZE; i++) {

		struct ht_entry *temp = ht->entries[i];

		while (temp != NULL) {
			printf("USER: %s  COMMITS: %d\n",temp->key, *((int*)temp->data));
			temp = temp->next;
		}
	}
}
