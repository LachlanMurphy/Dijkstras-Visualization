#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <malloc.h>

#include "graph.h"
#include "../../src/lgraph.h"

#define PI 3.141592654


struct Graph* graph;

struct Node* connect = NULL;

void setup() {
    size(500,500);

    graph = (struct Graph *) malloc( sizeof(struct Graph) );
    
    if (!graph)
        perror("malloc error in setup\n");
    
    init_graph(graph);

    // add_node(graph, 12);
    // add_node(graph, 21);
    // add_node(graph, 20);
    // add_node(graph, 13);
    // add_node(graph, 14);
    // add_node(graph, 15);

    // add_edge(graph, search_node(graph, 12), search_node(graph, 21), 1);
    // add_edge(graph, search_node(graph, 12), search_node(graph, 13), 2);
    // add_edge(graph, search_node(graph, 13), search_node(graph, 12), 2);
    // add_edge(graph, search_node(graph, 21), search_node(graph, 12), 1);
    // add_edge(graph, search_node(graph, 12), search_node(graph, 15), 1);
    // add_edge(graph, search_node(graph, 15), search_node(graph, 12), 1);
}

void display()
{
    display_graph(graph);

    if (connect) {
        l_color(255, 255, 255, 0);
        l_line(connect->x, connect->y, mousex, mousey);
        // printf("(%d,%d) (%d,%d)\n", connect->x, connect->y, mousex, mousey);
    }
}

void onExit() {
    destruct_graph(graph);
    print_graph(graph);
}

void keypressed(unsigned char c, int x, int y) {
    switch (c) {
        case '+': {
            add_node(graph, graph->num_nodes);
        } break;
    }
}

void mouseUpdate(int button, int mouse_up, int x, int y) {
    struct Node* clicked = get_clicked(graph, x, y);

    if (clicked && !mouse_up) {
        connect = clicked;
    }

    if (mouse_up && connect) {
        if (clicked) {
            if (edge_exist(connect, clicked))
                remove_edge(graph, connect, clicked);
            else
                add_edge(graph, connect, clicked, graph->num_nodes);
        }
        connect = NULL;
    }
}