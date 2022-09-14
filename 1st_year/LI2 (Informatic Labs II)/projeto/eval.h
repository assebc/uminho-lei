#ifndef ___EVAL_H___
#define ___EVAL_H___

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *restante (char *line);
char *get_token(char *line, char **rest);
char *get_delimited(char *line, char *seps, char **rest);
char *get_string(char *line, char *seps, char **rest);
void handle_array(char *line, STACK *init_stack, DATA *vars);
STACK *eval(char *line, STACK *init_stack, DATA *vars);

