#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "define.h"

typedef struct lineData_1 {
	int followers_listCount;
	int followers;
	int following_listCount;
	int following;
} LineData_1;

void sh (char *str)
{
	char *p = str;
	for (;*p; p++) *p = *(p+1);
}

/*
 * Funcao removeSpaces, remove todos os caracteres espaco de uma string e retorna o endereco da string
 */
char* removeSpaces (char *str)
{
	char *p = str;
	while (*p)
	{
		if (*p == ' ')
			sh(p);
		p++;
	}
	return str;
}

int isNumber(char *str)
{
	char *p = str;
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

/*
 * Funcao validList, verifica se uma lista e valida e guarda em n o numero de elementos dentro da lista
 */
int validList(char *str, int *n)
{
	char *p = str;

	if (p[0] == '[' && p[strlen(p) - 1] == ']')
	{
		sh(p);
		p[strlen(p) - 1] = '\0';
		if (strlen(p) == 0)
			return 1;

		char *q = NULL;
		while ((q = strsep(&p, ",")) != NULL)
		{	
			if (!isNumber(removeSpaces(q)) || *q == '\0')
				return 0;
			(*n)++;

		}
		return 1;
	}
	return 0;
}

/*
void fixDateStr(char *str){
	if (str[4] == '/')
		str[4] = '-';
	if (str[7] == '/')
		str[7] = '-';
} */

int validDate(char str[])
{	
	int year, month, day, hour, minutes, seconds, matches;
	//fixDateStr(str);
	matches = sscanf(str,"%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &minutes, &seconds);
	if (matches == 6 && ((year == 2005 && month > 4) || (year == 2005 && month == 4 && day >=7) || year > 2005) && year <= 2021 && strlen(str) == 19)
	{
		if (((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day <= 31) || ((month == 4 || month == 6 || month == 9 || month == 11) && day <= 30) || (month == 2 && ((((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && day <= 29) || day <= 28)) && day > 0)
		{
			if (hour >= 0 && hour <= 23 && minutes >= 0 && minutes <= 59 && seconds >= 0 && seconds <= 59)
				return 1;
		}

	}
	return 0;
}


int validType (char *str)
{
	return (strcmp(str, "Bot") == 0 || strcmp(str, "User") == 0 || strcmp(str, "Organization") == 0) ? 1 : 0;
}


// Verifica se um nome e valido, nome1/nome2
int validName(char *str)
{
	char *p = str;
	for (; *p; p++) 
		if (p > str && *p == '/' && *(p+1) != '\0')
			return 1;
	return 0;
}
// Verifica se o input e bool
int validBool(char *str)
{
	char *p = str;
	for (; *p; p++) *p = tolower(*p);	
	return (strcmp(str, "true") == 0 || strcmp(str, "false") == 0) ? 1 : 0;
}


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

void removePossibleNewLine(char line[]) {
	int len = 0;
	char *s = line;
	while (*s != '\0') { len++; s++; }
	if (line[len-2] == '\r') { //WINDOWS
		sh(s-1);
		sh(s-2);
	} else if (line[len-1] == '\n') // UNIX
		sh(s-1);
}
