#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../parser.h"
#include "../define.h"
#include "repo.h"

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

REPO create_repo() {
	REPO r = malloc(sizeof *r);
	return r;
}

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

void set_repo_id(REPO r, char *s) {
	r->id = strdup(s);
}
void set_repo_owner_id(REPO r, char *s) {
	r->owner_id = strdup(s);
}
void set_repo_full_name(REPO r, char *s) {
	r->full_name = strdup(s);
}
void set_repo_license(REPO r, char *s) {
	r->license = strdup(s);
}
void set_repo_has_wiki(REPO r, char *s) {
	r->has_wiki = strdup(s);
}
void set_repo_description(REPO r, char *s) {
	r->description = strdup(s);
}
void set_repo_language(REPO r, char *s) {
	r->language = strdup(s);
}
void set_repo_default_branch(REPO r, char *s) {
	r->default_branch = strdup(s);
}
void set_repo_created_at(REPO r, char *s) {
	r->created_at = strdup(s);
}
void set_repo_updated_at(REPO r, char *s) {
	r->updated_at = strdup(s);
}
void set_repo_forks_count(REPO r, char *s) {
	 r->forks_count = strdup(s);
}
void set_repo_open_issues(REPO r, char *s) {
	r->open_issues = strdup(s);
}
void set_repo_stargazers_count(REPO r, char *s) {
	r->stargazers_count = strdup(s);
}
void set_repo_size(REPO r, char *s) {
	r->size = strdup(s);
}

void set_repo(REPO r, char *line) {
	char *p = NULL, *temp_line = strdup(line), *os;
	os = temp_line;
	int i = 0;
	while ((p = strsep(&temp_line, ";")) != NULL) {
		switch(i) {
			case 0:
				set_repo_id(r, p);
				break;
			case 1:
				set_repo_owner_id(r, p);
				break;
			case 2:
				set_repo_full_name(r, p);
				break;
			case 3:
				set_repo_license(r, p);
				break;
			case 4:
				set_repo_has_wiki(r, p);
				break;
			case 5:
				set_repo_description(r, p);
				break;
			case 6:
				set_repo_language(r, p);
				break;
			case 7:
				set_repo_default_branch(r, p);
				break;
			case 8:
				set_repo_created_at(r, p);
				break;
			case 9:
				set_repo_updated_at(r, p);
				break;
			case 10:
				set_repo_forks_count(r, p);
				break;
			case 11:
				set_repo_open_issues(r, p);
				break;
			case 12:
				set_repo_stargazers_count(r, p);
				break;
			case 13:
				set_repo_size(r, p);
				break;
		}
		i++;
	}	
	free(os);
}

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

char* get_repo_id(REPO r) {
	return strdup(r->id);
}