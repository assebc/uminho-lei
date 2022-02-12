#ifndef INTERFACE_H
#define INTERFACE_H

typedef struct paginacao *PAGINACAO;

PAGINACAO create_paginacao();
void push_pagina(PAGINACAO pg, char* line);
void print_results(int page_num, PAGINACAO pg);
int get_pg_size(PAGINACAO pg);


#endif