#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

#include "LL.h"
#include "../../src/lgraph.h"

// typed for the key for each verticy, or node, in the graph
typedef int key_t;

// defines a graph edge
struct Edge {
    // pointer to next Edge node
    struct Node* next;

    // weight of this edge
    int weight;
};

// defines a Node, or verticy in the graph
struct Node {
    // key to identify this graph node
    key_t key;

    // array of adjacent nodes
    struct LL_node* adj;

    // boolean value for use in graph traversal
    unsigned char visited;

    // stores the distance from the left edge of the screen
    int x;

    // stores the distance from the top of the screen (down is positive)
    int y;

    // radius of the verticy circle on screen
    int r;
};

// stores data of the graph
struct Graph {
    // array to store Nodes in graph
    struct LL_node* LL;

    // number of nodes
    unsigned int num_nodes;
};

// initializes the graph
void init_graph(struct Graph* graph);

// prints the graph and the edges
void print_graph(struct Graph* graph);

// adds a node to the graph with no initial edges
void add_node(struct Graph* graph, key_t key);

// adds an edge from n1 to n2
void add_edge(struct Graph* graph, struct Node* n1, struct Node* n2, int weight);

// removes and frees the memory of a graph node
void remove_node(struct Graph* graph, struct Node* node);

// removes and frees the memory of an edge from n1 to n2
void remove_edge(struct Graph* graph, struct Node* n1, struct Node* n2);

// searched for a node with the key, returns a pointer to that node
struct Node* search_node(struct Graph* graph, key_t key);

// frees memory of all verticies and edges in a graph, sets Graph->LL to NULL
void destruct_graph(struct Graph* graph);

// ##########################################
// START OF VISUAL FUNCTIONS
// ##########################################

void display_graph(struct Graph* graph);


#endif // GRAPH_H