/**
 * @file main.c
 * @brief Ficheiro que contém a função principal do programa
 */

#include <stdio.h>
#include <stdlib.h>
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
#include "./includes/interface.h"
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
 * @brief Função delete_line
 *
 * Função que apaga linha de ficheiro
 *
 */
void delete_line(int delete_line, char * filename){
    FILE *fileptr1, *fileptr2;
    char ch;
    int temp = 1;

    //open file in read mode
    fileptr1 = fopen(filename, "r");
    ch = getc(fileptr1);
    /*
    while (ch != EOF){
        printf("%c", ch);
        ch = getc(fileptr1);
    }
    */
    //rewind
    rewind(fileptr1);
    //open new file in write mode
    fileptr2 = fopen("replica.csv", "w");
    ch = 'A';
    while (ch != EOF)
    {
        ch = getc(fileptr1);
        //except the line to be deleted
        if (temp != delete_line)
        {
            //copy all lines in file replica.c
            putc(ch, fileptr2);
        }
        if (ch == '\n')
        {
            temp++;
        }
    }
    fclose(fileptr1);
    fclose(fileptr2);
    remove(filename);
    //rename the file replica.c to original name
    rename("replica.csv", filename);
    fileptr1 = fopen(filename, "r");
    ch = getc(fileptr1);
    /*
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = getc(fileptr1);
    }
    */
    fclose(fileptr1);
}

/**
 * @brief Função exercise_1
 *
 * Função que executa o exercício 1 do guião 1
 * 
 * 
 */
void exercise_1(){
    
    char *files[3] = {USERS_FILEPATH, COMMITS_FILEPATH, REPOS_FILEPATH};
    char line[LINE_BUFFER];

    // percorrer os 3 ficheiro
    for (int i = 0; i < 3; i++) {

        FILE *f = fopen(files[i], "r"); 

        int ok = 0, total = 0;

        // Ler linha a linha no ficheiro e verifica se a linha e valida
        while (fgets(line, LINE_BUFFER, f) != NULL) {
            remove_possible_new_line(line);

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
            if (!valid_line) delete_line(total, files[i]);
            else ok++;
            total++;
        }
        fclose(f);
        printf("FILE: %s TOTAL LINES: %d TOTAL OK: %d TOTAL WRONG: %d\n", files[i], total, ok, total-ok);
    }
}

/**
 * @brief Função exercise_2
 *
 * Função que executa o exercício 2 do guião 1
 * 
 * 
 */
void exercise_2(){
    char *files[3] = {USERS_FILEPATH, COMMITS_FILEPATH, REPOS_FILEPATH,};
    char line[LINE_BUFFER], line_2[LINE_BUFFER];

    // percorrer os 3 ficheiro
    for (int i = 0; i < 3; i++) {
        FILE *f = fopen(files[i], "r"); 

        int ok = 0, total = 0;

        if (i == 0) {
            while (fgets(line, LINE_BUFFER, f) != NULL) {
                remove_possible_new_line(line);

                int valid_line = 0;

                USER u = create_user();
                set_user(u, line);
                valid_line = is_valid_user(u);
                delete_user(u);

                if (!valid_line) delete_line(total,files[i]);
                else ok++;
                total++;
            }
        }

        // Ler linha a linha no ficheiro e verifica os commits
        else if (i == 1){
            while (fgets(line, LINE_BUFFER, f) != NULL) {
                remove_possible_new_line(line);

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
                    remove_possible_new_line(line);

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
                        remove_possible_new_line(line);

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

                //if (!valid_line) delete_line(total, files[i]);
                //else ok++;
                
                if (valid_line) ok++;
                total++;
            }
        }

        // Ler linha a linha no ficheiro e verifica os repos
        else if (i == 2){
            while (fgets(line, LINE_BUFFER, f) != NULL) {
                remove_possible_new_line(line);
        
                int valid_line = 0, half = 0;
                char * owner_id = NULL;
                char * repo_id = NULL;

                REPO r = create_repo();
                set_repo(r, line);
                owner_id = get_repo_owner_id(r);
                repo_id = get_repo_id(r);

                FILE *user= fopen(files[0], "r"); 
                while (fgets(line_2, LINE_BUFFER, user) != NULL){
                    remove_possible_new_line(line);

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
                        remove_possible_new_line(line);

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

                if (!valid_line) delete_line(total, files[i]);
                else ok++;
                total++;
            }   
        }

        fclose(f);
        printf("FILE: %s TOTAL LINES: %d TOTAL OK: %d TOTAL WRONG: %d\n", files[i], total, ok, total-ok);
        
    }
}


int display_sub_interface_IO(int *page_num, int last_page_num, PAGINACAO pg){
    puts("\n");
    print_results(*page_num, pg);
    printf("-------- Página %d de %d --------\n", *page_num, last_page_num);
    printf("P     -> Próxima\n");
    printf("A     -> Anterior\n");
    printf("S <N> -> Saltar para página\n");
    printf("Q     -> Sair\n");
    printf("\nInsira opção:\n");

    char str[10];
    fgets(str, 10, stdin);
    
    if((str[0]=='P' || str[0]=='p') && *page_num<last_page_num){
        (*page_num)++;
        return 1;
    } 
    else if((str[0]=='A' || str[0]=='a') && *page_num>1){
        (*page_num)--;
        return 1;
    }
    else if((str[0]=='S' || str[0]=='s') && atoi(&str[2])<=last_page_num){
        *page_num = atoi(&str[2]);
        return 1;
    } 
    else if((str[0]=='Q' || str[0]=='q')) return 0;

    return 1;
}

void sub_interface_IO(PAGINACAO pg){
    int page_num = 1;
    int last_page_num = get_pg_size(pg)/5;
    while(display_sub_interface_IO(&page_num, last_page_num, pg));
    system("clear||cls");
}

/**
 * @brief Função interface_IO
 *
 * Função para caso não sejam dados quaisquer argumentos na execução do executável
 * 
 */
void interface_IO(){

    PAGINACAO pg = create_paginacao();
    system("clear||cls");
    int ans_data;
    char * n_data = malloc(50*sizeof(char)); char * data1 = malloc(50*sizeof(char)); char * data2 = malloc(50*sizeof(char)); char * lang = malloc(50*sizeof(char));
    char *query_param[4];

    puts("\n|---------------------------------------------------------------------------------------|\n");
    puts("| 1 |                   Quantidade de bots, organizações e utilizadores                 |\n");
    puts("|---------------------------------------------------------------------------------------|\n");
    puts("| 2 |                   Número médio de colaboradores por repositório                   |\n");
    puts("|---------------------------------------------------------------------------------------|\n");
    puts("| 3 |                            Número de bots colaboradores                           |\n");
    puts("|---------------------------------------------------------------------------------------|\n");
    puts("| 4 |                          Média de commits por utilizador                          |\n");
    puts("|---------------------------------------------------------------------------------------|\n");
    puts("| 5 |                  Top N utilizadores com commits entre X e Y data                  |\n");
    puts("|---------------------------------------------------------------------------------------|\n");
    puts("| 6 |                 Top N utilizadores com commits a usar X linguagem                 |\n");
    puts("|---------------------------------------------------------------------------------------|\n");
    puts("| 7 |               Lista de repositórios sem commits a partir de X data                |\n");
    puts("|---------------------------------------------------------------------------------------|\n");
    puts("| 8 |                            Top N linguagens após X data                           |\n");
    puts("|---------------------------------------------------------------------------------------|\n");
    puts("| 9 |            Top N utilizadores com mais commits em repositórios de amigos          |\n");
    puts("|---------------------------------------------------------------------------------------|\n");
    puts("| 10 |                    Top N de utilizadores por cada repositório                    |\n");
    puts("|---------------------------------------------------------------------------------------|\n");

    printf("\nInsira opção: ");
    scanf("%d",&ans_data); 

    switch (ans_data){

        case 1 :
            read_queries_2(1, query_param, NULL);
            break;

        case 2 :
            read_queries_2(2, query_param, NULL);
            break;

        case 3 :
            read_queries_2(3, query_param, NULL);
            break;

        case 4 :
            read_queries_2(4, query_param, NULL);
            break;

        case 5 :
            puts("\nInsira o número de utilizadores:\n");
            scanf("%s",n_data);
            puts("\nInsira a primeira data (formato aceite -> YYYY-MM-DD) :\n");
            scanf("%s",data1);
            puts("\nInsira a segunda data (formato aceite -> YYYY-MM-DD) :\n");
            scanf("%s",data2);
            putchar('\n');
            query_param[1] = n_data;
            query_param[2] = data1;
            query_param[3] = data2;
            read_queries_2(5, query_param, pg);
            sub_interface_IO(pg);
            break;

        case 6 :
            puts("\nInsira o número de utilizadores:\n");
            scanf("%s",n_data);
            puts("\nInsira a linguagem:\n");
            scanf("%s",lang);
            putchar('\n');
            query_param[1] = n_data;
            query_param[2] = lang;
            read_queries_2(6, query_param, pg);
            sub_interface_IO(pg);
            break;

        case 7 :
            puts("\nInsira a data (formato aceite -> YYYY-MM-DD) :\n");
            scanf("%s",data1);
            putchar('\n');
            query_param[1] = data1;      
            read_queries_2(7, query_param, pg);
            sub_interface_IO(pg);
            break;

        case 8 :
            puts("\nInsira o número de utilizadores:\n");
            scanf("%s",n_data);
            puts("\nInsira a data (formato aceite -> YYYY-MM-DD) :\n");
            scanf("%s",data1);
            putchar('\n');
            query_param[1] = n_data;
            query_param[2] = data1;
            read_queries_2(8, query_param, pg);
            sub_interface_IO(pg);

            break;

        case 9 :
            puts("\nInsira o número de utilizadores:\n");
            scanf("%s",n_data);
            putchar('\n');
            query_param[1] = n_data;
            read_queries_2(9, query_param, pg);
            sub_interface_IO(pg);
            break;

        case 10 :
            puts("\nInsira o número de utilizadores:\n");
            scanf("%s",n_data);
            putchar('\n');
            query_param[1] = n_data;
            read_queries_2(10, query_param, pg);
            sub_interface_IO(pg);
            break;
    }

    // do smth

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

    if (!fileExists(USERS_FILEPATH) || !fileExists(COMMITS_FILEPATH) || !fileExists(REPOS_FILEPATH))
        return 0;

    //exercise_1(); // verifica colunas dos files
    //exercise_2(); 

    if (argc == 1){
        opt = 0;
        interface_IO();
    }
    else if (argc == 2){
        if(!fileExists(argv[1])) return 0;
            else{
                opt = 1;
                read_queries(argv[1]);
            }
    }
    
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds\n", time_spent);
    
    return 0;
}

