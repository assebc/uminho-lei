#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>


#define START 0
#define END 1


typedef struct hash_utils HASH_UTILS;
HASH_UTILS *newHash_Table ();
void insert_PIDS (HASH_UTILS *ht,char* key, char *value);
void delete_PID (HASH_UTILS *ht, char *key);
GHashTable *getHashTable (HASH_UTILS *ht);

int _readc(int fd, char * c);
size_t _readln(int fd, char * buffer, size_t size);
void _printf(char * buffer, size_t size);
void _printf_string(char ** buffer, size_t size);
char * int_to_str(int num);
char * time_t_to_str(time_t timestamp);
char ** _tail(char ** arr, int len);

void make_dir(const char * dirname);
int exists_dir(const char * dirname);

void make_file(const char * filename);
void write_file(const char * filename, char * buffer);
void write_file_append(const char * filename, char * buffer);
void write_file_string(const char * filename, char ** buffer, size_t num_lines);
int exists_file(const char * filename);

time_t get_timeofday();
char ** getProgram(const int argc, char * argv[], int start);
int _cat();
int _cp(const char* from_path, const char* to_path, int size);
void _nl(char * file);
char* join_strings(char** strings, int num_strings);
char* transformList(char** list, int size);
void transformString(char* str, char **lista);
int _size(char *str);
char *my_strptime(const char *s, const char *format, struct tm *tm_time);

#endif