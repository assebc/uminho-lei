/**
 * @file parser.c
 * @brief Ficheiro que contém as funções auxiliares usadas ao longo do projeto
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "define.h"

#define __USE_XOPEN
#include "time.h"

/**
 * @brief Função sh
 *
 * Função que remove um caracter de uma string
 * 
 */
static void sh (char *str)
{
	char *p = str;
	for (;*p; p++) *p = *(p+1);
}

/**
 * @brief Função is_valid_type
 *
 * Função que remove (/n ou /r/n) do final de uma string
 * 
 */
void remove_possible_new_line(char line[]) {
	int len = 0;
	char *s = line;
	while (*s != '\0') { len++; s++; }
	if (line[len-2] == '\r') { //WINDOWS
		sh(s-1);
		sh(s-2);
	} else if (line[len-1] == '\n') // UNIX
		sh(s-1);
}

/**
 * @brief Função remove_spaces
 *
 * Função que retira todos os espaços (' ') de uma dada string
 * 
 * @returns string sem espaços
 */
static char* remove_spaces(char *s) {
	char *p = s;
	while (*p)
	{
		if (*p == ' ')
			sh(p);
		p++;
	}
	return s;
}

/**
 * @brief Função is_valid_date
 *
 * Função que verifica se a string é uma data válida
 * 
 * @returns bool
 */
int is_valid_date(char *s) {
		int year, month, day, hour, minutes, seconds, matches;

	matches = sscanf(s,"%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &minutes, &seconds);
	if (matches == 6 && ((year == 2005 && month > 4) || (year == 2005 && month == 4 && day >=7) || year > 2005) && year <= 2021 && strlen(s) == 19)
	{
		if ((((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day <= 31) || ((month == 4 || month == 6 || month == 9 || month == 11) && day <= 30) || (month == 2 && ((((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && day <= 29) || day <= 28))) && day > 0)
		{
			if (hour >= 0 && hour <= 23 && minutes >= 0 && minutes <= 59 && seconds >= 0 && seconds <= 59)
				return 1;
		}

	}
	return 0;
}

/**
 * @brief Função is_valid_number
 *
 * Função que verifica se a string é um número válido
 * 
 * @returns bool
 */
int is_valid_number(char *s) {
	char *p = s;
	if (p[0] == '\0' || p[0] == '-')
		return 0;
	while (*p)
	{
		if (*p < '0' || *p > '9')	
			return 0;
		p++;
	}
	return 1;
}

/**
 * @brief Função is_valid_list
 *
 * Função que verifica se a string é uma lista válida
 * 
 * @returns bool
 */
int is_valid_list(char *s) {
	char *p = strdup(s), *os;
	os = p;

	if (p[0] == '[' && p[strlen(p) - 1] == ']')
	{
		sh(p);
		p[strlen(p) - 1] = '\0';
		if (strlen(p) == 0) {
				free(os);
				return 1;
			}

		char *q = NULL;
		while ((q = strsep(&p, ",")) != NULL)
		{	
			if (!is_valid_number(remove_spaces(q)) || *q == '\0') {
				free(os);
				return 0;
			}
		}
		free(os);
		return 1;
	}
	free(os);
	return 0;
}

/**
 * @brief Função elem_list
 *
 * Função que verifica o número de elementos numa lista
 * 
 * @returns 0 se for vazia, -1 se inválida ou n que é o tamanho da lista
 */
int elem_list(char *s) {
	char *p = strdup(s), *os;
	os = p;
	int n = 0;
	if (p[0] == '[' && p[strlen(p) - 1] == ']')
	{
		sh(p);
		p[strlen(p) - 1] = '\0';
		if (strlen(p) == 0) {
			free(os);
			return 0;
		}

		char *q = NULL;
		while ((q = strsep(&p, ",")) != NULL)
		{	
			if (!is_valid_number(remove_spaces(q)) || *q == '\0') {
				free(os);
				return -1;
			}
			n++;

		}
		free(os);
		return n;
	}
	free(os);
	return -1;

}

/**
 * @brief Função is_valid_name
 *
 * Função que verifica se a string é um nome válido
 * 
 * @returns bool
 */
int is_valid_name(char *s) {
	char *p = s;
	for (; *p; p++) 
		if (p > s && *p == '/' && *(p+1) != '\0')
			return 1;
	return 0;
}

/**
 * @brief Função is_valid_type
 *
 * Função que verifica se a string é um tipo válido
 * 
 * @returns bool
 */
int is_valid_type(char *s) {
	return (strcmp(s, "Bot") == 0 || strcmp(s, "User") == 0 || strcmp(s, "Organization") == 0) ? 1 : 0;
}

/**
 * @brief Função is_valid_bool
 *
 * Função que verifica se a string é do tipo bool
 * 
 * @returns bool
 */
int is_valid_bool(char *s) {
	char *p = s;
	for (; *p; p++) *p = tolower(*p);	
	return (strcmp(s, "true") == 0 || strcmp(s, "false") == 0) ? 1 : 0;
}

/**
 * @brief Função hash
 *
 * Função que através de determinada key calcula um valor para a sua hash, para a futura inserção na hashtable
 * 
 * @returns valor de hash
 */
int hash(char *key) {
    unsigned int value = 0;
    int i = 0;
    int key_len = strlen(key);

    for (; i < key_len; ++i) {
        value = value * 37 + key[i];
    }

    // 0 <= value < TABLE_SIZE
    value = value % TABLE_SIZE;

    return value;
}

/**
 * @brief Função file_count
 *
 * Conta o número de linhas existentes num dado ficheiro
 * 
 * @returns número de linhas num ficheiro
 */
int file_count(char *file) {
	char line[LINE_BUFFER];
    FILE *f = fopen(file, "r");
    fgets(line, LINE_BUFFER, f);
    int r = 0;
    while(fgets(line, LINE_BUFFER, f) != NULL)
    	r++;
    fclose(f);

    return r;
}

/**
 * @brief Função insertionSort
 *
 * Ordena um array utilizando o algoritmo de ordenação insertion_sort
 * 
 */
void insertion_sort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
 
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

/**
 * @brief Função date_compare
 *
 * Compara duas datas
 * date_2 > date_1 => r < 0
 * date_2 < date_1 => r > 0
 * date _2 == date_1 => r == 0
 * 
 * @returns diferença em segundos de tempo entre as duas datas
 */
int date_compare(char* date_1, char* date_2) {

	struct tm dtb_1 = {0}, dtb_2 = {0};
	time_t dt_1, dt_2;

	strptime(date_1, "%Y-%m-%d %H:%M:%S", &dtb_1);
	strptime(date_2, "%Y-%m-%d %H:%M:%S", &dtb_2);

	dt_1 = mktime(&dtb_1);
	dt_2 = mktime(&dtb_2);

	int r = difftime(dt_1, dt_2);
	
	return r;	
}

/**
 * @brief Função is_follower
 *
 * Verifica se um id pretence a uma lista de de ids
 *
 * @returns bool
 */
int is_follower(char* list, char* id) {
	char *p = strdup(list), *os;
	os = p;
	if (p[0] == '[' && p[strlen(p) - 1] == ']')
	{
		sh(p);
		p[strlen(p) - 1] = '\0';
		if (strlen(p) == 0) {
			free(os);
			return 0;
		}

		char *q = NULL;
		while ((q = strsep(&p, ",")) != NULL)
		{	
			if (strcmp(remove_spaces(q), id) == 0)
				return 1;
		}
		free(os);
		return 0;
	}
	free(os);
	return 0;
}