#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <malloc.h>

#include "graph.h"
#include "../lgraph/lgraph.h"

#define PI 3.141592654

// the graph data structure
Graph* graph;

// keeps track of which node to connect to when adding an edge
Node* connect = NULL;

// last edge that was added
Edge* last_edge = NULL;

// start node for dijkstras algo
Node* start = NULL;

// target node for dijkstras algo
Node* target = NULL;

// delete mode
bool del = false;

// if key is pressed for selecting start node
bool start_select = false;

// if key is pressed for slecting target node
bool target_select = false;

// keeps track of the id for the next node
int next_id = 0;

// main function
int main(int argc, char* argv[])
{
    setup();
    l_init(&argc, argv);
}

void setup() {
    // size of window
    size(500,500);

    // init graph
    graph = (Graph *) malloc( sizeof(Graph) );
    
    if (!graph)
        perror("malloc error in setup\n");
    
    // init graph
    init_graph(graph);
}

// display func
void display() {
    // displays graph and clears background
    display_graph(graph);
    l_background(100, 100, 100, 0);

    // draws a line from a source node to the mouse if actively creating an edge
    if (connect) {
        l_color(255, 255, 255, 0);
        l_color(connect->col[0], connect->col[1], connect->col[2], 0);
        l_line(connect->x, connect->y, mousex, mousey);
    }
}

// garbage collect on exit of program
void onExit() {
    destruct_graph(graph);
    print_graph(graph);
}

// 
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
                find_dis(graph, start, target);
            }
        } break;
        case 'p': {
            if (last_edge)
                last_edge->weight++;
        } break;
        case 'l': {
            if (last_edge && last_edge->weight > 0)
                last_edge->weight--;
        } break;
        case 's': {
            start_select = true;
        } break;
        case 't': {
            target_select = true;
        } break;
    }
}

void keyup(unsigned char c, int x, int y) {
    switch (c)
    {
        case '\b':{
            del = false;
        } break;
        case 's': {
            start_select = false;
        } break;
        case 't': {
            target_select = false;
        } break;
    }
}

void mouseUpdate(int button, int mouse_up, int x, int y) {
    Node* clicked = get_clicked(graph, x, y);

    if (connect && start_select) {
        if (start) {
            start->col[0] = 255;
            start->col[1] = 255;
            start->col[2] = 255;
        }
        start = clicked;
        start->col[0] = 0;
        start->col[1] = 255;
        start->col[2] = 0;
        connect = NULL;
        return;
    }

    if (connect && target_select) {
        if (target) {
            target->col[0] = 255;
            target->col[1] = 255;
            target->col[2] = 255;
        }
        target = clicked;
        target->col[0] = 255;
        target->col[1] = 0;
        target->col[2] = 0;
        connect = NULL;
        return;
    }

    if (del && clicked && !mouse_up) {
        remove_node(graph, clicked);
        return;
    }

    if (clicked && !mouse_up) {
        connect = clicked;
    }

    if (mouse_up && connect) {
        if (clicked && connect != clicked) {
            
            if (edge_exist(connect, clicked)) {
                remove_edge(graph, connect, clicked);
                last_edge = NULL;
            } else {
                last_edge = add_edge(graph, connect, clicked, 0);
            }
        }
        connect = NULL;
    }
}