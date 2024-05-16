#include "graph.h"


void init_graph(struct Graph* graph) {
    graph->LL = NULL;
}

void add_node(struct Graph* graph, key_t key) {

    // create new Node
    struct Node* temp = (struct Node *) malloc( sizeof(struct Node) );

    if (!temp)
        perror("malloc error in add_node\n");
    
    // initalize data
    temp->key = key;

    // init adjacency list
    temp->adj = NULL;

    // add node to graph
    graph->LL = LL_add_node(graph->LL, temp);
}

void add_edge(struct Graph* graph, struct Node* n1, struct Node* n2, int weight) {

    // init data
    struct Edge* edge1 = (struct Edge *) malloc( sizeof(struct Edge) );
    edge1->next = n2;
    edge1->weight = weight;

    // add to edge 2 adj LL
    
    n1->adj = LL_add_node(n1->adj, edge1);
}

void remove_node(struct Graph* graph, struct Node* node) {
    // deallocate the adj LL
    LL_deconstruct(node->adj);

    // remove data from graph's LL
    struct LL_node* crawler = graph->LL;
    while (crawler) {
        if (crawler->data == node) {
            // deallocate
            free(crawler->data);

            // move pointers around
            LL_remove_node(graph->LL, crawler);
            break;
        }
    }
}

void remove_edge(struct Graph* graph, struct Node* n1, struct Node* n2) {

    // find edge in LL and remove
    struct LL_node* crawler = n1->adj;
    while (crawler) {
        struct Edge* tmp = (struct Edge *) crawler->data;
        if (tmp->next == n2) {
            // remove this edge
            free(tmp);

            LL_remove_node(n1->adj, crawler);
            break;
        }
    }
}

struct Node* search_node(struct Graph* graph, key_t key) {
    struct LL_node* crawler = graph->LL;
    while (crawler) {
        struct Node* tmp = (struct Node *) crawler->data;
        if (tmp->key == key)
            return tmp;
        
        crawler = crawler->next;
    }

    return NULL;
}

void print_graph(struct Graph* graph) {
    struct LL_node* node_crawler = graph->LL;
    while (node_crawler) {
        struct Node* node = (struct Node *) node_crawler->data;
        printf("%d -> ", node->key);

        struct LL_node* edge_crawler = node->adj;
        while (edge_crawler) {
            struct Edge* edge = (struct Edge *) edge_crawler->data;

            printf("%d, ", edge->next->key);

            edge_crawler = edge_crawler->next;
        }
        printf("\n");

        node_crawler = node_crawler->next;
    }
}