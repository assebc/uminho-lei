#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "define.h"
#include "hashtable.h"
#include "./modules/user.h"
#include "./modules/commit.h"
#include "./modules/repo.h"

struct ht_entry {
	char *key;
	void *data;
	ht_entry *next;
};

// struct da hashtable
struct ht {
	ht_entry **entries;  // hash slots
};


ht* ht_create() {
	ht *ht = malloc(sizeof ht);

	if (!ht) {
		printf("Erro ao criar hashtable.");
		return NULL;
	}
	ht->entries = calloc(TABLE_SIZE, sizeof(ht_entry));

	return ht;
}

ht_entry* ht_pair(char *key, void *d) {
	ht_entry *entry = malloc(sizeof(ht_entry));
	entry->key = strdup(key);
	entry->data = d;
	entry->next = NULL;

	return entry; 
}

void* ht_get(ht *ht, char *key) {
	int slot = hash(key);

	ht_entry *entry = ht->entries[slot];

	if (entry == NULL)
		return NULL;

	while (entry != NULL) {
		if (strcmp(entry->key, key) == 0)
			return entry->data;

		entry = entry->next;
	}

	return NULL;
}

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

void ht_destroy(ht *ht, void(*delete_data)(void*)) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (ht->entries[i] != NULL) {
			while (ht->entries[i] != NULL) {
				ht_entry *entry = ht->entries[i];
				ht->entries[i] = ht->entries[i]->next;

				free(entry->key);
				delete_data(entry->data); 
				free(entry);
			}
		}
	}
	free(ht->entries);
	free(ht);
}


void ht_init(ht *ht, char *file, void*(*create_type)(void), void(*set_type)(void*, char*), char*(*get_key)(void*)) {
	char line[LINE_BUFFER];

	FILE *f = fopen(file, "r");

	fgets(line, LINE_BUFFER, f);
	
	int j = 0;
	
	while(fgets(line, LINE_BUFFER, f) != NULL) {
		remove_possible_new_line(line);
		
		void* data = create_type();
		set_type(data, line);
		char* key = get_key(data);

		ht_insert(ht, key, data);

		j++;
	}
	printf("LINHAS: %d\n", j);

}
/*void ht_init(ht* ht, char *file, int data_type, int key_i) {
	char line[LINE_BUFFER];

	FILE *f = fopen(file, "r");

	fgets(line, LINE_BUFFER, f);

	int j = 0;
	while (fgets(line, LINE_BUFFER, f) != NULL) {
			
		remove_possible_new_line(line);
		char *key = NULL;

		// para a key ser a linha 
		if (key_i == 0)
			key = line;

		if (data_type == 0) {
			USER u = create_user();
			set_user(u, line);

		// para a key ser o id
			if (key_i == 1)
				key = get_user_id(u);

			ht_insert(ht, key, u);
		} 
		else if (data_type == 1) {
			COMMIT c = create_commit();
			set_commit(c, line);

			// para a key ser o committer_id
			if (key_i == 2)
				key = get_commit_committer_id(c);

			//para a key ser o author_id
			else if (key_i == 3)
				key = get_commit_author_id(c);

			ht_insert(ht, key, c);
		}
		else {
			REPO r = create_repo();
			set_repo(r, line);
			ht_insert(ht, line, r);
		}

		if (key_i > 0)
			free(key);
		j++;
	}
	printf("LINHAS: %d\n", j);
	fclose(f);
}
*/
int hash(char *key) {
    unsigned int value = 0;
    int i = 0;
    int key_len = strlen(key);

    // do several rounds of multiplication
    for (; i < key_len; ++i) {
        value = value * 37 + key[i];
    }

    // make sure value is 0 <= value < TABLE_SIZE
    value = value % TABLE_SIZE;

    return value;
}


void count_types(ht *ht, int *bots, int *orgs, int *users){

	for(int i=0; i<TABLE_SIZE; i++){

		ht_entry *temp = ht->entries[i];


		while(ht->entries[i] != NULL && temp != NULL){
			if(strcmp(get_user_type(ht->entries[i]->data), "Bot") == 0) (*bots)++;
			else if(strcmp(get_user_type(ht->entries[i]->data), "Organization") == 0) (*orgs)++;
			else if(strcmp(get_user_type(ht->entries[i]->data), "User") == 0) (*users)++;

			temp = temp->next;
		}
		free(temp);
	}
}

/*
void remove_commits_by_user(ht *users_ht) {
	int elem = 0;
	for (int i = 0; i < TABLE_SIZE; i++) {
		ht_entry *commit_entry = commits_ht->entries[i];

		while (commit_entry != NULL) {
			elem++;
			commit_entry = commit_entry->next;
		}
	}
	printf("COMMITS: %d\n", elem);
}
*/