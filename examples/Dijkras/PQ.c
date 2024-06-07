#include "PQ.h"

void PQ_init(PQ* pq) {
    pq->root = NULL;
    pq->size = 0;
}

// Function to check if the priority queue is empty
int isEmpty(PQ *pq) {
    return pq->root == NULL;
}

// Function to insert an element into the priority queue
void enqueue(PQ *pq, void* data, int priority) {
    // init data
    PQ_node* toAdd = (PQ_node *) malloc(sizeof(PQ_node));
    toAdd->data = data;
    toAdd->priority = priority;
    toAdd->left, toAdd->right, toAdd->parent = NULL;

    if (isEmpty(pq)) {
        pq->root = toAdd;
        return;
    }

    // find where to insert the new node
    int n = pq->size;
    int ls, n_levels;
    unsigned int bit;
    // Let n be the current number of nodes in the tree.
    // Subtract sizes of levels until we're at the last.
    for (ls = 1, n_levels = 0; ; ls *= 2, n_levels++) {
        if (n - ls < 0) break;
        n -= ls;
    }
    // n now contains number of nodes in bottom level
    // n_levels contains the number of complete levels above.
    PQ_node* p = pq->root;
    for (bit = 1 << (n_levels - 1); bit != 1; bit >>= 1)
    if (n & bit)
        p = p->right;
    else
        p = p->left;
    if (n & 1)
        p->right = toAdd;
    else
        p->left = toAdd;
    toAdd->parent = p;

    // now swap up the tree
    PQ_node* crawler = toAdd;
    while (crawler->parent && crawler->parent->priority > crawler->priority) {
        // swap data in this case is a little easier than swapping pointers
        PQ_node temp = *crawler->parent;

        crawler->parent->data = crawler->data;
        crawler->parent->priority = crawler->priority;

        crawler->data = temp.data;
        crawler->priority = temp.priority;

        crawler = crawler->parent;        
    }
}

// Function to remove and return the highest priority element from the priority queue
PQ_node dequeue(PQ *pq) {
    
}