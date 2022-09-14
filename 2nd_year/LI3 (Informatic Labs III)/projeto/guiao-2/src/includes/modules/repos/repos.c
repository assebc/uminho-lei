/**
 * @file repos.c
 * @brief Ficheiro que contém as funções para a gestão dos catálogos dos repos
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../parser.h"
#include "../../define.h"
#include "repo.h"
#include "repos.h"
#include "../../hashtable/hashtable.h"

/** 
 * Definição dos catálogos dos repos
 * 
 * Contém uma hashtable
 * 
 */
struct repos {
    ht *repos;
};

/**
 * @brief Função create_repos
 *
 * Função que aloca na memoria o espaco necessario para um catalogo de repositorios
 * 
 * @returns catálogo de repos
 */
REPOS create_repos() {
    REPOS rs = malloc(sizeof(*rs));
    if (rs == NULL) {
		printf("Erro ao criar repos\n");
		return NULL;
    }
    ht *ht = ht_create(TABLE_SIZE);
    rs->repos = ht;
    return rs;
}

/**
 * @brief Função delete_repos
 *
 * Função que liberta da memoria espaco alocado por uma hashtable de users
 * 
 */
void delete_repos(REPOS rs) {
    ht_destroy(rs->repos, delete_repo);
    free(rs);        
}

/**
 * @brief Função insert_repo
 *
 * Função que insere um repositório no seu catálogo
 * 
 */
void insert_repo(REPOS rs, char* key, REPO r){
	ht_insert(rs->repos, key, r);
}

/**
 * @brief Função get_repo
 *
 * Função que devolve uma nova instancia de um repositorio dentro do catalgo dos repositorios
 * 
 * @returns repo
 */
REPO get_repo(REPOS rs, char* key) {
   return ht_get(rs->repos, key, create_repo, copy_repo); 
}

/**
 * @brief Função get_repo_no_mem_cpy
 *
 * Função que devolve um repositorio dentro do catalogo dos repositorios
 * 
 * @returns repo
 */
REPO get_repo_no_mem_cpy(REPOS rs, char* key) {
   return ht_get_no_mem_cpy(rs->repos, key); 
}

/**
 * @brief Função get_repos_table
 *
 * Função que obtem a hashtable com os repositorios
 * 
 * @returns hashtable de repositorios
 */
ht* get_repos_table(REPOS rs) {
    return rs->repos;
}