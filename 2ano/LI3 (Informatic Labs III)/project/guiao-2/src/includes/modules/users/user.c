/**
 * @file user.c
 * @brief Ficheiro que contém as funções para criação dos módulos dos users, usando o encapsulamento
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../parser.h"
#include "../../define.h"
#include "user.h"

/** 
 * Definição dos módulos de user
 * 
 * Contém todos os elementos de um user, como char*
 * 
 */
struct user {
	char *id;
	char *login;	
	char *type;
	char *created_at;
	char *followers;
	char *follower_list;
	char *following;
	char *following_list;
	char *public_gists;
	char *public_repos;
};

/**
 * @brief Função create_user
 *
 * Função que aloca na memoria o espaco necessario para um user
 * 
 * @returns user 
 */
void* create_user() {
	USER u = malloc(sizeof *u);
	if (u == NULL)
		printf("Erro ao criar user\n");
	return u;
}

/**
 * @brief Função delete_user
 *
 * Função que liberta da memoria o espaco ocupado por um user
 * 
 */
void delete_user(void *u) {
	USER uc = (USER) u;
	free(uc->id);
	free(uc->login);
	free(uc->type);
	free(uc->created_at);
	free(uc->followers);
	free(uc->follower_list);
	free(uc->following);
	free(uc->following_list);
	free(uc->public_gists);
	free(uc->public_repos);
	free(uc);
}

/**
 * @brief Função set_user_id
 *
 * Função que define o id de um user
 * 
 */
void set_user_id(USER u, char *s) {
	u->id = strdup(s);
}

/**
 * @brief Função set_user_login
 *
 * Função que define o login de um user
 * 
 */
void set_user_login(USER u, char *s) {
	u->login = strdup(s);
}

/**
 * @brief Função set_user_type
 *
 * Função que define o type de um user
 * 
 */
void set_user_type(USER u, char *s) {
	u->type = strdup(s);
}

/**
 * @brief Função set_user_created_at
 *
 * Função que define o created_at de um user
 * 
 */
void set_user_created_at(USER u, char *s) {
	u->created_at = strdup(s);
}

/**
 * @brief Função set_user_followers
 *
 * Função que define os followers de um user
 * 
 */
void set_user_followers(USER u, char *s) {
	u->followers = strdup(s);

}

/**
 * @brief Função set_user_follower_list
 *
 * Função que define o follower_list de um user
 * 
 */
void set_user_follower_list(USER u, char *s) {
	u->follower_list = strdup(s);
}

/**
 * @brief Função set_user_following
 *
 * Função que define o following de um user
 * 
 */
void set_user_following(USER u, char *s) {
	u->following = strdup(s);
}

/**
 * @brief Função set_user_following_list
 *
 * Função que define o following_list de um user
 * 
 */
void set_user_following_list(USER u, char *s) {
	u->following_list = strdup(s);
}

/**
 * @brief Função set_user_public_gists
 *
 * Função que define o public_gists de um user
 * 
 */
void set_user_public_gists(USER u, char *s) {
	u->public_gists = strdup(s);
}

/**
 * @brief Função set_user_public_repos
 *
 * Função que define o public_repos de um user
 * 
 */
void set_user_public_repos(USER u,char *s) {
	u->public_repos = strdup(s);
}

/**
 * @brief Função set_user
 *
 * Função que define user, utilizando as funções anterioes
 * 
 */
void set_user(void* u, char *line) {
	char *p = NULL, *temp_line = strdup(line), *os;
	USER uc = (USER) u;
	os = temp_line;
	int i = 0;
	while ((p = strsep(&temp_line, ";")) != NULL) {
		switch (i) {
			case 0:
				set_user_id(uc, p);
				break;
			case 1:
				set_user_login(uc, p);
				break;
			case 2:
				set_user_type(uc, p);
				break;
			case 3:
				set_user_created_at(uc, p);
				break;
			case 4:
				set_user_followers(uc, p);
				break;
			case 5:
				set_user_follower_list(uc, p);
				break;
			case 6:
				set_user_following(uc, p);
				break;
			case 7:
				set_user_following_list(uc, p);
				break;
			case 8:
				set_user_public_gists(uc, p);
				break;
			case 9:
				set_user_public_repos(uc, p);
				break;
			}
		i++;
	}
	free(os);
}

/**
 * @brief Função is_valid_user
 *
 * Função que verifica se um user é válido
 * 
 * @returns bool
 */
int is_valid_user(USER u) {
	if (!(is_valid_number(u->id) && is_valid_number(u->public_repos) 
		&& is_valid_number(u->followers) && is_valid_number(u->following) 
		&& is_valid_number(u->public_gists)))
		return 0;
	if (!(is_valid_list(u->follower_list) && is_valid_list(u->following_list)))
		return 0;
	if (!(is_valid_date(u->created_at) && is_valid_type(u->type)))
		return 0;
	if (u->login[0] == '\0')
		return 0;
	if (atoi(u->followers) != elem_list(u->follower_list) || atoi(u->following) != elem_list(u->following_list))
		return 0;
	return 1;
}

/**
 * @brief Função get_user_id
 *
 * Função que devolve uma copia do id de um user
 * 
 * @returns id de um user
 */
char *get_user_id(void* u) {
	USER uc = (USER) u;
	return strdup(uc->id);
}

/**
 * @brief Função get_user_login
 *
 * Função que devolve uma copia do login de um user
 * 
 * @returns login de um user
 */
char *get_user_login(void* u) {
	USER uc = (USER) u;
	return strdup(uc->login);
}

/**
 * @brief Função get_user_type
 *
 * Função que devolve uma copia do type de um user
 * 
 * @returns type de um user
 */
char *get_user_type(void* u) {
	USER uc = (USER) u;
	return strdup(uc->type);
}

/**
 * @brief Função get_user_follower_list
 *
 * Função que devolve uma copia do follower_list de um user
 * 
 * @returns follower_list de um user
 */
char *get_user_follower_list(void* u) {
	USER uc = (USER) u;
	return strdup(uc->follower_list);
}

/**
 * @brief Função get_user_following_list
 *
 * Função que devolve uma copia do following_list de um user
 * 
 * @returns following_list de um user
 */
char *get_user_following_list(void* u) {
	USER uc = (USER) u;
	return strdup(uc->following_list);
}


/**
 * @brief Função print_user
 *
 * Função que imprime um módulo user
 * Função para testes
 * 
 */
void print_user(void* u) {
	USER uc = (USER) u;
	printf("USER-> ID:%s LOGIN:%s CREATED_AT:%s FOLLOWERS:%s FOLLOWER_LIST:%s FOLLOWING:%s FOLLOWING_LIST:%s PUBLIC_GISTS:%s PUBLIC_REPOS:%s\n", uc->id, uc->login, uc->created_at, uc->followers, uc->follower_list, uc->following, uc->following_list, uc->public_gists, uc->public_repos);
}

/**
 * @brief Função copy_user
 *
 * Função que copia o modulo user dst para src
 * Duplica um user
 * 
 */
void copy_user(void* dst, void* src) {
	USER dstc = (USER) dst;
	USER srcc = (USER) src;
	dstc->id = strdup(srcc->id);
	dstc->login = strdup(srcc->login);
	dstc->type = strdup(srcc->type);
	dstc->created_at = strdup(srcc->created_at);
	dstc->followers = strdup(srcc->followers);
	dstc->follower_list = strdup(srcc->follower_list);
	dstc->following = strdup(srcc->following);
	dstc->following_list = strdup(srcc->following_list);
	dstc->public_gists = strdup(srcc->public_gists);
	dstc->public_repos = strdup(srcc->public_repos);
}