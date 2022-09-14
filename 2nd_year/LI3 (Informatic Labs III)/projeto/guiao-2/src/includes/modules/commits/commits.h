/**
 * @file commits.h
 * @brief Header quer inicializa as funções do ficheiro commits.c
 */

#ifndef COMMITS_H
#define COMMITS_H

#include "commit.h"
#include "../../hashtable/hashtable.h"

/** Definição dos catálogos dos commits */
typedef struct commits *COMMITS;

COMMITS create_commits();
void set_commits();
void delete_commits();
void insert_commit(COMMITS cs, char* key, COMMIT c);
int count_commits(COMMITS cs);
ht* get_commits_table(COMMITS cs);

#endif