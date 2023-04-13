#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define FIFO "fifo"

int main(int argc, char *argv[]) {
    int pipe_fd;
    char buffer[1024];

    if (argc != 2) {
        fprintf(stderr, "Uso: %s mensagem\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pipe_fd = open(FIFO, O_WRONLY);
    if (pipe_fd == -1) {
        perror("Erro ao abrir o pipe");
        exit(EXIT_FAILURE);
    }

    snprintf(buffer, sizeof(buffer), "%s\n", argv[1]);
    write(pipe_fd, buffer, strlen(buffer));

    close(pipe_fd);

    return 0;
}




