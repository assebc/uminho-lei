/**
 * @file repo.h
 * @brief Header quer inicializa as funções do ficheiro repo.c
 */

#ifndef REPO_H
#define REPO_H

#define REPO_COLUMNS 14

/** Definição dos módulos do repositório */
typedef struct repo *REPO;

void* create_repo();
void delete_repo(void* r);

void set_repo_id(REPO r, char *s);
void set_repo_owner_id(REPO r, char *s);
void set_repo_full_name(REPO r, char *s);
void set_repo_license(REPO r, char *s);
void set_repo_has_wiki(REPO r, char *s);
void set_repo_description(REPO r, char *s);
void set_repo_language(REPO r, char *s);
void set_repo_default_branch(REPO r, char *s);
void set_repo_created_at(REPO r, char *s);
void set_repo_updated_at(REPO r, char *s);
void set_repo_forks_count(REPO r, char *s);
void set_repo_open_issues(REPO r, char *s);
void set_repo_stargazers_count(REPO r, char *s);
void set_repo_size(REPO r, char *s);

char* get_repo_id(void* r);
char* get_repo_language(void* r);
char* get_repo_description(void* r);
char* get_repo_owner_id(void* r);

void set_repo(void *r, char *line);

int is_valid_repo(REPO r);

void copy_repo(void* dst, void* src);
#endif
