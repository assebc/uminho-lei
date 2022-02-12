/**
 * @file parser.h
 * @brief Header quer inicializa as funções do ficheiro parser.c
 */

#ifndef PARSER_H
#define PARSER_H

int is_valid_date(char *s);
int is_valid_number(char *s);
int is_valid_list(char *s);
int is_valid_type(char *s);
int is_valid_bool(char *s);
int is_valid_name(char *s);
int elem_list(char *s);
void remove_possible_new_line(char *line);

int file_count(char *file);
void insertion_sort(int arr[], int n);

int date_compare(char *date_1, char *date_2);
int is_follower(char* list, char* id);

#endif