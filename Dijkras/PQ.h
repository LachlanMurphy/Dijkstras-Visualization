#ifndef PQ_H
#define PQ_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void* data;
    int priority;
} PQ_node;

typedef struct {
    PQ_node** tree;
    unsigned int size;
    unsigned int capacity;
} PQ;

void PQ_init(PQ* pq);

// Function to check if the priority queue is empty
int isEmpty(PQ *pq);

// Function to insert an element into the priority queue
void enqueue(PQ *pq, void* data, int priority);

// Function to remove and return the highest priority element from the priority queue
PQ_node* dequeue(PQ *pq);

// maintain structure of heap upward
void heapifyUp(PQ* pq, int pos);

// maintain structure of heap downward
void heapifyDown(PQ* pq, int pos);

// deallocated memory
void PQ_gc(PQ* pq);

#endif // PQ_H