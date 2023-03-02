#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define ROWS 10
#define COLUMNS 10000

void __pid_and_ppid(){
  printf("child: %d\nfather: %d\n", getpid(), getppid());
}

void __pid_ppid(){
  pid_t pid;
  if((pid = fork())==0){
    printf("child: %d father: %d\n", getpid(), getppid());
    _exit(0);
  } else{
    int status;
    wait(&status);
    printf("child: %d father: %d bash: %d\n", pid, getpid(), getppid());
  }
}

void __10_pid_seq(){
  for(int i = 1;i<11;i++){
    if(fork()==0){
      printf("child: %d father: %d\n", getpid(), getppid());
      _exit(i);
    } else{
      int status;
      wait(&status);
      if(WIFEXITED(status))
        printf("child: %d left\n",WEXITSTATUS(status));   
    }
  }
} 

void __10_pid_conc(){
  for(int i = 1;i<11;i++){
    if(!fork()){
      _exit(i);
    } 
  }
  int status;
  while(wait(&status)!= -1){
     printf("child: %d left\n",WEXITSTATUS(status));
  } 
}

void __matrix_number(){
  int matrix[ROWS][COLUMNS];
  for(int i = 0; i < ROWS; i++)
    for(int j = 0; j < COLUMNS; j++)
      matrix[i][j] = rand() % COLUMNS;
  int num = rand() % COLUMNS;
  for(int i = 0; i < ROWS; i++) {
    if(fork() == 0) {
      // search line
      for(int j = 0; j < COLUMNS; j++) {
        if(matrix[i][j] == num)
          _exit(1); 
      }
      _exit(0);
    }
  }

  int ocurrences = 0;
  int status;
  for(int i = 0; i < ROWS; i++) {
    wait(&status);
    if(WEXITSTATUS(status) == 1)
      ocurrences++;
  }

  printf("number: %d ocurrences: %d\n", num,ocurrences);
}

void __matrix_number_order(){
  int matrix[ROWS][COLUMNS];
  for(int i = 0; i < ROWS; i++)
    for(int j = 0; j < COLUMNS; j++)
      matrix[i][j] = rand() % COLUMNS;

  int num = rand() % COLUMNS;
  printf("number: %d\n",num);
  for(int i = 0; i < ROWS; i++) {
    if(fork() == 0) {
      // search line
      for(int j = 0; j < COLUMNS; j++) {
        if(matrix[i][j] == num)
          _exit(1); 
      }
      _exit(0);
    }
  }

  int status;
  for(int i = 0; i < ROWS; i++) {
    wait(&status);
    if(WEXITSTATUS(status) == 1)
      printf("row: %d\n", i);

  }
}


int main(const int argc, const char* argv[]){
  if (argc==2){
    if(strcmp(argv[1],"ps")==0) __pid_and_ppid();
    else if(strcmp(argv[1],"ps2")==0) __pid_ppid(); 
    else if(strcmp(argv[1],"matrix")==0) __matrix_number();
  } else if(argc==3){
    if(strcmp(argv[1],"ps10")==0){
      if(strcmp(argv[2],"-s")==0)  __10_pid_seq();
      else if(strcmp(argv[2],"-c")==0)  __10_pid_conc();
    } else if(strcmp(argv[1],"matrix")==0){
      if(strcmp(argv[2],"-o")==0) __matrix_number_order();
    }
  }
  return 0;
}