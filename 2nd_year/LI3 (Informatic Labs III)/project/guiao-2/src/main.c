/**
 * @file main.c
 * @brief Ficheiro que contém a função principal do programa
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "./includes/modules/commits/commits.h"
#include "./includes/modules/users/users.h"
#include "./includes/modules/repos/repos.h"

#include "./includes/modules/commits/commit.h"
#include "./includes/modules/users/user.h"
#include "./includes/modules/repos/repo.h"

#include "./includes/hashtable/hashtable.h"

#include "./includes/parser.h"
#include "./includes/parsing.h"
#include "./includes/define.h"
#include "./includes/queries/queries.h"

// valgrind --leak-check=full --show-leak-kinds=all -s ./teste 


/**
 * @brief Função fileExists
 *
 * Verifica se ficheiro existe
 * @returns 1 se ficheiro existe
 * @returns 0 se ficheiro não existe
 */
int fileExists(char *filepath)
{
	FILE *f = fopen(filepath, "r");
	if (f == NULL)
	{
		printf("Error, %s doesn't exist.\n", filepath);
		return 0;
	}
	fclose(f);
	return 1;
	
}

/**
 * @brief Função main
 *
 * Ponto de partida da execução do nosso programa.
 * @returns 0
 */
int main (int argc, char * argv[]) {

	double time_spent = 0.0;
	clock_t begin = clock();

	if (!fileExists(USERS_FILEPATH) || !fileExists(COMMITS_FILEPATH) || !fileExists(REPOS_FILEPATH) || !fileExists(argv[1]))
		return 0;

	if (argc == 2){
		if (fileExists(*argv) == 0) return 0;
		read_queries(argv[1]);
	} else {
		printf("Invalid input!\n");
	}
	
	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	printf("The elapsed time is %f seconds\n", time_spent);

	return 0;
}
