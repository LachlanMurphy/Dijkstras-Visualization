#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef int key_t;

struct Edge {
    // pointer to next node
    struct Node* next;

    // weight of this edge
    int weight;
};

struct Node {
    key_t key;

    // array of adjacent nodes
    struct Edge* adj;
    unsigned int adj_len;
    unsigned int adj_capacity;

    // boolean value for use in graph traversal
    unsigned char visited;
};

struct Graph {
    // array to store Nodes in graph
    struct Node** arr;
    unsigned int size;
    unsigned int capacity;
};

void init_graph(struct Graph* graph);

void add_node(struct Graph* graph, key_t key);
void add_edge(struct Graph* graph, struct Node* n1, struct Node* n2, int weight);
void remove_node(struct Graph* graph, key_t key);
void remove_edge(struct Graph* graph, key_t key1, key_t key2);

struct Node* search_node(struct Graph* graph, key_t key);


#endif // GRAPH_H