/**
 * @file parsing.c
 * @brief Ficheiro que contém as funções para a criação dos catálogos
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "define.h"
#include "parsing.h"
#include "parser.h"
#include "modules/users/users.h"
#include "modules/repos/repos.h"
#include "modules/commits/commits.h"
#include "modules/users/user.h"
#include "modules/repos/repo.h"
#include "modules/commits/commit.h"
#include "hashtable/hashtable.h"

/**
 * @brief Função create_users_catalog
 *
 * Criação dos catálogos dos users
 * Recebe como parametros o endereco de inteiros bots, orgs e useres em que sao posteriormente
 * incrementados ao longo da criacao do catalgo o numero de bots, orgs e users existentes no catalogo
 * 
 * @returns catálogo dos users
 */
USERS create_users_catalog(int *bots, int *orgs, int *users) {

	USERS us = create_users();
	
	char line[LINE_BUFFER];

	FILE *f = fopen(USERS_FILEPATH, "r");

	fgets(line, LINE_BUFFER, f);
	
	while(fgets(line, LINE_BUFFER, f) != NULL) {
		remove_possible_new_line(line);

        USER u = create_user();
		set_user(u, line);

		/* QUERY 1 CONTAR OS TIPOS */
		char *user_type = get_user_type(u);
		if(strcmp(user_type, "Bot") == 0) (*bots)++;
		else if(strcmp(user_type, "Organization") == 0) (*orgs)++;
		else if(strcmp(user_type, "User") == 0) (*users)++;
		free(user_type);
		/*------ */

        char *key = get_user_id(u);
		
		insert_user(us, key, u);

		free(key);
	 }
	fclose(f);

	return us;
}

/**
 * @brief Função create_commits_catalog
 *
 * Criação dos catálogos dos commits
 * Recebe como parametros o catalogo dos users, o endereco de uma hashtable, onde e
 * posteriormente guardada nessa hashtable os colaboradores, e recebe tambem o endereco de um
 * inteiro n_commits onde e depois incrementado ao longo da criacao do catalogo de commits que conta
 * o numero de linhas do ficheiro (numero de commits)
 * 
 * @returns catálogo dos commits
 */
COMMITS create_commits_catalog(USERS us, ht *ht_repo_colabs, int *n_commits) {
	
	COMMITS cs = create_commits();

	char line[LINE_BUFFER];

	FILE *f = fopen(COMMITS_FILEPATH, "r");

	fgets(line, LINE_BUFFER, f);

	while(fgets(line, LINE_BUFFER, f) != NULL) {
		remove_possible_new_line(line);

        COMMIT c = create_commit();
		set_commit(c, line);

        char *key = get_commit_repo_id(c);

    	/* HT_REPO_COLABS init */

        char *author_id = get_commit_author_id(c);
        char *committer_id = get_commit_committer_id(c);

        USER u1 = get_user(us, author_id);
        USER u2 = get_user(us, committer_id);

        if (u1 != NULL) {
        	ht_insert_3(ht_repo_colabs, key, u1);
        } 
        if (u2 != NULL) { 
        	ht_insert_3(ht_repo_colabs, key, u2);	
		}

    	/* ------------------- */   	

		insert_commit(cs, key, c);

		free(key);
		
		(*n_commits)++;
	}
	fclose(f);

	return cs;
}

/**
 * @brief Função create_repos_catalog
 *
 * Criação dos catálogos dos repos
 * Recebe como parametro um endereco de um inteiro n_repos onde e
 * posteriormente incrementando ao longo da criacao do catalogo de repositorios
 * com conta o numero de linhas do ficheiro (numero de repositorios)
 * 
 * @returns catálogo dos repos
 */
REPOS create_repos_catalog(int *n_repos) {

	REPOS rs = create_repos();

	char line[LINE_BUFFER];

	FILE *f = fopen(REPOS_FILEPATH, "r");

	fgets(line, LINE_BUFFER, f);

	while(fgets(line, LINE_BUFFER, f) != NULL) {
		remove_possible_new_line(line);

        REPO r = create_repo();
		set_repo(r, line);

        char *key = get_repo_id(r);
		
		insert_repo(rs, key, r);

		free(key);

		(*n_repos)++;
	}
	fclose(f);

	return rs;
}

