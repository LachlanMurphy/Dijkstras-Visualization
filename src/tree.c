#include "tree.h"

void init_tree(Tree* tree) {
    tree->root = NULL;
}

Tree_node* tree_add_node(Tree* tree, Tree_node* parent, int key) {
    Tree_node* toAdd = (Tree_node *) malloc( sizeof(Tree_node) );
    toAdd->children = (Tree_node **) malloc( sizeof(Tree_node *) );
    toAdd->children_capacity = 1;
    toAdd->children_size = 0;
    toAdd->key = key;
    toAdd->parent = NULL;

    if (!tree->root) {
        tree->root = toAdd;
        return tree->root;
    }

    if (parent->children_capacity == parent->children_size) {
        parent->children = (Tree_node **) realloc(parent->children, parent->children_capacity);
    }

    parent->children[parent->children_size++] = toAdd;
    toAdd->parent = parent;
    return toAdd;
}

Tree_node* tree_search_node(Tree* tree, int key) {
    return tree_search_helper(tree->root, key);
}

Tree_node* tree_search_helper(Tree_node* curr, int key) {
    if (curr->key == key)
        return curr;
    for (int i = 0; i < curr->children_size; i++) {
        Tree_node* search = tree_search_helper(curr->children[i], key);
        if (search)
            return search;
    }
    return NULL;
}


void Tree_gc(Tree* tree) {
    tree_gc_helper(tree->root);
}

void tree_gc_helper(Tree_node* curr) {
    for (int i = 0; i < curr->children_size; i++) {
        tree_gc_helper(curr->children[i]);
    }

    // free(curr->children);
    free(curr);
}