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

    add_edge()


    for (int i = 0; i < graph->size; i++) {
        printf("%d -> ", graph->arr[i]->key);
    }

    printf("\n");
}

void display()
{
    exit(0);
}