#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];

    if (pipe(fd) < 0) {
        perror("pipe");
        _exit(0);
    }

    if (fork() == 0) { 
        close(fd[1]); 
        
        if (dup2(fd[0], STDIN_FILENO) < 0) {
            perror("dup2");
            _exit(0);
        }

        
        if (execlp("wc", "wc", NULL) < 0) {
            perror("execlp");
           _exit(0);
        }
    } else { 
        close(fd[0]);

        char buf[1024];
        ssize_t bytes_read;
        while ((bytes_read = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
            if (write(fd[1], buf, bytes_read) < 0) {
                perror("write");
                _exit(0);
            }
        }

        close(fd[1]); 

        int status;
        if (wait(&status) < 0) {
            perror("wait");
            _exit(0);
        }
    }

    return 0;
}