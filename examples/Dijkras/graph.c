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
        struct Node** tmp = realloc(graph->arr, graph->capacity * 2 * sizeof(struct Node *));
        if (tmp) {
            graph->arr = tmp;
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
    
    // initalize data
    temp->key = key;

    // init array
    temp->adj = (struct Edge **) malloc( sizeof(struct Edge *) );
    temp->adj_capacity = 1;
    temp->adj_len = 0;

    // add node to graph
    graph->arr[graph->size++] = temp;
}

void add_edge(struct Graph* graph, struct Node* n1, struct Node* n2, int weight) {

    // init data
    struct Edge* edge1 = (struct Edge *) malloc( sizeof(struct Edge) );
    edge1->next = n2;
    edge1->weight = weight;

    // add to edge 2 array
    
    if (n1->adj_capacity == n1->adj_len) {
        n1 = realloc(n1, n1->adj_len * 2 * sizeof(struct Edge *));

        if (!n1)
            perror("realloc error in array double");
        
        n1->adj_capacity *= 2;
    }

    n1->adj[n1->adj_len++] = edge1;
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