#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define FIFO "fifo"

int main() {
    int pipe_fd;
    char buffer[1024];
    ssize_t bytes_read;
    int log_fd;

    if (mkfifo(FIFO, 0666) == -1) {
        perror("Erro ao criar fifo");
        exit(EXIT_FAILURE);
    }

    pipe_fd = open(FIFO, O_RDONLY);
    if (pipe_fd == -1) {
        perror("Erro ao abrir o pipe");
        exit(EXIT_FAILURE);
    }

    open(FIFO,O_WRONLY); //isto 

    log_fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0646);
    if (log_fd == -1) {
        perror("Erro ao abrir o arquivo de log");
        exit(EXIT_FAILURE);
    }

    while ((bytes_read = read(pipe_fd, buffer, sizeof(buffer))) > 0) {
        // Server always open without using while true
        write(log_fd, buffer, bytes_read);
    }

    close(log_fd);
    close(pipe_fd);
    unlink(FIFO);

    return 0;
}
