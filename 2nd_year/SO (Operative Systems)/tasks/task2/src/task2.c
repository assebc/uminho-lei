#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

void __pid_and_ppid(){
  printf("son: %d\nfather: %d\n", getpid(), getppid());
}

void __pid_ppid(){
  pid_t pid;
  int status;
  if((pid = fork())==0){
    printf("son: %d father: %d\n", getpid(), getppid());
    _exit(0);
  } else{
    wait(&status);
    printf("son: %d father: %d bash: %d\n", pid, getpid(), getppid());
  }
}

void __10_pid_seq(){
} 


void __10_pid_conc(){
  for(int i = 0;i<10;i++){
    fork();
  }
}

int main(const int argc, const char* argv[]){
  if (argc==2){
    if(strcmp(argv[1],"ps")==0) __pid_and_ppid();
    else if(strcmp(argv[1],"ps2")==0) __pid_ppid();
    else if(strcmp(argv[1],"ps10")==0){
      if(strcmp(argv[2],"-s")==0)  __10_pid_seq();
      else if(strcmp(argv[2],"-c")==0)  __10_pid_conc();
    }
  }
  return 0;
}