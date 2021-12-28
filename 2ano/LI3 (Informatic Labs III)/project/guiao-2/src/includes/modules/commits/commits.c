/**
 * @file commits.c
 * @brief Ficheiro que contém as funções para a gestão dos catálogos dos commits
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../parser.h"
#include "../../define.h"
#include "commit.h"
#include "commits.h"
#include "../../hashtable/hashtable.h"

/** 
 * Definição dos catálogos dos commits
 * 
 * Contém uma hashtable
 * 
 */
struct commits {
    ht *commits;
};

/**
 * @brief Função create_commits
 *
 * Função que cria catálogo de commits
 * 
 * @returns catálogo
 */
COMMITS create_commits() {
    COMMITS cs = malloc(sizeof(*cs));
    if (cs == NULL) {
		printf("Erro ao criar commits\n");
		return NULL;
    }
    ht *ht = ht_create(TABLE_SIZE);
    cs->commits = ht;
    return cs;
}

/**
 * @brief Função delete_commits
 *
 * Função que remove um catálogo de commits
 * 
 */
void delete_commits(COMMITS cs) {
    ht_destroy(cs->commits, delete_commit);
    free(cs);        
}

/**
 * @brief Função insert_commit
 *
 * Função que insere um commit no seu catálogo
 * 
 */
void insert_commit(COMMITS cs, char* key, COMMIT c){
	ht_insert_2(cs->commits, key, c);
}

/**
 * @brief Função count_commits
 *
 * Função que conta o número de commits (gerais)
 * 
 * @returns numero de commits
 */
int count_commits(COMMITS cs) {
	int k = ht_count(cs->commits);
	return k;
}

/**
 * @brief Função get_commits_table
 *
 * Função que obtem a hashtable com os catálogos
 * 
 * @returns hashtable de catálogos
 */
ht* get_commits_table(COMMITS cs) {
    return cs->commits;
}