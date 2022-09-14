#ifndef COMMIT_H
#define COMMIT_H

#define COMMIT_COLUMNS 5

typedef struct commit *COMMIT;

COMMIT create_commit();
void delete_commit(void* u);

void set_commit_repo_id(COMMIT c, char *s);
void set_commit_author_id(COMMIT c, char *s);
void set_commit_committer_id(COMMIT c, char *s);
void set_commit_commit_at(COMMIT c, char *s);
void set_commit_message(COMMIT c, char *s);

char* get_commit_committer_id(COMMIT c);
char* get_commit_author_id(COMMIT c);

void set_commit(COMMIT c, char *line);

int is_valid_commit(COMMIT c);

void print_commit(COMMIT c);

#endif
