#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <malloc.h>

#include "graph.h"
#include "../../src/lgraph.h"

#define PI 3.141592654

Graph* graph;

Node* connect = NULL;

bool del = false;

int next_id = 0;
int next_edge = 0;

void setup() {
    size(500,500);

    graph = (Graph *) malloc( sizeof(Graph) );
    
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
    l_background(100, 100, 100, 0);

    if (connect) {
        l_color(255, 255, 255, 0);
        l_color(connect->col[0], connect->col[1], connect->col[2], 0);
        l_line(connect->x, connect->y, mousex, mousey);
    }
}

void onExit() {
    destruct_graph(graph);
    print_graph(graph);
}

void keypressed(unsigned char c, int x, int y) {
    switch (c) {
        case '+': {
            add_node(graph, next_id++);
        } break;
        case '\b': {
            del = true;
        } break;
        case 'd': {
            if (graph->num_nodes > 1) {
                Node* start = search_node(graph, 0);
                Node* end = search_node(graph, next_id-1);
                find_path(graph, start, end);
            }
        } break;
    }
}

void keyup(unsigned char c, int x, int y) {
    switch (c)
    {
    case '\b':{
            del = false;
        } break;
    }
}

void mouseUpdate(int button, int mouse_up, int x, int y) {
    Node* clicked = get_clicked(graph, x, y);

    if (del && clicked && !mouse_up) {
        remove_node(graph, clicked);
        return;
    }

    if (clicked && !mouse_up) {
        connect = clicked;
    }

    if (mouse_up && connect) {
        if (clicked && connect != clicked) {
            
            if (edge_exist(connect, clicked))
                remove_edge(graph, connect, clicked);
            else
                add_edge(graph, connect, clicked, next_edge++);
        }
        connect = NULL;
    }
}