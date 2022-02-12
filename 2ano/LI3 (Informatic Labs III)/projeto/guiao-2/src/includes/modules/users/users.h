/**
 * @file users.h
 * @brief Header quer inicializa as funções do ficheiro users.c
 */

#ifndef USERS_H
#define USERS_H

#include "user.h"

/** Definição dos catálogos dos users */
typedef struct users *USERS;

USERS create_users();
void set_users();
void delete_users();
void insert_user(USERS us, char* key, USER u);
USER get_user(USERS us, char* key);
USER get_user_no_mem_cpy(USERS us, char* key);
#endif