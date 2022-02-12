/**
 * @file commit.c
 * @brief Ficheiro que contém as funções para criação dos módulos dos commits, usando o encapsulamento
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../parser.h"
#include "commit.h"
#include "../../define.h"

/** 
 * Definição do modulo de commit
 * 
 * Contém todos os elementos de um commit, como char*
 * 
 */
struct commit {
	char *repo_id;
	char *author_id;
	char *committer_id;
	char *commit_at;
	char *message;
};

/**
 * @brief Função create_commit
 *
 * Função que aloca na memoria o espaco necessario para uma commit
 * 
 * @returns commit 
 */
void* create_commit() {
	COMMIT c = malloc(sizeof *c);
	if (c == NULL)
		printf("Erro ao criar commit\n");
	return c;
}

/**
 * @brief Função delete_commit
 *
 * Função que liberta da memoria o espaco alocado por uma commit
 * 
 */
void delete_commit(void* c) {
	COMMIT cc = (COMMIT)c;
	free(cc->repo_id);
	free(cc->author_id);
	free(cc->committer_id);
	free(cc->commit_at);
	free(cc->message);
	free(cc);
}

/**
 * @brief Função set_commit_repo_id
 *
 * Função que define commit_repo_id
 * 
 */
void set_commit_repo_id(COMMIT c, char *s) {
	c->repo_id = strdup(s);
}

/**
 * @brief Função set_commit_author_id
 *
 * Função que define commit_author_id
 * 
 */
void set_commit_author_id(COMMIT c, char *s) {
	c->author_id = strdup(s);
}

/**
 * @brief Função set_commit_committer_id
 *
 * Função que define commit_committer_id
 * 
 */
void set_commit_committer_id(COMMIT c, char *s) {
	c->committer_id = strdup(s);
}

/**
 * @brief Função set_commit_at
 *
 * Função que define commit_at
 * 
 */
void set_commit_at(COMMIT c, char *s) {
	c->commit_at = strdup(s);
}

/**
 * @brief Função set_commit_message
 *
 * Função que define commit_message
 * 
 */
void set_commit_message(COMMIT c, char *s) {
	c->message = strdup(s);
}

/**
 * @brief Função set_commit
 *
 * Função que define commit, utilizando as funções anterioes
 * 
 */
void set_commit(void* c, char *line) {
	char *p = NULL, *temp_line = strdup(line), *os;
	COMMIT cc = (COMMIT) c;
	os = temp_line;
	int i = 0;
	while ((p = strsep(&temp_line, ";")) != NULL) {
		switch (i) {
			case 0:
				set_commit_repo_id(cc, p);
				break;
			case 1:
				set_commit_author_id(cc, p);
				break;
			case 2:
				set_commit_committer_id(cc, p);
				break;
			case 3:
				set_commit_at(cc, p);
				break;
			case 4:
				set_commit_message(cc, p);
				break;
		}
		i++;
	}
	free(os);
}

/**
 * @brief Função is_valid_commit
 *
 * Função que verifica se uma commit é válida
 * 
 * @returns bool
 */
int is_valid_commit(COMMIT c) {
	if (!(is_valid_number(c->repo_id) && is_valid_number(c->author_id) && is_valid_number(c->committer_id)))
		return 0;
	if (!(is_valid_date(c->commit_at)))
		return 0;
	if (c->repo_id[0] == '\0' || c->author_id[0] == '\0' || c->committer_id[0] == '\0' || c->commit_at[0] == '\0')
		return 0;
	return 1;
}

/**
 * @brief Função get_commit_repo_id
 *
 * Função que devolve uma copia do repo_id de uma commit
 * 
 * @returns repo_id
 */
char* get_commit_repo_id(void* c) {
	COMMIT cc = (COMMIT) c;
	return strdup(cc->repo_id);
}

/**
 * @brief Função get_commit_committer_id
 *
 * Função que devolve uma copia do committer_id de uma commit
 * 
 * @returns committer_id
 */
char* get_commit_committer_id(void* c) {
	COMMIT cc = (COMMIT) c;
	return strdup(cc->committer_id);
}

/**
 * @brief Função get_commit_author_id
 *
 * Função que devolve uma copia do author_id de uma commit
 * 
 * @returns author_id
 */
char* get_commit_author_id(void* c) {
	COMMIT cc = (COMMIT) c;
	return strdup(cc->author_id);
}

/**
 * @brief Função get_commit_at
 *
 * Função que devolve uma copia do commit_at de uma commit
 * 
 * @returns commit_at
 */
char* get_commit_commit_at(void* c) {
	COMMIT cc = (COMMIT) c;
	return strdup(cc->commit_at);
}

/**
 * @brief Função get_commit_message
 *
 * Função que devolve uma copia do message de uma commit 
 * 
 * @returns message
 */
char* get_commit_message(void* c) {
	COMMIT cc = (COMMIT) c;
	return strdup(cc->message);
}

/**
 * @brief Função print_commit
 *
 * Função que imprime um módulo de um commit
 * Função para testes
 * 
 */
void print_commit(void* c) {
	COMMIT cc = (COMMIT) c;
	printf("COMMIT-> REPO_ID: %s AUTHOR_ID: %s COMMITTER_ID: %s COMMIT_AT: %s MESSAGE: %s\n", cc->repo_id, cc->author_id, cc->committer_id, cc->commit_at, cc->message);
}

/**
 * @brief Função print_commit_committer_id
 *
 * Função que imprime um commit_committer_id
 * Função para testes
 * 
 */
void print_commit_committer_id(void* c) {
	COMMIT cc = (COMMIT) c;
	printf("COMMITER_ID: %s\n", cc->committer_id);
}
