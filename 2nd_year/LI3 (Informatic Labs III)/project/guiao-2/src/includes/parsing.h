/**
 * @file parsing.h
 * @brief Header que com as assinaturas as funções do ficheiro parsing.c
 */

#ifndef PARSING_H
#define PARSING_H

#include "modules/users/users.h"
#include "modules/commits/commits.h"
#include "modules/repos/repos.h"

#include "hashtable/hashtable.h"

USERS create_users_catalog(int *bots, int *orgs, int *users);
COMMITS create_commits_catalog(USERS us, ht *ht_repo_colabs, int *n_commits);
REPOS create_repos_catalog(int *n_repos);

#endif
