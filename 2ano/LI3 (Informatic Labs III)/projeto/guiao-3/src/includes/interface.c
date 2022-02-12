#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interface.h"

struct paginacao {
  char **results;
  int n_elems;
  int size;
};

PAGINACAO create_paginacao() {
	PAGINACAO pg = calloc(1, sizeof(PAGINACAO));
	pg->size = 5;
	pg->n_elems = 0;
	pg->results = calloc(pg->size, sizeof (char*));
	return pg;
}

void push_pagina(PAGINACAO pg, char* line) {
  if (pg->size == pg->n_elems) {  
    pg->size += 5;
    pg->results = realloc(pg->results, pg->size * sizeof(char *));  
  }
  pg->results[pg->n_elems]=malloc(sizeof(char)*(strlen(line)+1));
  strcpy(pg->results[pg->n_elems], line);
  pg->n_elems++;
}

void print_results(int page_num, PAGINACAO pg){
    int pag = (page_num-1) * 5;
    for (int i = pag; (i < pag + 5) && (i < pg->n_elems); i++) printf("%s\n", pg->results[i]);
}

int get_pg_size(PAGINACAO pg){
    return pg->size;
}