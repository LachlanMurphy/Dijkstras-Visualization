#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <malloc.h>

#include "graph.h"
#include "../../src/lgraph.h"

#define PI 3.141592654
#define LEN 5


struct Graph* graph;

void setup() {
    size(500,500);

    graph = (struct Graph *) malloc( sizeof(struct Graph) );
    
    if (!graph)
        perror("malloc error in setup\n");
    
    init_graph(graph);

    add_node(graph, 12);
    add_node(graph, 21);
    add_node(graph, 20);
    add_node(graph, 13);
    add_node(graph, 14);
    add_node(graph, 15);

    add_edge(graph, search_node(graph, 12), search_node(graph, 21), 1);
    add_edge(graph, search_node(graph, 12), search_node(graph, 13), 2);
    add_edge(graph, search_node(graph, 21), search_node(graph, 12), 1);
}

void display()
{
    display_graph(graph);
}

void onExit() {
    destruct_graph(graph);
    print_graph(graph);
}