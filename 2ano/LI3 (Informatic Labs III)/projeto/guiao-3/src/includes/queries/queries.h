/**
 * @file queries.h
 * @brief Header quer inicializa as funções do ficheiro queries.c
 */

#ifndef QUERIES_H
#define QUERIES_H

typedef struct paginacao *PAGINACAO;

extern int opt;


PAGINACAO create_paginacao();

void read_queries(char *f);
void read_queries_2(int query, char *query_param[4], PAGINACAO pg);


#endif