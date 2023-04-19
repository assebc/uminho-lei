#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(const int argc, const char ** argv) {
    
    int res;
    char buffer[1024];
    setbuf(stdout, buffer);
    int fdpass = open("/etc/passwd", O_RDONLY);
    int fdsaida = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0600);
    int fderro = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0600);

    dup2(fdpass, 0);
    close(fdpass);
    
    dup2(fdsaida, 1);
    close(fdsaida);

    dup2(fderro, 2);
    close(fderro);

    int fdin = dup(0);
    int fdout = dup(1);
    int foerr = dup(2);

    while((res=read(0,buffer,1024))>0){
        if(fork() == 0){
            printf("son: %d\n", getpid());
        } else {
            printf("father: %d\n",getpid());
            int status;
            wait(&status);
            if(WIFEXITED(status))
                printf("child: %d left\n",WEXITSTATUS(status)); 
        }
    }

    dup2(fdin, 0);
    close(fdin);
    dup2(fdout, 1);
    close(fdout);
    dup2(foerr, 2);
    close(foerr);

    printf("finished\n");   
    
    return 0;
}