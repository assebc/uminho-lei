#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "commit.h"
#include "user.h"
#include "repo.h"

#include "hashtable.h"
#include "eval.h"
#include "parser.h"

// Funcao que executa o exercicio 1 do guiao 1
void exercise_1(){
	
	char *files[6] = {USERS_FILEPATH, COMMITS_FILEPATH, REPOS_FILEPATH, USERSOK_FILEPATH, COMMITSOK_FILEPATH, REPOSOK_FILEPATH};
	char firstline[LINE_BUFFER], line[LINE_BUFFER];

	// percorrer os 3 ficheiro
	for (int i = 0; i < 3; i++) {

		FILE *f = fopen(files[i], "r"); 
		FILE *ef = fopen(files[i+3], "w");

		fgets(firstline, LINE_BUFFER, f);
		fprintf(ef, "%s", firstline);

		int ok = 0, total = 0;

		// Ler linha a linha no ficheiro e verifica se a linha e valida
		while (fgets(line, LINE_BUFFER, f) != NULL) {
			removePossibleNewLine(line);

			int valid_line = 0;
			
			if (i == 0) { // user
				USER u = create_user();
				set_user(u, line);
				valid_line = is_valid_user(u);
				delete_user(u);
			}
			else if (i == 1) { // commit
				COMMIT c = create_commit();
				set_commit(c, line);
				valid_line = is_valid_commit(c);
				delete_commit(c);
			}
			else { //repo
				REPO r = create_repo();
				set_repo(r, line);
				valid_line = is_valid_repo(r);
				delete_repo(r);
			}
			if (valid_line) {
				ok++;
				fprintf(ef, "%s\n", line);
			}
			total++;
		}
		fclose(f);
		fclose(ef);
		printf("FILE: %s TOTAL LINES: %d TOTAL OK: %d TOTAL WRONG: %d\n", files[i], total, ok, total-ok);
	}
}

// Funcao que executa o exercicio 2 do guiao 1
void exercise_2(){
	char *files[6] = {USERSOK_FILEPATH, COMMITSOK_FILEPATH, REPOSOK_FILEPATH, USERSFINAL_FILEPATH, COMMITSFINAL_FILEPATH, REPOSFINAL_FILEPATH, };
	char firstline[LINE_BUFFER], line[LINE_BUFFER], line_2[LINE_BUFFER];

	// percorrer os 3 ficheiro
	for (int i = 0; i < 3; i++) {
		FILE *f = fopen(files[i], "r"); 
		FILE *ef = fopen(files[i+3], "w");

		fgets(firstline, LINE_BUFFER, f);
		fprintf(ef, "%s", firstline);

		int ok = 0, total = 0;

		if (i == 0) {
			while (fgets(line, LINE_BUFFER, f) != NULL) {
				removePossibleNewLine(line);

				int valid_line = 0;

				USER u = create_user();
				set_user(u, line);
				valid_line = is_valid_user(u);
				delete_user(u);

				if (valid_line) {
					ok++;
					fprintf(ef, "%s\n", line);
				}
				total++;
			}
		}

		// Ler linha a linha no ficheiro e verifica os commits
		else if (i == 1){
			while (fgets(line, LINE_BUFFER, f) != NULL) {
				removePossibleNewLine(line);

				int valid_line = 0, valid_line_2 = 0, tmp_1 = 0, tmp_2 = 0, equal = 0, half = 0;;
				char * commiter_id = NULL;
				char * author_id = NULL;
				char * repo_id = NULL;

				COMMIT c = create_commit();
				set_commit(c, line);

				commiter_id = get_commit_committer_id(c);
				author_id = get_commit_author_id(c);
				repo_id = get_commit_repo_id(c);

				if (strcmp(commiter_id, author_id) == 0) equal = 1;
				
				FILE *user = fopen(files[0], "r"); 
				while (fgets(line_2, LINE_BUFFER, user) != NULL){
					removePossibleNewLine(line);

					USER u = create_user();
					set_user(u,line_2);

					if (equal){
						if(strcmp(commiter_id, get_user_id(u)) == 0){
							half = 1;
							delete_user(u);
							break;
						} else delete_user(u);
					} else {
						if((strcmp(author_id, get_user_id(u)) == 0) && tmp_2 == 0){
							tmp_1 = 1;
							delete_user(u);
						} else if (tmp_1){
							if(strcmp(author_id, get_user_id(u)) == 0){
								tmp_1 = 0;
								half = 1;
								delete_user(u);
								break;
							}
						} else if((strcmp(author_id, get_user_id(u)) == 0) && tmp_1 == 0){
							tmp_2 = 1;
							delete_user(u);
						} else if (tmp_2){
							if(strcmp(commiter_id, get_user_id(u)) == 0){
								tmp_2 = 0;
								half = 1;
								delete_user(u);
								break;
							}
						} else {
							delete_user(u);
						}

					}
				}
				fclose(user);

				if (half){
					FILE *repo = fopen(files[2], "r"); 
					while (fgets(line_2, LINE_BUFFER, repo) != NULL){
						removePossibleNewLine(line);

						REPO r = create_repo();
						set_repo(r,line_2);

						if(strcmp(repo_id, get_repo_id(r)) == 0){
							valid_line_2 = 1;
							delete_repo(r);
							break;
						} else delete_repo(r);
					}
					fclose(repo);
				}

				valid_line = valid_line_2;
				delete_commit(c);

				if (valid_line){
					ok++;
					fprintf(ef, "%s\n", line);
				}
				total++;
			}
		}

		// Ler linha a linha no ficheiro e verifica os repos
		else if (i == 2){
			while (fgets(line, LINE_BUFFER, f) != NULL) {
				removePossibleNewLine(line);
		
				int valid_line = 0, half = 0;
				char * owner_id = NULL;
				char * repo_id = NULL;

				REPO r = create_repo();
				set_repo(r, line);
				owner_id = get_repo_owner_id(r);
				repo_id = get_repo_id(r);

				FILE *user= fopen(files[0], "r"); 
				while (fgets(line_2, LINE_BUFFER, user) != NULL){
					removePossibleNewLine(line);

					USER u = create_user();
					set_user(u,line_2);
					if (strcmp(owner_id,get_user_id(u)) == 0){
						half = 1;
						delete_user(u);
						break;
					}
					delete_user(u);		
				}
				fclose(user);

				if (half == 1){
					FILE *commit = fopen(files[1], "r"); 
					while (fgets(line_2, LINE_BUFFER, commit) != NULL){
						removePossibleNewLine(line);

						COMMIT c = create_commit();
						set_commit(c,line_2);
						if (strcmp(repo_id,get_commit_repo_id(c)) == 0){
							valid_line = 1;
							delete_commit(c);
							break;
						}
						delete_commit(c);		
					}
					fclose(commit);
				}

				delete_repo(r);

				if (valid_line){
					ok++;
					fprintf(ef, "%s\n", line);
				}
				total++;
			}	
		}

		fclose(f);
		fclose(ef);
		printf("FILE: %s TOTAL LINES: %d TOTAL OK: %d TOTAL WRONG: %d\n", files[i], total, ok, total-ok);
		
	}
}


// final function
int main (int argc, char * argv[]) {

	double time_spent = 0.0;
	clock_t begin = clock();

	if (argc == 2){
		get_output_dir_file("saida");
		if(strcmp(argv[1], "exercicio-1") == 0) exercise_1();
		else if(strcmp(argv[1], "exercicio-2") == 0) exercise_2();
		else printf("Error in input");

	} else printf("Error in input");

	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	printf("The elapsed time is %f seconds\n", time_spent);

	return 0;
}
