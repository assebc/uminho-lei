#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

int mycp(const char* from_path, const char* to_path, int size){

  ssize_t bytesRead = 0, bytesWrite = 0;
  char buffer[size];

  int fd_start = open(from_path,O_RDONLY);
  int fd_end = open(to_path, O_WRONLY | O_CREAT | O_TRUNC, 0640);
  if(fd_start<0){
    perror("Error while opening!");
    exit(1);
  }

  while((bytesRead = read(fd_start, buffer, size)) > 0) {
    bytesWrite = write(fd_end, buffer, bytesRead);
  }

  close(fd_start);
  close(fd_end);
  
  if(bytesRead - bytesWrite != 0){
    return -1;
  }

  return 0;
}

int mycat(){

  ssize_t bytesRead = 0;
  char buffer[1024]; 
  while((bytesRead = read(STDIN_FILENO,buffer,1024))> 0){
    write(STDOUT_FILENO,buffer,bytesRead);
  }
  return 0;
}

void readc(int fd, char* c){
  ssize_t bytesRead = read(fd,c,1);
  if(bytesRead == -1){
    perror("Error while reading");
    exit(1);
  }
}

ssize_t readln(int fd, char *line, size_t size){
  ssize_t bytesRead = 0;
  char c;

  while(bytesRead < size - 1){
    readc(fd,&c);

    line[bytesRead++] = c;

    if (c == '\n') break;
  }

  return bytesRead;
}

char * int_to_str(int num){
  int temp = num;
  int digits = 0;
  
  // Count the number of digits in the integer
  while (temp != 0) {
      digits++;
      temp /= 10;
  }
  
  // Allocate memory for the string and null terminator
  char* str = (char*)malloc((digits) * sizeof(char));
  
  // Convert each digit to ASCII and store in the string
  for (int i = digits - 1; i >= 0; i--) {
      str[i] = (char)((num % 10) + '0');
      num /= 10;
  }
  
  return str;
}

void mynl(char * file){
  ssize_t bytesRead = 0;
  int id = 1, fd = 0;
  char * buffer = malloc(sizeof(char)*1024);
  char * index = int_to_str(id);

  if ((fd = open(file, O_RDONLY)) == -1) {
    perror("open");
    exit(1);
  }

  while((bytesRead = readln(fd,buffer,1024)) > 0){
    char * res = malloc(sizeof(buffer) + sizeof(index) + 1);
    strcat(res,index);
    strcat(res, " ");
    strcat(res,buffer);
    write(STDOUT_FILENO,res,bytesRead+sizeof(index));
    index = int_to_str(++id);
  }
}

typedef struct person {
    char name[100];
    int age;
} Person;


void pessoas(char flag, char* argv1, char* argv2, int opt){
  Person person;
  ssize_t fd;
  int pos = 0;

  switch (flag){
    case 'i':
      fd = open("pessoas",O_WRONLY | O_CREAT | O_APPEND,0640);
      if(fd<0){
        perror("Error while opening!");
        exit(1);
      }

      strcpy(person.name,argv1);
      person.age = atoi(argv2);
      
      if(write(fd, &person, sizeof(struct person)) < 1){
        perror("Error while writing!");
        close(fd);
        exit(1);
      }

      struct stat st;
      fstat(fd, &st);
      off_t filesize = st.st_size;
      pos = (int)filesize / sizeof(struct person);

      char * index = int_to_str(pos);
      char * res = malloc(sizeof(char)*1024);
      strcat(res,"registo ");
      strcat(res,index);
      strcat(res,"\n");
      write(STDIN_FILENO, res, sizeof(index)+9);

      close(fd);
      break;

    case 'u':
      fd = open("pessoas", O_RDWR);
      int idx = 1;
      if(fd<0){
        perror("Error while opening!");
        exit(1);
      }
      char name[100];
      switch(opt){
        case 0: // argv1 is name
          strcpy(name,argv1);
          break;

        case 1: // argv1 is pos
          pos = atoi(argv1);
          break;
      }
      while(read(fd,&person,sizeof(struct person)) > 0){
        if (((opt==1) && (pos == idx)) || ((opt == 0) && (strcmp(person.name,argv1)==0))){
          person.age = atoi(argv2);
          if(write(fd, &person, sizeof(struct person)) < 1) {
            perror("Couldn't write in file!");
            close(fd);
            exit(1);
          }
        }
        idx++;
      }

      close(fd);
      break;

    case 'o':
      pos = atoi(argv1);
      int age = atoi(argv2);
      pessoas('u',int_to_str(pos),int_to_str(age),1);

      break;

    default:
      perror("Invalid input!");
      exit(1);

  }
}


int main(int argc, char * argv[]){
  switch(argc){
    case 2:
      if(strcmp(argv[1],"mycat")==0) mycat();
      break;

    case 3:
      if(strcmp(argv[1],"mynl")==0) mynl(argv[2]);
      break;

    case 5:
      if(strcmp(argv[1],"mycp")==0) mycp(argv[2],argv[3],atoi(argv[4]));
      else if(strcmp(argv[1],"readln")==0) readln(atoi(argv[2]),argv[3],(size_t)argv[4]);
      else if(strcmp(argv[1],"pessoas")==0){
        if(argv[2][0] == '-'){
          pessoas(argv[2][1],argv[3],argv[4],0);
        }
      }
      break;
  }

  return 0;
}