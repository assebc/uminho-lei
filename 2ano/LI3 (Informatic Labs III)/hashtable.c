#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include "define.h"


typedef struct{
	char * idU;
	char ** idR;
} Data_2;

typedef struct{
	char * idR;
	int commit_R;
} Data_R;

/*

idU, *commiter_id, *author_id, *owner_id, *idR, *repo_id
commiter_id == idU, author_id = idU // repo_id == idR // owner_id == idU // idR == repo_id

standard_columns[0] = "repo_id;author_id;committer_id;commit_at;message"; // commits
standard_columns[1] = "id;login;type;created_at;followers;follower_list;following;following_list;public_gists;public_repos"; // users
standard_columns[2] = "id;owner_id;full_name;license;has_wiki;description;language;default_branch;created_at;updated_at;forks_count;open_issues;stargazers_count;size"; // repos

*/


Data_2 * hash_table[TABLE_SIZE];

unsigned int hash(char * idU){
	int id = atoi(idU);
	unsigned int hash_value = 0;

	for (int i=0;i;i++){
		hash_value = (id / TABLE_SIZE) / 100;
	}

	return hash_value;
}

Data_R * hash_tableR[TABLE_SIZE];

unsigned int hashR(char * idR){
	int id = atoi(idR);
	unsigned int hash_value = 0;

	for (int i=0;i<id;i++){
		hash_value = id % TABLE_SIZE;
	}

	return hash_value;
}

void init_hash_table(){
	for (int i=0;i<TABLE_SIZE;i++){
		hash_table[i] = NULL;
	}
	// table is empty
}

void init_hash_tableR(){
	for (int i=0;i<TABLE_SIZE;i++){
		hash_tableR[i] = NULL;
	}
	// table is empty
}
// checkcommituser checkrepositorycommit removerepositoryuser removerepositorycommit
void print_table(){
	printf("Start\n");
	for (int i=0; i< TABLE_SIZE;i++){
		if (hash_table[i] == NULL){
			printf("\t%i\t---\n",i);
		} else if (hash_table[i] == DELETED_NODE){
			printf("\t%i\t---<deleted>\n",i);
		} else {
			printf("\t%i\t%s\n",i, hash_table[i]->idU); // commiter_id é o guided id
		}
	}
	printf("End\n");
}

void print_tableR(){
	printf("Start\n");
	for (int i=0; i< TABLE_SIZE;i++){
		if (hash_tableR[i] == NULL){
			printf("\t%i\t---\n",i);
		} else if (hash_tableR[i] == DELETEDR_NODE){
			printf("\t%i\t---<deleted>\n",i);
		} else {
			printf("\t%i\t%s\n",i, hash_tableR[i]->idR); // commiter_id é o guided id
		}
	}
	printf("End\n");
}



bool hash_table_insert(Data_2 * p){
	if (p == NULL) return false;
	int index = hash(p->idU);
	for(int i=0;i < TABLE_SIZE;i++){
		int try = ((i + index) / TABLE_SIZE) / 100;
		if (hash_table[try] == NULL || hash_table[try] == DELETED_NODE){
			hash_table[try] = p;
			return true;
		}
	}

	return false;
}

bool hash_table_insertR(Data_R * p){
	if (p == NULL) return false;
	int index = hash(p->idR);
	for(int i=0;i < TABLE_SIZE;i++){
		int try = (i + index) % TABLE_SIZE;
		if (hash_tableR[try] == NULL || hash_tableR[try] == DELETEDR_NODE){
			hash_tableR[try] = p;
			return true;
		}
	}

	return false;
}

bool hash_insert(char * p){
	if (p == NULL) return false;

	Data_2 * pr = malloc(sizeof(*pr));
	pr->idU = p; pr->idR = NULL;
	hash_table_insert(pr);
	return true;
}

bool hash_insertR(char * p){
	if (p == NULL) return false;

	Data_R * pr = malloc(sizeof(*pr));
	pr->idR = p; pr->commit_R = 0;
	hash_table_insertR(pr);
	return true;
}

bool hash_table_member_insert(Data_2 * p, char * idR, char * repo_id){
	if (p == NULL) return false;
	int index = hash(p->idU);
	for(int i=0;i < TABLE_SIZE;i++){
		int try = (i + index) % TABLE_SIZE;
		if (strncmp(hash_table[try]->idU, idR, TABLE_SIZE) == 0){
			for(int o = 0;o;o++){
				if(p->idR[o] == NULL) p->idR[o] = repo_id;

			}
			return true;
		}
	}

	return false;
}

bool hash_table_member_insertR(Data_R * p, char * commit_R){
	p->commit_R = 0;
	if (p == NULL) return false;
	int index = hash(p->idR);
	for(int i=0;i < TABLE_SIZE;i++){
		int try = (i + index) % TABLE_SIZE;
		if (strncmp(hash_tableR[try]->idR, commit_R, TABLE_SIZE) == 0){
			 p->commit_R++;
			 return true;
		}
		
	}

	return false;
}

// id a = {.idU = X, .idR[0] = Y};

// find in table by their name
Data_2 *hash_table_lookup (char * idU){
	int index = hash(idU);
	for (int i=0;i < TABLE_SIZE;i++) {
		int try = (index + i) % TABLE_SIZE;

		if (hash_table[try] == NULL){
			return false; // not here
		}

		if (hash_table[try] == DELETED_NODE) continue;

		if (hash_table[try] != NULL &&
			strncmp(hash_table[try]->idU, idU, TABLE_SIZE)==0){
			return hash_table[try];
		}
		
	}

	return NULL;

}

// find in table by their name
Data_R *hash_table_lookupR (char * idR){
	int index = hash(idR);
	for (int i=0;i < TABLE_SIZE;i++) {
		int try = (index + i) % TABLE_SIZE;

		if (hash_tableR[try] == NULL){
			return NULL; // not here
		}

		if (hash_tableR[try] == DELETEDR_NODE) continue;

		if (hash_tableR[try] != NULL &&
			strncmp(hash_tableR[try]->idR, idR, TABLE_SIZE)==0){
			return hash_tableR[try];
		}
		
	}

	return NULL;

}


// find in table by different from idU
int hash_table_member_lookupR(char * idR){
	int r = 0;
	for (int i=0;i < TABLE_SIZE;i++) {

		if (hash_tableR[i] == NULL){
			r = 0; // not here
		}

		if (hash_tableR[i] == DELETEDR_NODE) continue;

		if (hash_tableR[i] != NULL &&
		   (hash_tableR[i]->commit_R != 0)){
				r = 1;
		}
		
	}

	return r;

}



Data_2 *hash_table_delete (char * idU){
	int index = hash(idU);
	for (int i=0;i < TABLE_SIZE;i++) {
		int try = (index + i) % TABLE_SIZE;
		if (hash_table[try] == NULL){
			return NULL;
		}
		if (hash_table[try] == DELETED_NODE) continue;
		if (hash_table[try] != NULL &&
			strncmp(hash_table[try]->idU, idU, TABLE_SIZE)==0){
			Data_2 * tmp = hash_table[try];
			hash_table[try] = DELETED_NODE;
			return tmp;
		}
		
	}

	return NULL;

}

Data_R *hash_table_deleteR (char * idR){
	int index = hash(idR);
	for (int i=0;i < TABLE_SIZE;i++) {
		int try = (index + i) % TABLE_SIZE;
		if (hash_tableR[try] == NULL){
			return NULL;
		}
		if (hash_tableR[try] == DELETEDR_NODE) continue;
		if (hash_tableR[try] != NULL &&
			strncmp(hash_tableR[try]->idR, idR, TABLE_SIZE)==0){
			Data_R * tmp = hash_tableR[try];
			hash_tableR[try] = DELETEDR_NODE;
			return tmp;
		}
		
	}

	return NULL;

}


