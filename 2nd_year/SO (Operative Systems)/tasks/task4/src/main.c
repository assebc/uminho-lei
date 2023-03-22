#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define ROWS 10
#define COLUMNS 10000

void child_to_parent(){
	int p[2];
	pipe(p);
	printf("p[0] -> %d p[1] -> %d\n", p[0], p[1]);

	if(fork()==0){

		close(p[0]);
		int i = 1000;

		write(p[0],&i,sizeof(int));
		printf("Sent to parent %d\n", i);

		close(p[0]);
		_exit(0);

	} else{

		close(p[1]);
		int res = 0;

		read(p[1],&res,sizeof(int));
		printf("Received from child %d\n", res);

		close(p[1]);
		wait(NULL);
	}
}

void parent_to_child(){
	int p[2];
	pipe(p);
	printf("p[0] -> %d p[1] -> %d\n", p[0], p[1]);

	if(fork()==0){

		close(p[1]);
		int res = 0;

		read(p[0],&res,sizeof(int));
		printf("Received from parent %d\n", res);

		close(p[0]);
		_exit(0);

	} else{

		close(p[0]);
		int i = 1000;

		printf("Sent to child %d\n", i);
		write(p[1],&i,sizeof(int));

		close(p[1]);
		wait(NULL);
	}
}


void matrix_number(){
  int matrix[ROWS][COLUMNS];
  int p[2];
  pipe(p);
  for(int i = 0; i < ROWS; i++)
    for(int j = 0; j < COLUMNS; j++)
      matrix[i][j] = rand() % COLUMNS;

  int num = rand() % COLUMNS;
  printf("number: %d\n",num);
  for(int i = 0; i < ROWS; i++) {
    if(fork() == 0) {

      close(p[1]);

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

int main(int argc, char** argv){
	if(argc == 2){
		if(strcmp(argv[1],"1")==0) child_to_parent();
		else if(strcmp(argv[1],"2")==0) parent_to_child(); 
		else if(strcmp(argv[1],"6")==0) matrix_number(); 
	}

	return 0;
}