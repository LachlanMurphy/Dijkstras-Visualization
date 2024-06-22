#ifndef LL_H
#define LL_H

#include <stdlib.h>
#include <stdio.h>

typedef struct ll_node {
    void* data;

    struct ll_node* next;
} LL_node;

// always returns the root
LL_node* LL_add_node(LL_node* root, void* data);
LL_node*  LL_remove_node(LL_node* root, LL_node* node);
void LL_deconstruct(LL_node* root);

void LL_print_list(LL_node* root);

#endif // LL_H