#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * fopen
 * fscanf
 * fgets
 * fclose
 * malloc -> sizeof()
 * perror
 * 
 * strtok
 * strchr 
 * strsep
 * sscanf
 *
 * strdup
 *
 * gprof Texec 
 */

#define FILEPATH "users100.csv"
#define EXITFILE "exitfile.csv"
/*
 * Funcao isNumber, verifica se uma string e composta apenas por digitos
 */
int isNumber(char *str)
{
	char *p = str;
	while (*p)
	{
		if (*p < '0' || *p > '9')	
			return 1;
		p++;
	}
	return 0;
}	

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
/*
 * Funcao validList, verifica se uma lista e valida
 */
int validList(char *str)
{
	char *p = str;

	if (p[0] == '[' && p[strlen(p) - 1] == ']')
	{
		sh(p);
		p[strlen(p) - 1] = '\0';
		if (strlen(p) == 0)
			return 0;

		char *q = NULL;
		while ((q = strsep(&p, ",")) != NULL)
		{
			if (isNumber(removeSpaces(q)) == 1 || *q == '\0')
				return 1;
		}
		return 0;
	}
	return 1;
}

int validDate(char str[])
{	
	int year, month, day, hour, minutes, seconds, matches;
	matches = sscanf(str,"%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &minutes, &seconds);
	if (matches == 6 && ((year == 2005 && month >= 4 && day >=7) || year > 2005) && strlen(str) == 19)
	{
		if (((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day <= 31) || ((month == 4 || month == 6 || month == 9 || month == 11) && day <= 30) || (month == 2 && ((((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && day <= 29) || day <= 28) ) && day >= 0)
		{
			if (hour >= 0 && hour <= 23 && minutes >= 0 && minutes <= 59 && seconds >= 0 && seconds <= 59)
				return 0;
		}

	}
	return 1;
}


int validType (char *str)
{
	return (strcmp(str, "Bot") == 0 || strcmp(str, "User") == 0 || strcmp(str, "Organization") == 0) ? 0 : 1;
}
/*
 * Funcao mainParse, analisa uma linha csv
 */
int mainParse(char *str, int file)
{
	//public_repos;id;followers;follower_list;type;following_list;public_gists;created_at;following;login

	char *p = NULL;
	int column = 0;
	int valid_row = 0;
	
	while ((p = strsep(&str, ";")) != NULL)
	{
		if (file == 1)
		{
			if (!(((column == 0 || column == 1 || column == 2 || column == 6 || column == 8) && isNumber(p) == 0) || ((column == 3 || column == 5) && validList(p) == 0) || (column == 4 && validType(p) == 0) || (column == 7 && validDate(p) == 0) || column == 9)){
				return 1;
			}
			
		}
		else if (file == 2)
		{
			printf("aa");
		}
		else
		{
			printf("aa");
		}
		column++;
		
	}
	return 0;
	//(e);
		
}

int main() {

	FILE *f = fopen(FILEPATH, "r");
	char str[1024];
	char firstline[1024];

	

	if (f == NULL)
		printf("error\n");
	else
	{
		fgets(firstline, 1024,f);
		FILE *e = fopen(EXITFILE, "w");
		fprintf(e, "%s", firstline);
	
		while (fgets(str,1024,f) != NULL)
		{	
			char *s = strdup(str);
			if(mainParse(str, 1) == 0) fprintf(e, "%s", s);			
		}
		fclose(e);
	}
	fclose(f);
	return 0;
}
