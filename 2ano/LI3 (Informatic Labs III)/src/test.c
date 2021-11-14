#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct users{
	int public_repos;
	int id;
	int followers;
	char * follower_list;
	char * type;
	char * following_list;
	int public_gists;
	char * created_at;
	int following;
	char * login;
} *Users;

typedef struct commits{
	int repo_id;
	int commiter_id;
	int author_id;
	char * created_at;
	char * message;
} *Commits;

typedef struct repos{
	char * license;
	char * description;
	char * language;
	char * full_name;
	char * default_branch;
	char * created_at;
	char * updated_at;
	int forks_count;
	int open_issues;
	int stargazers_count;
	int owner_id;
	int id;
	int size;
	int has_wiki;
} *Repos;

#define FILEUSERS "D:/github/Laboratorios-Informatica-III/Ficheiros_Guiao_1/users.csv"
#define FILECOMMITS "D:/github/Laboratorios-Informatica-III/Ficheiros_Guiao_1/commits.csv"
#define FILEREPOS "D:/github/Laboratorios-Informatica-III/Ficheiros_Guiao_1/repos.csv"

int checkcollum(int ncollum, char * collum){

	int commits = 5;
	int repos = 10;
	int users = 14;

	char * v[15];
	int res, i;
	
	switch (ncollum){

		case 5 :
			scanf("%s;%s;%s;%s;%s\n", v[0], v[1], v[2], v[3], v[4]);
			for(i=0;i<ncollum;i++){
				if(strcmp(v[i], collum) == 0) res = i;
			}
			
		break;

		case 10 :
			scanf("%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9]);
			for(i=0;i<ncollum;i++){
				if(strcmp(v[i], collum) == 0) res = i;
			}
		break;

		case 14 :
			scanf("%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9], v[10], v[11], v[12], v[13]);
			for(i=0;i<ncollum;i++){
				if(strcmp(v[i], collum) == 0) res = i;
			}
		break;
	}

	return res;

}

// get a specific collum in a string
char * getfield(char* singleLine, int num){

    char* tok;

    for (tok = strsep(&singleLine, ";");tok && *tok;tok = strsep(&singleLine, ";\n")){
        if (!--num) return tok;
    }

    return NULL;
}

// remove a char from a string
void removeChar(char *str, char garbage) {
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

// count elements on line using a char (follower list or following list example) (char is ",")
int countfield(char * str, char x) {
    int count = 1;

    for(int i=0;i<strlen(str);i++){
        if (str[i] == x){
            count++;
        }
    }

    return count;
}


// exercicio 2


// check if commit have a valid id user
void checkuser(Users user, Commits commit){

}

// check if commit has a repository
void checkrepositorycommit(Commits commit, Repos repos){

}

// main function for check commits
void checkcommit(Users user, Commits commit, Repos repos){
	checkuser(user, commit);
	checkrepositorycommit(commit,repos);
}

// remove repository, owner that does not exit
void removerepositoryuser(Repos repos, Users user){

}

// remove repository if has no commits
void removereposityorycommit(Repos repos, Commits commit){

}

// main function for check repository
void checkrepository(Repos repos, Commits commit, Users user){
	removerepositoryuser(repos, user);
	removereposityorycommit(repos,commit);
}

// main function for exercicie 2
void mainex2(Users user, Commits commit, Repos repos){
	checkcommit(user, commit, repos);
	checkrepository(repos, commit, user);
}

int main() {

	
	return 0;

}