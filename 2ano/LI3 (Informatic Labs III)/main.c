#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include "eval.h"
#include "btree.h"

int parseColumnex1(int nfile, char *p, int column, LineData_1 *ld)
{
	int n_list_elements = 0;
	if (nfile == 0) // commits
	{
		if (((column == 0 || column == 1  || column == 2) && isNumber(p) && p[0] != '\0') || (column == 3 && validDate(p)) || column == 4)
			return 1;
		return 0;
	}
	else if (nfile == 1) // users
	{
		if (column == 4 && isNumber(p))
			ld->followers = atoi(p);
		else if (column == 5 && validList(p, &n_list_elements))
			ld->followers_listCount = n_list_elements;
		else if (column == 6 && isNumber(p))
			ld->following = atoi(p);
		else if (column == 7 && validList(p, &n_list_elements))
			ld->following_listCount = n_list_elements;
		else if ((column == 1 && p[0] != '\0') || ((column == 0 || column == 8) && isNumber(p))
				|| (column == 3 && validDate(p)) || (column == 2 && validType(p)))
			return 1;
		else if (column == 9 && isNumber(p))
		{
			if (ld->following == ld->following_listCount && ld->following >= 0 && ld->followers == ld->followers_listCount && ld->followers >= 0)
				return 1;
		} else
			return 0;	
		return 1;
	
	} else if (nfile == 2) // repos
	{
		if (((((column == 0 || column == 1 || column == 10 || column == 11 || column == 12 || column == 13) && isNumber(p)) ||  
				(column == 2 && validName(p)) ||
				(column == 3 && (strcmp(p,"") != 0)) ||
				(column == 4 && validBool(p)) ||
				((column == 8 || column == 9) && validDate(p)) ||
				(column == 6 && (strcmp(p,"") != 0)) ||
				(column == 7 ))&& p[0] != '\0') ||
				(column == 5))
			return 1;
	}
	return 0;
}

void sortColumns(int v[], int N,int nfile, char *firstline)
{
	char *standard_columns[3];
	standard_columns[0] = "repo_id;author_id;committer_id;commit_at;message"; // commits
	standard_columns[1] = "id;login;type;created_at;followers;follower_list;following;following_list;public_gists;public_repos"; // users
	standard_columns[2] = "id;owner_id;full_name;license;has_wiki;description;language;default_branch;created_at;updated_at;forks_count;open_issues;stargazers_count;size"; // repos
	char *s, *p = NULL;
    s = strdup(standard_columns[nfile]);
	int i = 0;

	for (int k = 0; k <= N; k++) v[k] = k; // init v

	while ((p = strsep(&s, ";")) != NULL){
		int j = 0;
		char *ss, *q = NULL;
		ss = strdup(firstline);
		while ((q = strsep(&ss, ";")) != NULL) {
			if (strcmp(p, q) == 0) {
				v[j] = i;
				break;
			}
			j++;	
		}
		i++;
	}
}


void Parse_1()
{
	// users commits repos
	const char *files[6];

	// ex1	
	files[0] = COMMITS_FILEPATH;
	files[1] = USERS_FILEPATH;
	files[2] = REPOS_FILEPATH;
	files[3] = COMMITSOK_FILEPATH;
	files[4] = USERSOK_FILEPATH;
	files[5] = REPOSOK_FILEPATH;

	char str[BUFFER];
	char firstline[BUFFER];
	int total, ok, column;

	// LL *ll = malloc(sizeof(LL));
	// initLL(ll);
	
	
		for (int i = 0; i < 3; i++) 
		{
			
		int NCOL = 5*(i+1)-((i*i)/2) + i/2; // numero de colunas do ficheiro
		FILE *f = fopen(files[i], "r");
		FILE *ef = fopen(files[i+3], "w");
		int v[NCOL];
		total = 0, ok = 0;
		LineData_1 *ld = malloc(sizeof(LineData_1));
		//for (int j = 0; j <= NCOL; j++) v[j] = j; // init v
		
		fgets(firstline, BUFFER, f);
		fprintf(ef, "%s", firstline);
		removePossibleNewLine(firstline);
		sortColumns(v, NCOL, i, firstline);
	
		while (fgets(str, BUFFER, f) != NULL) 
		{
			removePossibleNewLine(str);
			char *s = strdup(str), *os;
			os = s;
			char *p = NULL;
			column = 0;
			ld->followers_listCount = -1;
			ld->followers = -1;
			ld->following_listCount = -1;
			ld->following = -1;
			
			while ((p = strsep(&s, ";")) != NULL)
			{
				if (!parseColumnex1(i, p, v[column], ld))
				{
					//printf("LINE: %d WRONG: %d ROW: %s\n", total+2, v[column], p);
				 	break;
				}
				column++;
			}
			if (column == NCOL){
				fprintf(ef, "%s\n", str);
			 	//printf("LINE: %d ROW: %s\n\n", total+2, str);
				ok++;	
			}
			total++;
			free(os);
		}

		printf("FICHEIROS1: %s TOTAL: %d OK: %d WRONG: %d\n", files[i], total, ok, total-ok);
		free(ld);
		fclose(f);
		fclose(ef);
	}
}

// ex 2

btree * id_btree(int file){
	
	// users commits repos
	const char *files[6];

	// ex2
	files[0] = COMMITSOK_FILEPATH;
	files[1] = USERSOK_FILEPATH;
	files[2] = REPOSOK_FILEPATH;
	files[3] = COMMITSFINAL_FILEPATH;
	files[4] = USERSFINAL_FILEPATH;
	files[5] = REPOSFINAL_FILEPATH;

	char str[BUFFER];
	char firstline[BUFFER];
	int column = 0;
	int i = file;
			
	int NCOL = 5*(i+1)-((i*i)/2) + i/2; // numero de colunas do ficheiro
	FILE *f = fopen(files[i], "r");
	int v[NCOL];

	fgets(firstline, BUFFER, f);
	removePossibleNewLine(firstline);
	sortColumns(v, NCOL, i, firstline);
	btree * bin = malloc(sizeof(btree));
	btree * tmp = bin;

	while (fgets(str, BUFFER, f) != NULL) {
		removePossibleNewLine(str);
		char *p = NULL; 
		char *s = strdup(str), *os;
		while ((p = (strsep(&s, ";"))) != "\0") {

			// id user
			if (i == 1){
				if ((column == 0)){
					insertID(&tmp,atoi(p));
					break;
				}
			// id repo		
			} else if (i == 2){
				if ((column == 0)){
					insertID(&tmp,atoi(p));
					break;
				}		
			}
		
		}
	
	}	
	fclose(f);
	return bin;
}


int commit_user_valid(btree * user, char * p){

	int r = 0;
	if(findID(user, atoi(p)) == true) r = 1;

	return r;
}

int commit_repo_valid(btree * repo, char * repo_id){

	int r = 0;
	if(findID(repo, atoi(repo_id)) == true) {
		insert_commit(repo, atoi(repo_id));
		r = 1;
	}
	return r;
}

int repo_owner_valid(btree * user, char * owner_id){

	int r = 0;
	if(findID(user, atoi(owner_id)) == true) r = 1;

	return r;
}

int repo_has_commit(btree * repo, char * id_repo){

	int r =	 0;
	btree * tmp = malloc(sizeof(btree));
	tmp = id_wanted(repo,atoi(id_repo));
	if(tmp->value[1] == 1) r = 1;
	return r;
}

void Parse_2()
{
	// users commits repos
	const char *files[6];

	// ex1	
	files[0] = COMMITSOK_FILEPATH;
	files[1] = USERSOK_FILEPATH;
	files[2] = REPOSOK_FILEPATH;
	files[3] = COMMITSFINAL_FILEPATH;
	files[4] = USERSFINAL_FILEPATH;
	files[5] = REPOSFINAL_FILEPATH;

	char str[BUFFER];
	char firstline[BUFFER];
	int total, ok, column;
	int r = 0;
	char * tmp = NULL;


	// LL *ll = malloc(sizeof(LL));
	// initLL(ll);
	
	
	for (int i = 0; i < 3; i++) 
	{
			
		int NCOL = 5*(i+1)-((i*i)/2) + i/2; // numero de colunas do ficheiro
		FILE *f = fopen(files[i], "r");
		FILE *ef = fopen(files[i+3], "w");
		int v[NCOL];
		total = 0, ok = 0;
		//for (int j = 0; j <= NCOL; j++) v[j] = j; // init v
		
		fgets(firstline, BUFFER, f);
		fprintf(ef, "%s", firstline);
		removePossibleNewLine(firstline);
		sortColumns(v, NCOL, i, firstline);
		char * q = NULL;

		btree * user_btree = id_btree(1);
		btree * repo_btree = id_btree(2);

		while (fgets(str, BUFFER, f) != NULL) 
		{
			removePossibleNewLine(str);
			char *s = strdup(str), *os;
			os = s;
			char *p = NULL;
			column = 0;
			
			while ((p = strsep(&s, ";")) != NULL)
			{ 
				if (i == 0){ 
					if (column == 0){
						if (commit_repo_valid(repo_btree,p) == 1) r = 1;
					} else if (column == 1 || column == 2){
						if (commit_user_valid(user_btree,p) == 1) r = 1; 
						else if (column == 2) break;
					} 

				} else if (i == 2){
					
					if (column == 0){
						if (repo_has_commit(repo_btree, p) == 1) r = 1;
					} else if (column == 1){
						if (repo_owner_valid(user_btree, p) == 1) r = 1; break;
					
					}
					
				}
				column++;

				if (column == NCOL){
					fprintf(ef, "%s\n", str);
					ok++;	
				}

				total++;
				
			}
			free(os);
		//printf("FICHEIROS1: %s TOTAL: %d OK: %d WRONG: %d\n", files[i], total, ok, total-ok);
		
		}
	fclose(f);
	fclose(ef);
	}

}

int main(int ex, char const * argv[])
{
	ex = 2;
	double time_spent = 0.0;
	clock_t begin = clock();
	if (ex == 1)
	{
		if (fileExists(USERS_FILEPATH) && fileExists(COMMITS_FILEPATH) && fileExists(REPOS_FILEPATH))
		{	
			Parse_1();
			clock_t end = clock();
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
			printf("The elapsed time is %f seconds\n", time_spent);
		}
	}
	else if (ex == 2)
	{
		if (fileExists(USERSOK_FILEPATH) && fileExists(COMMITSOK_FILEPATH) && fileExists(REPOSOK_FILEPATH))
		{	
			Parse_2();
			clock_t end = clock();
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
			printf("The elapsed time is %f seconds\n", time_spent);
		}


	} else
		printf("%d is not a valid input!\n", ex);


	return 0;
}
