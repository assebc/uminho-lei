#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../parser.h"
#include "../define.h"
#include "user.h"

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

void* create_user() {
	USER u = malloc(sizeof *u);
	return u;
}

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

void set_user_id(USER u, char *s) {
	u->id = strdup(s);
}
void set_user_login(USER u, char *s) {
	u->login = strdup(s);
}
void set_user_type(USER u, char *s) {
	u->type = strdup(s);
}
void set_user_created_at(USER u, char *s) {
	u->created_at = strdup(s);
}
void set_user_followers(USER u, char *s) {
	u->followers = strdup(s);

}void set_user_follower_list(USER u, char *s) {
	u->follower_list = strdup(s);
}
void set_user_following(USER u, char *s) {
	u->following = strdup(s);
}
void set_user_following_list(USER u, char *s) {
	u->following_list = strdup(s);
}
void set_user_public_gists(USER u, char *s) {
	u->public_gists = strdup(s);
}
void set_user_public_repos(USER u,char *s) {
	u->public_repos = strdup(s);
}

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

char *get_user_id(void* u) {
	USER uc = (USER) u;
	return strdup(uc->id);
}

char *get_user_login(void* u) {
	USER uc = (USER) u;
	return strdup(uc->login);
}

char *get_user_type(void* u) {
	USER uc = (USER) u;
	return strdup(uc->type);
}

void print_user(USER u) {
	printf("USER-> ID:%s LOGIN:%s CREATED_AT:%s FOLLOWERS:%s FOLLOWER_LIST:%s FOLLOWING:%s FOLLOWING_LIST:%s PUBLIC_GISTS:%s PUBLIC_REPOS:%s\n", u->id, u->login, u->created_at, u->followers, u->follower_list, u->following, u->following_list, u->public_gists, u->public_repos);
}