#include "define.h"
#include <stdbool.h>

typedef struct btree{
	int value[2];
	struct btree * left;
	struct btree * right;
} btree;

btree * create_node(int value);
void insertID(btree ** rootptr, int value);
bool findID(btree * root, int value);
btree * id_wanted(btree * root, int value);
void insert_commit(btree * rootptr, int id_repo);