#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include "define.h"

typedef struct btree{
	int value[2];
	struct btree * left;
	struct btree * right;
} btree;


btree * create_node(int value){

	btree * result = malloc(sizeof(btree));
	if (result == NULL){
		result->value[0] = value;
		result->value[1] = 0;
		result->left = NULL;
		result->right = NULL;
	}
	return result;
}

void insertID(btree ** rootptr, int val){

	btree * root = *rootptr;

	if (root == NULL) (*rootptr) = create_node(val);
	else if (root->value[0] == val) root->value[0] = val;
	else if (root->value[0] == 0) {
		root->value[0] = val;
		root->value[1] = 0;
	} else if (root->value[0] > val) {
		insertID(&(root->left),val);
	} else if (root->value[0] < val){
		insertID(&(root->right),val);
	}
}


bool findID(btree * root, int value){

	if (root == NULL) return false;
	else if(root->value[0]==value) return true;
	else if (value<root->value[0]) return findID(root->left,value);
	else return findID(root->right,value);

}

btree * id_wanted(btree * root, int value){

	if(root == NULL) return NULL;
	else if(root->value[0]==value) return root;
	else if (value<root->value[0]) return id_wanted(root->left,value);
	else return id_wanted(root->right,value);
}

void insert_commit(btree * rootptr, int id_repo){

	btree * root = rootptr;

	if (id_wanted(root, id_repo) != NULL) root->value[1] = 1; 
}