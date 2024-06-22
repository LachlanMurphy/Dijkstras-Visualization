#include "LL.h"

LL_node* LL_add_node(LL_node* root, void* data) {

    // init data
    LL_node* toAdd = (LL_node *) malloc( sizeof(LL_node) );
    toAdd->data = data;

    // if root is empty add to root
    if (!root) {
        root = toAdd;
        root->next = NULL;
        return root;
    }

    // else crawl until end is reached
    LL_node* crawler = root;
    while (crawler->next)
        crawler = crawler->next;
    
    // adda data
    crawler->next = toAdd;
    toAdd->next = NULL;

    return root;
}


LL_node* LL_remove_node(LL_node* root, LL_node* node) {
    // find node to remove

    LL_node* crawler = root;
    LL_node* prev = NULL;
    while (crawler) {
        if (crawler == node) break;
        prev = crawler;
        crawler = crawler->next;
    }
    
    // if node doesnt exist
    if (!crawler)
        perror("Node not found in LL_remove_node\n");
    
    // if root
    if (root == crawler) {
        root = crawler->next;
    } else {
        prev->next = crawler->next;
    }

    // free memory
    free(crawler);
    crawler = NULL;

    return root;
}

void LL_deconstruct(LL_node* root) {
    LL_node* temp = root;
    while (root) {
        temp = root;
        root = root->next;

        free(temp);
    }
}

void LL_print_list(LL_node* root) {
    LL_node* crawler = root;
    while (crawler) {
        printf("%p -> ", crawler);
        crawler = crawler->next;
    }
    printf("NULL\n");
}