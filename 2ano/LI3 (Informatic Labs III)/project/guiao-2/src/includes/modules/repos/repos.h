/**
 * @file repos.h
 * @brief Header quer inicializa as funções do ficheiro repos.c
 */

#ifndef REPOS_H
#define REPOS_H

#include "repo.h"
#include "../../hashtable/hashtable.h"

/** Definição dos catálogos dos repos */
typedef struct repos *REPOS;

REPOS create_repos();
void set_repos();
void delete_repos();
void insert_repo(REPOS rs, char* key, REPO r);
REPO get_repo(REPOS rs, char* key);
REPO get_repo_no_mem_cpy(REPOS rs, char* key);
ht* get_repos_table(REPOS rs);
#endif