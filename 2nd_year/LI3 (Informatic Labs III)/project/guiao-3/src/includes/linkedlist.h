#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct node node;

void node_push(node **n, void* data);

void node_destroy(node *n, void(*delete_data)(void *));

void node_print(node *n, void(*print)(void*));


void* node_get(node *n, char* key, char*(get_specific_data)(void*));
void* node_get_s(node **n);

int node_count(node *n);

#endif