#include "PQ.h"

void PQ_init(PQ* pq) {
    pq->tree = (PQ_node **) malloc( sizeof(PQ_node *) );
    pq->size = 0;
    pq->capacity = 1;
}

// Function to check if the priority queue is empty
int isEmpty(PQ *pq) {
    return pq->size == 0;
}

// Function to insert an element into the priority queue
void enqueue(PQ* pq, void* data, int priority) {
    // init data
    PQ_node* toAdd = (PQ_node *) malloc(sizeof(PQ_node));
    toAdd->data = data;
    toAdd->priority = priority;

    if (pq->capacity == pq->size) {
        // array double
        pq->capacity *= 2;
        pq->tree = (PQ_node **) realloc(pq->tree, pq->capacity);
    }

    // insert element in the last part of the array/tree
    pq->tree[pq->size] = toAdd;

    heapifyUp(pq, pq->size);

    pq->size++;
}

// Function to remove and return the lowest priority element from the priority queue
PQ_node* dequeue(PQ *pq) {
    if (isEmpty(pq))
        return NULL;
    
    PQ_node* toReturn = pq->tree[0];
    PQ_node* last = pq->tree[pq->size-1];

    // swap root and last node
    pq->tree[0] = last;
    pq->tree[--pq->size] = NULL;

    heapifyDown(pq, 0);

    return toReturn;
}

// maintain structure of heap upward
void heapifyUp(PQ* pq, int pos) {
    if (pos == 0)
        return;

    // check if parent is greater, if so swap
    PQ_node* parent = pq->tree[(pos - 1) / 2];
    PQ_node* curr = pq->tree[pos];

    if (parent->priority > curr->priority) {
        // swap pointers in tree array
        pq->tree[pos] = parent;
        pq->tree[(pos - 1) / 2] = curr;

        heapifyUp(pq, (pos - 1) / 2);
    }
}

// maintain structure of heap downward
void heapifyDown(PQ* pq, int pos) {
    int curr = pos;
    int left = 2*pos + 1;
    int right = 2*pos + 2;

    while (1) {
        // check left
        if (left < pq->size && pq->tree[left]->priority < pq->tree[pos]->priority) {
            // swap left value with current value
            PQ_node* tmp = pq->tree[left];
            pq->tree[left] = pq->tree[curr];
            pq->tree[curr] = tmp;

            // update node indicies
            curr = left;
            left = 2*curr + 1;
            right = 2*curr + 2; 
        }
        // check right
        else if (right < pq->size && pq->tree[right]->priority < pq->tree[pos]->priority) {
            // swap right value with current value
            PQ_node* tmp = pq->tree[right];
            pq->tree[right] = pq->tree[curr];
            pq->tree[curr] = tmp;

            // update node indicies
            curr = right;
            left = 2*curr + 1;
            right = 2*curr + 2; 
        }
        // totally heapified
        else {
            break;
        }
    }
}

void PQ_gc(PQ* pq) {
    free(pq->tree);
}