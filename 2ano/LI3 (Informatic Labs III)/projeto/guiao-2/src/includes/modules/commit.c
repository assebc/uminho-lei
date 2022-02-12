#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../parser.h"
#include "commit.h"
#include "../define.h"

struct commit {
	char *repo_id;
	char *author_id;
	char *committer_id;
	char *commit_at;
	char *message;
};

COMMIT create_commit() {
	COMMIT c = malloc(sizeof *c);
	return c;
}

void delete_commit(void* c) {
	COMMIT cc = (COMMIT)c;
	free(cc->repo_id);
	free(cc->author_id);
	free(cc->committer_id);
	free(cc->commit_at);
	free(cc->message);
	free(cc);
}

void set_commit_repo_id(COMMIT c, char *s) {
	c->repo_id = strdup(s);
}

void set_commit_author_id(COMMIT c, char *s) {
	c->author_id = strdup(s);
}

void set_commit_committer_id(COMMIT c, char *s) {
	c->committer_id = strdup(s);
}

void set_commit_at(COMMIT c, char *s) {
	c->commit_at = strdup(s);
}

void set_commit_message(COMMIT c, char *s) {
	c->message = strdup(s);
}

void set_commit(COMMIT c, char *line) {
	char *p = NULL, *temp_line = strdup(line), *os;
	os = temp_line;
	int i = 0;
	while ((p = strsep(&temp_line, ";")) != NULL) {
		switch (i) {
			case 0:
				set_commit_repo_id(c, p);
				break;
			case 1:
				set_commit_author_id(c, p);
				break;
			case 2:
				set_commit_committer_id(c, p);
				break;
			case 3:
				set_commit_at(c, p);
				break;
			case 4:
				set_commit_message(c, p);
				break;
		}
		i++;
	}
	free(os);
}

int is_valid_commit(COMMIT c) {
	if (!(is_valid_number(c->repo_id) && is_valid_number(c->author_id) && is_valid_number(c->committer_id)))
		return 0;
	if (!(is_valid_date(c->commit_at)))
		return 0;
	if (c->repo_id[0] == '\0' || c->author_id[0] == '\0' || c->committer_id[0] == '\0' || c->commit_at[0] == '\0')
		return 0;
	return 1;
}

char* get_commit_committer_id(COMMIT c) {
	return strdup(c->committer_id);
}

char* get_commit_author_id(COMMIT c) {
	return strdup(c->author_id);
}

void print_commit(COMMIT c) {
	printf("COMMIT-> REPO_ID: %s AUTHOR_ID: %s COMMITTER_ID: %s COMMIT_AT: %s MESSAGE: %s\n", c->repo_id, c->author_id, c->committer_id, c->commit_at, c->message);
}