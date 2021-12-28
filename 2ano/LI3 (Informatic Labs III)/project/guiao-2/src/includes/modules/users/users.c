/**
 * @file users.c
 * @brief Ficheiro que contém as funções para a gestão dos catálogos dos users
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../parser.h"
#include "../../define.h"
#include "user.h"
#include "users.h"
#include "../../hashtable/hashtable.h"

/** 
 * Definição dos catálogos dos users
 * 
 * Contém uma hashtable
 * 
 */
struct users {
    ht *users;
};

/**
 * @brief Função create_users
 *
 * Função que aloca na memoria o espaco necessario para um catalogo de users
 * 
 * @returns catalogo de users
 */
USERS create_users() {
    USERS us = malloc(sizeof(*us));
    if (us == NULL) {
		printf("Erro ao criar users\n");
		return NULL;
    }
    ht *ht = ht_create(TABLE_SIZE);
    us->users = ht;
    return us;
}

/**
 * @brief Função delete_users
 *
 * Função que liberta da memoria o espaco alocado por uma hashtable de users
 * 
 */
void delete_users(USERS us) {
    ht_destroy(us->users, delete_user);
    free(us);        
}

/**
 * @brief Função insert_user
 *
 * Função que insere um user no seu catálogo
 * 
 */
void insert_user(USERS us, char* key, USER u){
	ht_insert(us->users, key, u);
}

/**
 * @brief Função get_user
 *
 * Função que devolve uma nova instancia de um user dentro do catalogo users
 * 
 * @returns catálogo de um user
 */
USER get_user(USERS us, char* key) {
   return ht_get(us->users, key, create_user, copy_user); 
}

/**
 * @brief Função get_user_no_mem_cpy
 *
 * Função que devolve um user dentro do catalogo dos users
 * 
 * @returns catálogo de um user
 */
USER get_user_no_mem_cpy(USERS us, char* key) {
   return ht_get_no_mem_cpy(us->users, key); 
}