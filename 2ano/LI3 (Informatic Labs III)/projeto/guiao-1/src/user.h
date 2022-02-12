/**
 * @file user.h
 * @brief Header quer inicializa as funções do ficheiro user.c
 */

#ifndef USER_H
#define USER_H

#define USER_COLUMNS 10

/** Definição dos módulos do user */
typedef struct user *USER;

void* create_user();
void delete_user(void* u);

void set_user_id(USER u, char *s);
void set_user_login(USER u, char *s);
void set_user_type(USER u, char *s);
void set_user_created_at(USER u, char *s);
void set_user_followers(USER u, char *s);
void set_user_follower_list(USER u, char *s);
void set_user_following(USER u, char *s);
void set_user_following_list(USER u, char *s);
void set_user_public_gists(USER u, char *s);
void set_user_public_repos(USER u, char *s);

char* get_user_id(void* u);
char* get_user_login(void* u);
char* get_user_type(void* u);
char* get_user_following_list(void* u);
char* get_user_follower_list(void* u);

void set_user(void* u, char *line);

int is_valid_user(USER u);

void print_user(void* u);

void copy_user(void* dst, void* src);
#endif
