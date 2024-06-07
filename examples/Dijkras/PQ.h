#ifndef PQ_H
#define PQ_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void* data;
    int priority;
    PQ_node* parent;
    PQ_node* left;
    PQ_node* right;
} PQ_node;

typedef struct {
    PQ_node* root;
    unsigned int size;
} PQ;

void PQ_init(PQ* pq);

// Function to check if the priority queue is empty
int isEmpty(PQ *pq);

// Function to insert an element into the priority queue
void enqueue(PQ *pq, void* data, int priority);

// Function to remove and return the highest priority element from the priority queue
PQ_node dequeue(PQ *pq);

#endif // PQ_H