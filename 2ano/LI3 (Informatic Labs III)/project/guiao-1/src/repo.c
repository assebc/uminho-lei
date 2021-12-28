/**
 * @file repo.c
 * @brief Ficheiro que contém as funções para criação dos módulos dos repos, usando o encapsulamento
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "eval.h"
#include "parser.h"
#include "define.h"
#include "hashtable.h"

/** 
 * Definição dos módulos de repo
 * 
 * Contém todos os elementos de um repo, como char*
 * 
 */
struct repo {
	char *id;
	char *owner_id;
	char *full_name;
	char *license;
	char *has_wiki;
	char *description;
	char *language;
	char *default_branch;
	char *created_at;
	char *updated_at;
	char *forks_count;
	char *open_issues;
	char *stargazers_count;
	char *size;
};

typedef struct repo *REPO;

/**
 * @brief Função create_repo
 *
 * Função que aloca na memorira o espaco necessario para um repo
 * 
 * @returns repo
 */
void* create_repo() {
	REPO r = malloc(sizeof *r);
	if (r == NULL) {
		printf("Erro ao criar repo\n");
		return NULL;
	}
	return r;
}

/**
 * @brief Função delete_repo
 *
 * Função que liberta da memoria o espaco alocado por um repo
 * 
 */
void delete_repo(void* r) {
	REPO rc = (REPO)r;
	free(rc->id);
	free(rc->owner_id);
	free(rc->full_name);
	free(rc->license);
	free(rc->has_wiki);
	free(rc->description);
	free(rc->language);
	free(rc->default_branch);
	free(rc->created_at);
	free(rc->updated_at);
	free(rc->forks_count);
	free(rc->open_issues);
	free(rc->stargazers_count);
	free(rc->size);
	free(rc);
}

/**
 * @brief Função set_repo_id
 *
 * Função que define repo_id
 * 
 */
void set_repo_id(REPO r, char *s) {
	r->id = strdup(s);
}

/**
 * @brief Função set_repo_owner_id
 *
 * Função que define repo_owner_id
 * 
 */
void set_repo_owner_id(REPO r, char *s) {
	r->owner_id = strdup(s);
}

/**
 * @brief Função set_repo_full_name
 *
 * Função que define repo_full_name
 * 
 */
void set_repo_full_name(REPO r, char *s) {
	r->full_name = strdup(s);
}

/**
 * @brief Função set_repo_license
 *
 * Função que define repo_license
 * 
 */
void set_repo_license(REPO r, char *s) {
	r->license = strdup(s);
}

/**
 * @brief Função set_repo_has_wiki
 *
 * Função que define repo_has_wiki
 * 
 */
void set_repo_has_wiki(REPO r, char *s) {
	r->has_wiki = strdup(s);
}

/**
 * @brief Função set_repo_description
 *
 * Função que define repo_description
 * 
 */
void set_repo_description(REPO r, char *s) {
	r->description = strdup(s);
}

/**
 * @brief Função set_repo_language
 *
 * Função que define repo_language
 * 
 */
void set_repo_language(REPO r, char *s) {
	r->language = strdup(s);
}

/**
 * @brief Função set_repo_default_branch
 *
 * Função que define repo_default_branch
 * 
 */
void set_repo_default_branch(REPO r, char *s) {
	r->default_branch = strdup(s);
}

/**
 * @brief Função set_repo_created_at
 *
 * Função que define repo_created_at
 * 
 */
void set_repo_created_at(REPO r, char *s) {
	r->created_at = strdup(s);
}

/**
 * @brief Função set_repo_updated_at
 *
 * Função que define repo_updated_at
 * 
 */
void set_repo_updated_at(REPO r, char *s) {
	r->updated_at = strdup(s);
}

/**
 * @brief Função set_repo_forks_count
 *
 * Função que define repo_forks_count
 * 
 */
void set_repo_forks_count(REPO r, char *s) {
	 r->forks_count = strdup(s);
}

/**
 * @brief Função set_repo_open_issues
 *
 * Função que define repo_open_issues
 * 
 */
void set_repo_open_issues(REPO r, char *s) {
	r->open_issues = strdup(s);
}

/**
 * @brief Função set_repo_stargazers_count
 *
 * Função que define repo_stargazers_count
 * 
 */
void set_repo_stargazers_count(REPO r, char *s) {
	r->stargazers_count = strdup(s);
}

/**
 * @brief Função set_repo_size
 *
 * Função que define repo_size
 * 
 */
void set_repo_size(REPO r, char *s) {
	r->size = strdup(s);
}

/**
 * @brief Função set_repo
 *
 * Função que define repo, utilizando as funções anterioes
 * 
 */
void set_repo(void* r, char *line) {
	char *p = NULL, *temp_line = strdup(line), *os;
	REPO rc = (REPO) r;
	os = temp_line;
	int i = 0;
	while ((p = strsep(&temp_line, ";")) != NULL) {
		switch(i) {
			case 0:
				set_repo_id(rc, p);
				break;
			case 1:
				set_repo_owner_id(rc, p);
				break;
			case 2:
				set_repo_full_name(rc, p);
				break;
			case 3:
				set_repo_license(rc, p);
				break;
			case 4:
				set_repo_has_wiki(rc, p);
				break;
			case 5:
				set_repo_description(rc, p);
				break;
			case 6:
				set_repo_language(rc, p);
				break;
			case 7:
				set_repo_default_branch(rc, p);
				break;
			case 8:
				set_repo_created_at(rc, p);
				break;
			case 9:
				set_repo_updated_at(rc, p);
				break;
			case 10:
				set_repo_forks_count(rc, p);
				break;
			case 11:
				set_repo_open_issues(rc, p);
				break;
			case 12:
				set_repo_stargazers_count(rc, p);
				break;
			case 13:
				set_repo_size(rc, p);
				break;
		}
		i++;
	}	
	free(os);
}

/**
 * @brief Função is_valid_repo
 *
 * Função que verifica se um repo é válida
 * 
 * @returns bool
 */
int is_valid_repo(REPO r) {
	if (!(is_valid_number(r->forks_count) && is_valid_number(r->open_issues) && is_valid_number(r->stargazers_count) && is_valid_number(r->owner_id) && is_valid_number(r->id) && is_valid_number(r->size)))
		return 0;
	if (!(is_valid_date(r->created_at) && is_valid_date(r->updated_at)))
		return 0;
	if (!(is_valid_name(r->full_name)))
		return 0;
	if (!(is_valid_bool(r->has_wiki)))
		return 0;
	if ((r->license[0] == '\0' || r->language[0] == '\0' || r->default_branch[0] == '\0'))
		return 0;
	return 1;
}

/**
 * @brief Função get_repo_id
 *
 * Função que devolve uma copia do id de um repo
 * 
 * @returns id de um repo
 */
char* get_repo_id(void* r) {
	REPO rc = (REPO) r;
	return strdup(rc->id);
}

/**
 * @brief Função get_repo_language
 *
 * Função que devolve uma copia do language de um repo 
 * 
 * @returns language de um repo
 */
char* get_repo_language(void* r) {
	REPO rc = (REPO) r;
	return strdup(rc->language);
}

/**
 * @brief Função get_repo_description
 *
 * Função que devolve uma copia description de um repo
 * 
 * @returns description de um repo
 */
char* get_repo_description(void* r) {
	REPO rc = (REPO) r;
	return strdup(rc->description);
}

/**
 * @brief Função get_repo_owner_id
 *
 * Função que devolve uma copia owner_id de um repo
 * 
 * @returns owner_id de um repo
 */
char* get_repo_owner_id(void* r) {
	REPO rc = (REPO) r;
	return strdup(rc->owner_id);
}

/**
 * @brief Função copy_repo
 *
 * Função que copia um repo para outro
 * 
 */
void copy_repo(void* dst, void* src) {
	REPO dstc = (REPO) dst;
	REPO srcc = (REPO) src;
	dstc->id = strdup(srcc->id);
	dstc->owner_id = strdup(srcc->owner_id);
	dstc->full_name = strdup(srcc->full_name);
	dstc->license = strdup(srcc->license);
	dstc->has_wiki = strdup(srcc->has_wiki);
	dstc->description = strdup(srcc->description);
	dstc->language = strdup(srcc->language);
	dstc->default_branch = strdup(srcc->default_branch);
	dstc->created_at = strdup(srcc->created_at);
	dstc->updated_at = strdup(srcc->updated_at);
	dstc->forks_count = strdup(srcc->forks_count);
	dstc->open_issues = strdup(srcc->open_issues);
	dstc->stargazers_count = strdup(srcc->stargazers_count);
	dstc->size = strdup(srcc->size);
}