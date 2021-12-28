#include "define.h"

typedef struct lineData_1 {
	int followers_listCount;
	int followers;
	int following_listCount;
	int following;
} LineData_1;

void get_output_dir_file(char * f);
int isNumber(char * str);
char * removeSpaces(char * str);
int validName(char * str);
int validBool(char * str);
int validList(char *str, int *n);
int validDate(char * str);
int validType(char * str);
//int validLanguage(char * str, LL ll);
//int validLicense(char * str, LL ll);
int fileExists(char *filepath);
void removePossibleNewLine(char line[]);

