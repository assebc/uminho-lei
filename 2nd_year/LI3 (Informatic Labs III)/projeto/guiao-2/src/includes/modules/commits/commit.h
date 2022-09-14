/**
 * @file commit.h
 * @brief Header quer inicializa as funções do ficheiro commit.c
 */

#ifndef COMMIT_H
#define COMMIT_H

#define COMMIT_COLUMNS 5

/** Definição dos módulos do commit */
typedef struct commit *COMMIT;

void* create_commit();
void delete_commit(void* u);

void set_commit_repo_id(COMMIT c, char *s);
void set_commit_author_id(COMMIT c, char *s);
void set_commit_committer_id(COMMIT c, char *s);
void set_commit_commit_at(COMMIT c, char *s);
void set_commit_message(COMMIT c, char *s);

char* get_commit_repo_id(void* c);
char* get_commit_committer_id(void* c);
char* get_commit_author_id(void* c);
char* get_commit_commit_at(void* c);
char* get_commit_message(void* c);

void set_commit(void* c, char *line);

int is_valid_commit(COMMIT c);

void print_commit(void* c);
void print_commit_committer_id(void* c);

#endif