#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

struct btree {
    int data;
    struct btree * left;
    struct btree * right;    
};

void insert(node ** tree, int val){
    
    node *temp = NULL;
    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        *tree = temp;
        return;
    }

    if(val < (*tree)->data)
    {
        insert(&(*tree)->left, val);
    }
    else if(val > (*tree)->data)
    {
        insert(&(*tree)->right, val);
    }

}

void print_preorder(node * tree){
  
    if(tree)
    {
        printf("%d\n",tree->data);
        print_preorder(tree->left);
        print_preorder(tree->right);
    }

}

int count_nodes(node *tree){

    static int count = 0;
    if(tree){
        count_nodes(tree->left);
        count++;
        count_nodes(tree->right);
    }
    return count;
}
