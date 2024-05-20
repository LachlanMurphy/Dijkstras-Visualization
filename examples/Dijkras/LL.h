#ifndef LL_H
#define LL_H

#include <stdlib.h>
#include <stdio.h>

struct LL_node {
    void* data;

    struct LL_node* next;
};

// always returns the root
struct LL_node* LL_add_node(struct LL_node* root, void* data);
struct LL_node*  LL_remove_node(struct LL_node* root, struct LL_node* node);
void LL_deconstruct(struct LL_node* root);

void LL_print_list(struct LL_node* root);

#endif // LL_H