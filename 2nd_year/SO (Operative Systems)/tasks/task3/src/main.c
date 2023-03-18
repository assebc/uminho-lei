#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    switch(argc){
        case 4:
            if(strcmp(argv[3],"-s")){
                if(fork() == 0) 
                    execlp("ls", "-l", (char*) NULL);
            }
            else if(strcmp(argv[3],"-n"))
                execlp("ls", "-l", NULL);
            
            break;
        default:
            for(size_t i = 0; i < argc; i++) {
                puts(argv[i]);
            }
    }
    return 0;
}

