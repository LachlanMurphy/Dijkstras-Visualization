#include "LL.h"

struct LL_node* LL_add_node(struct LL_node* root, void* data) {

    // init data
    struct LL_node* toAdd = (struct LL_node *) malloc( sizeof(struct LL_node) );
    toAdd->data = data;

    // if root is empty add to root
    if (!root) {
        root = toAdd;
        root->next = NULL;
        return root;
    }

    // else crawl until end is reached
    struct LL_node* crawler = root;
    while (crawler->next)
        crawler = crawler->next;
    
    // adda data
    crawler->next = toAdd;
    toAdd->next = NULL;

    return root;
}


void LL_remove_node(struct LL_node* root, struct LL_node* node) {
    // find node to remove

    struct LL_node* crawler = root;
    struct LL_node* prev = NULL;
    while (crawler) {
        if (crawler == node) break;
        prev = crawler;
        crawler = crawler->next;
    }
    
    // if node doesnt exist
    if (!crawler)
        return;
    
    // if root
    if (root == crawler) {
        root = crawler->next;
    } else {
        prev->next = crawler->next;
    }

    // free memory
    free(crawler);
    crawler = NULL;
}

void LL_deconstruct(struct LL_node* root) {
    struct LL_node* temp = root;
    while (root) {
        temp = root;
        root = root->next;

        free(temp);
    }
}