/**
 * @file queries.c
 * @brief Ficheiro que contém as funções para a execução das queries
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../define.h"
#include "../hashtable/hashtable.h"
#include "../linkedlist.h"
#include "../parser.h"
#include "../parsing.h"

#include "../modules/commits/commits.h"
#include "../modules/users/users.h"
#include "../modules/repos/repos.h"

#include "../modules/commits/commit.h"
#include "../modules/users/user.h"
#include "../modules/repos/repo.h"

int output_n = 1;

/**
 * @brief Função get_output_dir_file
 *
 * Função que cria uma dir de output
 * 
 * @returns dir de output
 */
static void get_output_dir_file(char * f){

    mkdir(f,0777);

}

/**
 * @brief Função get_output_file
 *
 * Função que cria um ficheiro de output
 * 
 * @returns ficheiro de output
 */
static FILE* get_output_file () {

  	char output_file[50];
    
    
  	sprintf(output_file, "%s%d%s", "saida/command", output_n, "_output.txt");

    output_n++;
    //printf("%s\n", output_file);
    FILE *f = fopen(output_file, "w");
    if (!f)
    	perror("fopen");
    return f;
}


/**
 * @brief Função query_1
 *
 * Função que executa a query_1
 * 
 */
static void query_1(int bots, int orgs, int users) {
	FILE *output_file = get_output_file();

	//printf("--QUERY 1--\nBOTS: %d ORGS: %d USERS: %d TOTAL: %d\n\n", bots, orgs, users, bots + orgs + users);
    
    fprintf(output_file, "Bot: %d\n", bots);
    fprintf(output_file, "Organization: %d\n", orgs);
    fprintf(output_file, "User: %d\n", users);
    
    fclose(output_file);

}

/**
 * @brief Função query_2
 *
 * Função que executa a query_2
 * 
 */
static void query_2(ht *ht_repo_colabs, int n_repos) {

	int n_colabs = ht_count(ht_repo_colabs);

	//printf("--QUERY 2--\n->Media de colaboradores por reposiotiro<-\nn_colabs: %d\tn_repos: %d\nAVG: %.2f\n\n",n_colabs, n_repos, (float) n_colabs / n_repos);

    FILE *output_file = get_output_file();
    fprintf(output_file, " %.2f\n", (float) n_colabs / n_repos);
    fclose(output_file);

}

/**
 * @brief Função query_3
 *
 * Função que executa a query_3
 * 
 */
static void query_3(ht *ht_repo_colabs) {
	int i = 0, j = 0, bots = 0;
	void *u = NULL;
	while (ht_get_s(ht_repo_colabs, &i ,&j, &u) != NULL) {
		char *type = get_user_type(u);
		if (strcmp(type, "Bot") == 0)
			bots++;
		free(type);
	} 
	

    //printf("--QUERY 3--\nNumero de bots colaboradores: %d\n\n", bots);

    FILE *output_file = get_output_file();
    fprintf(output_file, "%d\n", bots);
    fclose(output_file);

}

/**
 * @brief Função query_4
 *
 * Função que executa a query_4
 * 
 */
static void query_4(int n_commits, int bots, int orgs, int users) {
	int total_users = bots + orgs + users;

    //printf("--QUERY 4--\n->Media de commits por utilizador<-\ntotal_commits: %d\ttotal_users: %d\nAVG: %.2f\n\n", n_commits, total_users, (float) n_commits / total_users);

    FILE *output_file = get_output_file();
    fprintf(output_file, "%.2f\n", (float) n_commits / total_users);
    fclose(output_file);

}

/*
*
*					PARAMETERIZAVEIS
*
*/

/**
 * @brief Função shift_array
 *
 * Função que move 2 arrays de inteiros para a direita partir do indice i
 * 
 */
static void shift_array(int N, int array[2][N], int i) {
	for (int j = N-1; j > i; j--) {
		array[0][j] = array[0][j-1];
		array[1][j] = array[1][j-1];
	}
}

/**
 * @brief Função shift_array
 *
 * Função que move 1 array de inteiros e 1 array de char* para a direita partir do indice i
 * 
 */
static void shift_array_2(int N, int array_data[N], char *array_key[N], int i) {
	for (int j = N-1; j > i; j--) {
		array_data[j] = array_data[j-1];
		array_key[j] = array_key[j-1];
	}
}


/**
 * @brief Função insert_top_n
 *
 * Função que vai buscar o top N de determinada key int
 * 
 */
static void insert_top_n(int N, int array[2][N], int k, int key) {
	for (int j = 0; j < N; j++) {
		if (array[0][j] == -1) {
			array[0][j] = k;
			array[1][j] = key;
			break;
		} else if (k > array[0][j]) {
			shift_array(N, array, j);
			array[0][j] = k;
			array[1][j] = key;
			break;
		}
	}
}

/**
 * @brief Função insert_top_n
 *
 * Função que vai buscar o top N de determinada key char*
 * 
 */
static void insert_top_n_2(int N, int array_data[N], char *array_key[N], int k, char* key) {
	for (int j = 0; j < N; j++) {
		if (array_data[j] == -1) {
			array_data[j] = k;
			array_key[j] = key;
			break;
		} else if (k > array_data[j]) {
			shift_array_2(N, array_data, array_key, j);
			array_data[j] = k;
			array_key[j] = key;
			break;
		}
	}

}
/**
 * @brief Função query_5
 *
 * Função que executa a query_5
 * 
 */
static void query_5(int N, char *init_date, char *end_date, COMMITS cs, USERS us) {
	ht *ht_n_commits = ht_create(TABLE_SIZE);

	int i = 0, j = 0;
	void* x;
	void* c = NULL;
	ht *ht = get_commits_table(cs);
	while (ht_get_s(ht, &i, &j, &c) != NULL) {
			
		char *committer_id = get_commit_committer_id(c);
		char *date = get_commit_commit_at(c);

		if (date_compare(init_date, date) <= 0 && date_compare(end_date, date) >= 0)
			ht_incrementation_insert(ht_n_commits, committer_id);

		free(committer_id);
		free(date);
	}

	int top_n[2][N];

    for (int i = 0; i < N; i++)
        top_n[0][i] = -1;

    i = j = 0;
   	char *key = NULL;
    while ((key = ht_get_s(ht_n_commits, &i, &j, &x)) != NULL) {
    	int c = *(int*)x;
    	insert_top_n(N, top_n, c, atoi(key));
    }

    FILE *output_file = get_output_file();

    char user_id[15];
    //printf("--QUERY 5--\n->TOP %d users committing between %s and %s <-\n", N, init_date, end_date);
    for (int i = 0; i < N; i++) {
        if (top_n[0][i] == -1)
            break;
		sprintf(user_id, "%d", top_n[1][i]);
        USER u = get_user_no_mem_cpy(us, user_id);
        if (u != NULL) {
        	char *login = get_user_login(u);
        	//printf("%d;%s;%d\n", top_n[1][i], login, top_n[0][i]);
        	fprintf(output_file, "%d;%s;%d\n", top_n[1][i], login, top_n[0][i]);
       	    free(login);
        }

    }
    fclose(output_file);
    ht_destroy(ht_n_commits, NULL);
    //printf("\n");
}

/**
 * @brief Função query_6
 *
 * Função que executa a query_6
 * 
 */
static void query_6(int N, char *language, USERS us, COMMITS cs, REPOS rs) {
	ht *ht_n_commits = ht_create(TABLE_SIZE);

	int i = 0, j = 0;
	void* x;
	void* c = NULL;
	ht *ht = get_commits_table(cs);
	while (ht_get_s(ht, &i, &j, &c) != NULL) {
		
		char *repo_id = get_commit_repo_id(c);
		
		char *committer_id = get_commit_committer_id(c);

		REPO r = get_repo_no_mem_cpy(rs, repo_id);

		if (r != NULL) {

			char *r_language = get_repo_language(r);

			if (strcmp(language, r_language) == 0)
                ht_incrementation_insert(ht_n_commits, committer_id);
            
            free(r_language);
		}
		free(committer_id);
		free(repo_id);
	}

	int top_n[2][N];

    for (int i = 0; i < N; i++)
        top_n[0][i] = -1;

    i = j = 0;
    char *key = NULL;
    while ((key = ht_get_s(ht_n_commits, &i, &j, &x)) != NULL) {
    	int c = *(int*)x;
    	insert_top_n(N, top_n, c, atoi(key));
    }

    FILE *output_file = get_output_file();

    char user_id[15];
    USER u = NULL;
    //printf("--QUERY 6--\n->TOP %d users by commits using %s language<-\n", N, language);
    for (int i = 0; i < N; i++) {
        if (top_n[0][i] == -1)
            break;
		sprintf(user_id, "%d", top_n[1][i]);
        u = get_user_no_mem_cpy(us, user_id);
        if (u != NULL) {
        	char *login = get_user_login(u);
	        //printf("%d;%s;%d\n", top_n[1][i], login, top_n[0][i]);
    	    fprintf(output_file, "%d;%s;%d\n", top_n[1][i], login, top_n[0][i]);
        	free(login);
        }
    }
    fclose(output_file);
    ht_destroy(ht_n_commits, NULL);
    //printf("\n");
}

/**
 * @brief Função query_7
 *
 * Função que executa a query_7
 * 
 */
static void query_7(char *init_date, COMMITS cs, REPOS rs) {
	ht *ht_n_commits = ht_create(TABLE_SIZE);

	int i = 0, j = 0;
	void* p = NULL;
	char *key = NULL;

	while ((key = ht_get_s(get_repos_table(rs), &i, &j, &p)) != NULL)
		ht_incrementation_insert(ht_n_commits, key);

	i = j = 0;

	void *c = NULL;
	while (ht_get_s(get_commits_table(cs), &i, &j, &c)) {
		
		char *repo_id = get_commit_repo_id(c);
		char *date = get_commit_commit_at(c);

		if (date_compare(init_date, date) <= 0) {
			ht_incrementation_insert(ht_n_commits, repo_id);
		}

		free(date);
		free(repo_id);
	}

	FILE *output_file = get_output_file();

    //printf("--QUERY 7--\n->Lista de repositorios sem commits a partir de %s\n", init_date);

	i = j = 0;

	int k = 0;

	while ((key = ht_get_s(ht_n_commits, &i, &j, &p)) != NULL) {
		int c = *(int*)p;
		
		if (c == 1) {
			REPO r = ht_get(get_repos_table(rs), key, create_repo, copy_repo);
			
			if (r != NULL) {
				char *description = get_repo_description(r);
				fprintf(output_file, "%s;%s\n", key, description);
				k++;
				free(description);
			}

			delete_repo(r);
		}		
	}
	fclose(output_file);
	ht_destroy(ht_n_commits, NULL);
	//printf("%d repositorios.\n\n", k);
}

/**
 * @brief Função query_8
 *
 * Função que executa a query_8
 * 
 */
static void query_8(int N, char* init_date, COMMITS cs, REPOS rs) {
	ht *ht_n_commits = ht_create(TABLE_SIZE);

	int i = 0, j = 0;
	void *p = NULL;

	while (ht_get_s(get_commits_table(cs), &i, &j, &p) != NULL) {
			
		char *date = get_commit_commit_at(p);
		char *repo_id = get_commit_repo_id(p);
		REPO r = get_repo_no_mem_cpy(rs, repo_id);
		if (r != NULL) {
			char *key = get_repo_language(r);

			if (date_compare(init_date, date) <= 0)
				ht_incrementation_insert(ht_n_commits, key);

			free(key);
		}
		free(date);
		free(repo_id);

	}

	int top_n_data[N];
	char *top_n_key[N];

	i = j = 0;
	for (int i = 0;i < N; i++)
		top_n_data[i] = -1;

	int k = 0;
	char *key = NULL;
	while ((key = ht_get_s(ht_n_commits, &k, &j, &p)) != NULL) {
		int c = *(int*)p;
		insert_top_n_2(N, top_n_data, top_n_key, c, key);
	}

	FILE *output_file = get_output_file();

	for (i = 0; i < N; i++) {
		if (top_n_data[i] == -1)
			break;
		//printf("N: %d Lang: %s\n", top_n_data[i], top_n_key[i]);
		fprintf(output_file, "%s\n", top_n_key[i]);
	}

	fclose(output_file);
	ht_destroy(ht_n_commits, NULL);
	//printf("\n");
}


/**
 * @brief Função query_9
 *
 * Função que executa a query_9
 * 
 */
static void query_9(int N, USERS us, COMMITS cs, REPOS rs) {
	ht *ht_n_commits = ht_create(TABLE_SIZE);
	
	int i = 0, j = 0;
	void *c = NULL;
	char *repo_id = NULL;
	while ((repo_id = ht_get_s(get_commits_table(cs), &i, &j, &c)) != NULL) {
		
		char *committer_id = get_commit_committer_id(c);
		REPO r = get_repo_no_mem_cpy(rs, repo_id);
		if (r != NULL) {
			char *owner_id = get_repo_owner_id(r);

			USER u = get_user_no_mem_cpy(us, committer_id);

			if (u) {

				char *u_following_list = get_user_following_list(u);
				char *u_follower_list = get_user_follower_list(u);

				if (is_follower(u_following_list, owner_id) && is_follower(u_follower_list, owner_id)) 
					ht_incrementation_insert(ht_n_commits, committer_id);
			
				free(u_follower_list);
				free(u_following_list);
			}

			free(owner_id);
		}


		free(committer_id);
	}

	int top_n[2][N];

    for (int i = 0; i < N; i++)
        top_n[0][i] = -1;

    i = j = 0;
    void *u = NULL;
    char *key = NULL;
    while ((key = ht_get_s(ht_n_commits, &i, &j, &u)) != NULL) {
    	int c = *(int*)u;
    	insert_top_n(N, top_n, c, atoi(key));
    }

    FILE *output_file = get_output_file();

    char user_id[15];
    USER u1 = NULL;
    //printf("--QUERY 9--\n->TOP %d users with more commits in repos which owner is his friend<-\n", N);
    for (int i = 0; i < N; i++) {
        if (top_n[0][i] == -1)
            break;
		sprintf(user_id, "%d", top_n[1][i]);
        u1 = get_user_no_mem_cpy(us, user_id);
        if (u1 != NULL) {
        	char *login = get_user_login(u1);
	        //printf("%d;%s commits: %d\n", top_n[1][i], login, top_n[0][i]);
    	    fprintf(output_file, "%d;%s\n", top_n[1][i], login);
        	free(login);
        }
    }
    fclose(output_file);

	ht_destroy(ht_n_commits, NULL);
	//printf("\n");
}

static void query_10(int N, COMMITS cs, USERS us) {

    ht *ht_n_commits = ht_create(TABLE_SIZE);
    int i = 0, j = 0;
    void *c = NULL;
    char *repo_id = NULL;

    while ((repo_id = ht_get_s(get_commits_table(cs), &i, &j, &c)) != NULL) {
        
        char *committer_id = get_commit_committer_id(c);
        if(c){
            char *message = get_commit_message(c);
            //int message_size = strlen(message);

            ht_incrementation_insert(ht_n_commits, committer_id);
            free(message);
        }
        free(committer_id);
    }

    FILE *output_file = get_output_file();

    char user_id[15];
    int top_n[2][N];

    for (int i = 0; i < N; i++)
        top_n[0][i] = -1;

    i = j = 0;
    void *u = NULL;
    char *key = NULL;
    while ((key = ht_get_s(ht_n_commits, &i, &j, &u)) != NULL) {
        int c = *(int*)u;
        insert_top_n(N, top_n, c, atoi(key));
    }
    
    for (int i = 0; i < N; i++) {
        if (top_n[0][i] == -1)
            break;

        sprintf(user_id, "%d", top_n[1][i]);
        u = get_user_no_mem_cpy(us, user_id);
        if (u != NULL) {
            char *login = get_user_login(u);
            repo_id = get_commit_repo_id(c);
            fprintf(output_file, "%d;%s;%d;%s\n", top_n[1][i], login, top_n[0][i], repo_id);
            free(repo_id);
            free(login);
        }
    }

    fclose(output_file);

    ht_destroy(ht_n_commits, NULL);
    //printf("\n")
}

/**
 * @brief Função read_queries
 *
 * Função que lê as queries solicitadas no ficheiro de input
 * 
 */
void read_queries(char* f) {


	int bots = 0, orgs = 0, users = 0, n_commits = 0, n_repos = 0;

	ht *ht_repo_colabs = ht_create(TABLE_SIZE);

	USERS us = create_users_catalog(&bots, &orgs, &users);
	COMMITS cs = create_commits_catalog(us, ht_repo_colabs, &n_commits);
	REPOS rs = create_repos_catalog(&n_repos);

	char line[1024];
	FILE *input_commands = fopen(f, "r");
    get_output_dir_file("saida");
	while (fgets(line, 1024, input_commands) != NULL) {
		remove_possible_new_line(line);

		char *temp_line = strdup(line), *os;
		os = temp_line;
		char *p = NULL;
		char *query_param[4];
		int i = 0;
		while ((p = strsep(&temp_line, " ")) != NULL) {
			query_param[i] = strdup(p);
			i++;
		}
		free(temp_line);

		switch (atoi(query_param[0])) {
			case 1:
				query_1(bots, orgs, users);
				break;
			case 2:
				query_2(ht_repo_colabs, n_repos);
				break;
			case 3:
				query_3(ht_repo_colabs);
				break;
			case 4:
				query_4(n_commits, bots, orgs, users);
				break;
			case 5:
				query_5(atoi(query_param[1]), query_param[2], query_param[3], cs, us);
				break;
			case 6:
				query_6(atoi(query_param[1]), query_param[2], us, cs, rs);
				break;
			case 7:
				query_7(query_param[1], cs, rs);
				break;
			case 8:
				query_8(atoi(query_param[1]), query_param[2], cs, rs);
				break;
			case 9:
				query_9(atoi(query_param[1]), us, cs, rs);
				break;
			case 10:
				query_10(atoi(query_param[1]), cs, us);
				break;
		}

	free(os);
	
	for (int j = 0; j < i; j++)
		free(query_param[j]);

	}

	fclose(input_commands);

	delete_users(us);
	delete_commits(cs);
	delete_repos(rs);

	ht_destroy_no_mem_cpy(ht_repo_colabs);

}
