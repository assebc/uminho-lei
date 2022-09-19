#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct users{
	char * public_repos;
	char * id;
	char * followers;
	char * follower_list;
	char * type;
	char * following_list;
	char * public_gists;
	char * created_at;
	char * following;
	char * login;
	struct users * nextL;
	struct users * pastL;
} *Users;

void removeChar(char *str, char garbage) {
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

int countferl(char * str, char x) {
	Users users;
    int count = 1;
    while (users->nextL != NULL) {
    	for(int i=0;i<strlen(users->follower_list);i++){
        	if (users->follower_list[i] == x){
            	count++;
        		users->pastL = users;
        		users=users->nextL;
        	}
        }
    }
    return count;
}

int countfingl(char * str, char x) {
	Users users;
    int count = 1;
    while (users->nextL != NULL) {
    	for(int i=0;i<strlen(users->following_list);i++){
        	if (users->follower_list[i] == x){
            	count++;
        		users->pastL = users;
        		users=users->nextL;
        	}
        }
    }
    return count;
}

char * getfield(char* singleLine, int num){

    char* tok;

    for (tok = strsep(&singleLine, ";");tok && *tok;tok = strsep(&singleLine, ";\n")){
        if (!--num) return tok;
    }

    return NULL;
}

// public_repos ;   id   ; followers ; follower_list ;    type    ; following_list ; public_gists ;       created_at    ; following ; login
// 0            ;23128004;      0    ;      []       ;Organization;     []         ;       0      ;  2016-10-28 20:08:16;     0     ; comandosfor

int checkusers(Users values){

	int r, i;

	for(i=0;;i++){
		scanf("%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", values->public_repos, 
												  values->id, 
												  values->followers, 
												  values->follower_list, 
												  values->type, 
												  values->following_list, 
												  values->public_gists, 
												  values->created_at, 
												  values->following, 
												  values->login);
	}

	// public_repos
	int check_pr = 1;
	if (isdigit(values->public_repos) && (values->public_repos >= 0)) check_pr; else (check_pr = 0);

	// id
	int check_id = 1;
	if (isdigit(values->id) && (values->id >= 0)) check_id; else (check_id = 0);

	// followers
	int check_fer = 1;
	if (isdigit(values->followers) && (values->followers >= 0)) check_fer; else (check_fer = 0);

	// follower_list
	int check_ferl = 1;
	char * virgul = ",";
	char * parR = "[]";
	if (( countferl(values->follower_list, virgul[0]) ) == atoi(values->followers)){
		if (values->follower_list[0] == parR[0] && (values->follower_list[strlen(values->follower_list) - 1] == parR[1]) ) check_ferl;
		else (check_ferl = 0);
	} else check_ferl = 0;
	
	// type
	int check_t = 1;
	if ((values->type == "Organization") || (values->type == "User") || (values->type == "Bot") ) check_t; else (check_t = 0);

	// following_list
	int check_fingl = 1;
	if (( countfingl(values->following_list, virgul[0]) ) == atoi(values->following)){
		if (values->following_list[0] == parR[0] && (values->following_list[strlen(values->following_list) - 1] == parR[1]) ) check_fingl;
		else (check_fingl = 0);
	} else check_fingl = 0;
	
	// public_gists
	int check_pg = 1;
	if (isdigit(values->public_gists) && (values->public_gists >= 0)) check_pg; else (check_pg = 0);

	// created_at
	int check_ca = 1;

	// char data
	char * year = (char *) malloc(2 + 4 * strlen(values->created_at) );
	char * month = (char *) malloc(2 + 2 * strlen(values->created_at) );
	char * day = (char *) malloc(2 + 2 *  strlen(values->created_at) );
	char * hour = (char *) malloc(2 + 2 * strlen(values->created_at) );
	char * minutes = (char *) malloc(2 + 2 * strlen(values->created_at) );
	char * seconds = (char *) malloc(2 + 2 * strlen(values->created_at) );

	year = strcat(strcat(values->created_at[0], values->created_at[1]), strcat(values->created_at[2] ,values->created_at[3]) );
	month = strcat(values->created_at[5], values->created_at[6]);
	day = strcat(values->created_at[8], values->created_at[9]);
	hour = strcat(values->created_at[11], values->created_at[12]);
	minutes = strcat(values->created_at[14], values->created_at[15]);
	seconds = strcat(values->created_at[17], values->created_at[18]);

	// char data to int data
	int yeari = atoi(year);
	int monthi = atoi(month);
	int dayi = atoi(day);
	int houri = atoi(hour);
	int minutesi = atoi(minutes);
	int secondsi = atoi(seconds);

	int passmin = 1; // data above min data
	int miny = 2005; // min year
	int minm = 04; // min month
	int mind = 07; // min day

	if (yeari < miny)
		passmin = 0;
	else if (yeari == miny){
		if (monthi < minm)
			passmin = 0;
		else if (monthi == minm){
			if (dayi > mind)
				passmin;
			else
				passmin = 0;
		} else
			passmin;
	} else
		passmin;

	int passmax = 1; // data below max data
	int maxy = 2021; // max year
	int maxm = 10; // max month
	int maxd = 16; // max day

	if (yeari > maxy)
		passmax = 0;
	else if (yeari == maxy){
		if (monthi > maxm)
			passmax = 0;
		else if (monthi == maxm){
			if (dayi > maxd)
				passmax;
			else
				passmax = 0;
		} else
			passmax;
	} else
		passmax;

	switch(strlen(values->created_at)){

		// values[i].created_at is char when i = 4;7;10;13;16; normal case
		case 19:

			// check min and max data
			if (passmax == passmin == 1) check_ca;
			else check_ca = 0;

			// checks in particular cases that "atoi" transform string of not digits into a perfect data
			if (isdigit(year)) check_ca; else check_ca = 0;
			if (isdigit(month)) check_ca; else check_ca = 0;
			if (isdigit(day)) check_ca; else check_ca = 0;
			if (isdigit(hour)) check_ca; else check_ca = 0;
			if (isdigit(minutes)) check_ca; else check_ca = 0;
			if (isdigit(seconds)) check_ca; else check_ca = 0;

			// check chars data
			if ( ( (values[4].created_at == "-") || (values[4].created_at == "/") ) && ( (values[7].created_at == "-") || (values[7].created_at == "/") ) ) check_ca;
			else check_ca = 1;
			
			// check char hours to minutes
			if ( (values[13].created_at == ":") || (values[13].created_at == "h") ) check_ca;
			else check_ca = 1;

			// check if char when (i = 10) is a space
			if (values[10].created_at == " ") check_ca;
			else check_ca = 1;

			// check char minutes to seconds
			if ( (values[16].created_at == ":") || (values[16].created_at == "m") ) check_ca;
			else check_ca = 1;

			// correct print for data
			if (values[4].created_at == "/") values[4].created_at = "-";
			if (values[7].created_at == "/") values[7].created_at = "-";

			// correct print for time
			if (values[13].created_at == "h") values[13].created_at = ":";
			if (values[16].created_at == "m") values[16].created_at = ":";

			break;
		
		// values[i].created_at is char when i = 4;7;10;13;16;20; case of seconds have the letter s
		case 20:

			// check min and max data
			if (passmax == passmin == 1) check_ca;
			else check_ca = 0;

			// checks in particular cases that "atoi" transform string of not digits into a perfect data
			if (isdigit(year)) check_ca; else check_ca = 0;
			if (isdigit(month)) check_ca; else check_ca = 0;
			if (isdigit(day)) check_ca; else check_ca = 0;
			if (isdigit(hour)) check_ca; else check_ca = 0;
			if (isdigit(minutes)) check_ca; else check_ca = 0;
			if (isdigit(seconds)) check_ca; else check_ca = 0;

			// part from case 19 (init)

			// check chars data
			if ( ( (values[4].created_at == "-") || (values[4].created_at == "/") ) && ( (values[7].created_at == "-") || (values[7].created_at == "/") ) ) check_ca;
			else check_ca = 1;
			
			// check char hours to minutes
			if ( (values[13].created_at == ":") || (values[13].created_at == "h") ) check_ca;
			else check_ca = 1;

			// check if char when (i = 10) is a space
			if (values[10].created_at == " ") check_ca;
			else check_ca = 1;

			// check char minutes to seconds
			if ( (values[16].created_at == ":") || (values[16].created_at == "m") ) check_ca;
			else check_ca = 1;

			// correct print for data
			if (values[4].created_at == "/") values[4].created_at = "-";
			if (values[7].created_at == "/") values[7].created_at = "-";

			// correct print for time
			if (values[13].created_at == "h") values[13].created_at = ":";
			if (values[16].created_at == "m") values[16].created_at = ":";

			// part from case 19 (end)

			// if (i = 20) && values[20].created_at exists and is "s" then it deletes s from the array
			if (values[20].created_at == "s") removeChar(values[i].created_at, 20);
			else check_ca = 1;

			break;
	}

	// following
	int check_fing = 1;
	if (isdigit(values->following) && (values->following >= 0)) check_fing; else (check_fing = 0);

	// login
	int check_l = 1;
	if (values->login != NULL) check_l; else (check_l = 0);

	// checks all members in the struct (arrays in the struct), if there "check's" are equal to 0 (zero)
	if (check_pr == check_id == check_fer == check_ferl == check_t == check_fingl == check_pg == check_ca == check_fing == check_l == 1) return r;
	else {
		r = 0; 
		return r;
	}
}

// public_repos ;   id   ; followers ; follower_list ;    type    ; following_list ; public_gists ;       created_at    ; following ; login
// 0            ;23128004;      0    ;      []       ;Organization;     []         ;       0      ; 2016-10-28 20:08:16 ;     0     ; comandosfor
//																									2016/10/28 20h08m16s


int main(Users values){

	// file pointer
	FILE * fp;

	// open file
	fp = fopen("users100.csv", "r");

	char singleLine[1024000]; // buffer of arrays of lines
	int row_count = 0;

	if(!fp){
		printf("Error\n");
		return 0;
	}

	int i;
	while(fgets(singleLine, 1024000, fp)){

		row_count++;
		if (row_count == 1) continue; // jump row of categories
		else row_count = 1;
		char * tmp = strdup(singleLine);
        
		values->public_repos = getfield(tmp, 0);
		values->id = getfield(tmp, 1);
		values->followers = getfield(tmp, 2);
		values->follower_list = getfield(tmp, 3);
		values->type = getfield(tmp, 4);
		values->following_list = getfield(tmp, 5);
		values->public_gists = getfield(tmp, 6);
		values->created_at = getfield(tmp, 7);
		values->following = getfield(tmp, 8);
		values->login = getfield(tmp, 9);
		
				
	}

	// print into the new file (temp)

	FILE * nfp;

	nfp = fopen("newusers100.csv", "w");

	fprintf(nfp,"public_repos;id;followers;follower_list;type;following_list;public_gists;created_at;following;login\n");
	if(checkusers(values) == 1){		

		fprintf(nfp, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", values->public_repos, 
												  values->id, 
												  values->followers, 
												  values->follower_list, 
												  values->type, 
												  values->following_list, 
												  values->public_gists, 
												  values->created_at, 
												  values->following, 
												  values->login);
	}

	fclose(nfp);

	return 0;
}
