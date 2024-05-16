#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <malloc.h>

#include "graph.h"
#include "../../src/lgraph.h"

#define PI 3.141592654
#define LEN 5

extern unsigned int WIDTH;
extern unsigned int HEIGHT;

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

    add_edge(graph, search_node(graph, 12), search_node(graph, 21), 1);
    add_edge(graph, search_node(graph, 12), search_node(graph, 13), 2);
    add_edge(graph, search_node(graph, 21), search_node(graph, 12), 1);


    print_graph(graph);

    remove_edge(graph, search_node(graph, 12), search_node(graph, 21));
    remove_edge(graph, search_node(graph, 21), search_node(graph, 12));
    remove_edge(graph, search_node(graph, 12), search_node(graph, 13));

    remove_node(graph, search_node(graph, 12));
    remove_node(graph, search_node(graph, 21));
    remove_node(graph, search_node(graph, 20));
    remove_node(graph, search_node(graph, 13));
}

void display()
{
    exit(0);
}