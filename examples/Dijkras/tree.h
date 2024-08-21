#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "LL.h"

typedef struct tree_node_tag {
    struct tree_node_tag** children; // array of children nodes
    int children_size;
    int children_capacity;
    struct tree_node_tag* parent;

    int key;
} Tree_node;

typedef struct {
    Tree_node* root;
} Tree;

void init_tree(Tree* tree);

Tree_node* tree_add_node(Tree* tree, Tree_node* parent, int key);

Tree_node* tree_search_node(Tree* tree, int key);
Tree_node* tree_search_helper(Tree_node* curr, int key);

void Tree_gc(Tree* tree);
void tree_gc_helper(Tree_node* curr);

#endif // TREE_H