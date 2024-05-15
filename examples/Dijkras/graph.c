#include "graph.h"


void init_graph(struct Graph* graph) {
    graph->arr = (struct Node **) malloc( sizeof(struct Node *) );
    graph->capacity = 1;
    graph->size = 0;
}

void add_node(struct Graph* graph, key_t key) {
    // normal array doubling and add to array
    

    // array double
    if (graph->capacity == graph->size) {
        struct Graph* tmp = realloc(graph, graph->capacity * 2);
        if (tmp) {
            graph = tmp;
            graph->capacity *= 2;
        } else {
            perror("Realloc error in array double.\n");
        }
        tmp = NULL;
    }

    // create new Node
    struct Node* temp = (struct Node *) malloc( sizeof(struct Node) );

    if (!temp)
        perror("malloc error in add_node\n");
    
    temp->key = key;

    // add node to graph
    graph->arr[graph->size++] = temp;
}

void add_edge(struct Graph* graph, struct Node* n1, struct Node* n2, int weight) {
    // edge from n1 to n2
    struct Edge* edge1 = (struct Edge *) malloc( sizeof(struct Edge) );
    edge1->next = n2;
    edge1->weight = weight;

    struct Edge* edge2 = (struct Edge *) malloc( sizeof(struct Edge) );
    edge2->next = n1;
    edge2->weight = weight;

    

}

void remove_node(struct Graph* graph, key_t key) {

}

void remove_edge(struct Graph* graph, key_t key1, key_t key2) {

}

struct Node* search_node(struct Graph* graph, key_t key) {
    int s = graph->size;
    for (int i = 0; i < s; i++) {
        if (graph->arr[i]->key == key)
            return graph->arr[i];
    }

    return NULL;
}
