#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

#include "LL.h"
#include "PQ.h"
#include "../../src/lgraph.h"

// typed for the key for each verticy, or node, in the graph
typedef int key_t;

// defines a Node, or verticy in the graph
typedef struct node_t {
    // key to identify this graph node
    key_t key;

    // array of adjacent nodes
    LL_node* adj;

    // boolean value for use in graph traversal
    unsigned char visited;

    // stores the distance from the left edge of the screen
    int x;

    // stores the distance from the top of the screen (down is positive)
    int y;

    // radius of the verticy circle on screen
    int r;

    // color to draw node
    int col[3];
} Node;

// defines a graph edge
typedef struct edge_t {
    // pointer to next Edge node
    Node* next;

    // weight of this edge
    int weight;

    // color to draw edge
    int col[3];
} Edge;

// stores data of the graph
typedef struct {
    // array to store Nodes in graph
    LL_node* LL;

    // number of nodes
    unsigned int num_nodes;
} Graph;

// initializes the graph
void init_graph(Graph* graph);

// prints the graph and the edges
void print_graph(Graph* graph);

// adds a node to the graph with no initial edges
void add_node(Graph* graph, key_t key);

// adds an edge from n1 to n2
void add_edge(Graph* graph, Node* n1, Node* n2, int weight);

// removes and frees the memory of a graph node
void remove_node(Graph* graph, Node* node);

// removes and frees the memory of an edge from n1 to n2
void remove_edge(Graph* graph, Node* n1, Node* n2);

// searched for a node with the key, returns a pointer to that node
Node* search_node(Graph* graph, key_t key);

// frees memory of all verticies and edges in a graph, sets Graph->LL to NULL
void destruct_graph(Graph* graph);

// ##########################################
// START OF VISUAL FUNCTIONS
// ##########################################

// displays all nodes and edges to screen
void display_graph(Graph* graph);

// displays an edge
void display_edge(Node* n1, Node* n2, int weight);

// called every time a node is added, resets all the screen positions of the nodes
void set_node_pos(Graph* graph);

// gets the node clicked on. returns null if no nodes clicked on.
Node* get_clicked(Graph* graph, int x, int y);

// checks if an edge exists between two edges
int edge_exist(Node* n1, Node* n2);

// finds the shortest path between two nodes
void find_path(Graph* graph, Node* start, Node* target);

// sets all nodes in the graph to unvisited
void reset_visited(Graph* graph);

#endif // GRAPH_H