#include "graph.h"

// ##########################################
// START OF LIST ASSIST FUNCTIONS
// ##########################################

void init_graph(struct Graph* graph) {
    graph->LL = NULL;
    graph->num_nodes = 0;
}

void add_node(struct Graph* graph, key_t key) {

    // create new Node
    struct Node* temp = (struct Node *) malloc( sizeof(struct Node) );

    if (!temp)
        perror("malloc error in add_node\n");
    
    // initalize data
    temp->key = key;
    temp->adj = NULL;
    temp->x = 0;
    temp->y = 0;
    temp->r = 10;

    // add node to graph
    graph->LL = LL_add_node(graph->LL, temp);

    // increment node counter
    graph->num_nodes++;

    set_node_pos(graph);
}

void add_edge(struct Graph* graph, struct Node* n1, struct Node* n2, int weight) {

    // init data
    struct Edge* edge = (struct Edge *) malloc( sizeof(struct Edge) );
    edge->next = n2;
    edge->weight = weight;

    // add to edge to n1 adj LL
    n1->adj = LL_add_node(n1->adj, edge);
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
            graph->LL = LL_remove_node(graph->LL, crawler);
            break;
        }
    }

    // decrement number of nodes
    if (crawler)
        graph->num_nodes--;
}

void remove_edge(struct Graph* graph, struct Node* n1, struct Node* n2) {

    // find edge in LL and remove
    struct LL_node* crawler = n1->adj;
    while (crawler) {
        struct Edge* tmp = (struct Edge *) crawler->data;
        if (tmp->next == n2) {
            // remove this edge
            free(tmp);
            
            // remove from LL
            n1->adj = LL_remove_node(n1->adj, crawler);
            break;
        }
    }
}

struct Node* search_node(struct Graph* graph, key_t key) {
    // search for node and return pointer to that node
    struct LL_node* crawler = graph->LL;
    while (crawler) {
        // must cast to Node * because of void* for data
        struct Node* tmp = (struct Node *) crawler->data;
        if (tmp->key == key)
            return tmp;
        
        crawler = crawler->next;
    }

    return NULL;
}

void print_graph(struct Graph* graph) {

    if (!graph->LL){
        printf("Graph empty\n");
        return;
    }

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

void destruct_graph(struct Graph* graph) {
    struct LL_node* crawler = graph->LL;

    // remove all edges from all verticies
    while (crawler) {
        struct Node* tmp = (struct Node *) crawler->data;
        LL_deconstruct(tmp->adj);
        tmp->adj = NULL;
        crawler = crawler->next;
    }

    // remove all verticies
    LL_deconstruct(graph->LL);
    graph->LL = NULL;
}

// ##########################################
// START OF VISUAL FUNCTIONS
// ##########################################

void display_graph(struct Graph* graph) {

    // loop through each node and display
    struct LL_node* node_crawler = graph->LL;
    while (node_crawler) {

        struct Node* node = (struct Node *) node_crawler->data;
        l_circle(node->x, node->y, node->r);

        // now display the node's edges
        for (struct LL_node* edge_crawler = node->adj; edge_crawler; edge_crawler = edge_crawler->next) {
            struct Node* edge_node = ((struct Edge *) edge_crawler->data)->next;
            
            display_edge(node, edge_node);
        }

        node_crawler = node_crawler->next;
    }
}

void display_edge(struct Node* n1, struct Node* n2) {
    float x1 = n1->x;
    float y1 = n1->y;
    float x2 = n2->x;
    float y2 = n2->y;

    float h = sqrt((y1 - y2) * (y1 - y2) + (x1 - x2) * (x1 - x2));

    float px = x2 + ((x1 - x2) / h) * n2->r; 
    float py = y2 + ((y1 - y2) / h) * n2->r;

    float val = 1.0f / sqrt(3.0f);

    float a = atan2(y1-y2, x1-x2) + PI;

    l_line(px,py, px-30.0f*cosf(a - val), py-30.0f*sinf(a - val));
    l_line(px,py, px-30.0f*cosf(a + val), py-30.0f*sinf(a + val));
    

    l_line(n1->x, n1->y, n2->x, n2->y);
}

void set_node_pos(struct Graph* graph) {
    int columns = 1;
    int rows = 1;

    // Calculate the number of rows and columns
    while (columns * rows < graph->num_nodes) {
        if (WIDTH / (columns + 1) >= HEIGHT / (rows + 1)) {
            columns++;
        } else {
            rows++;
        }
    }
    
    // Calculate the gap between points
    int xGap = WIDTH / (columns + 1);
    int yGap = HEIGHT / (rows + 1);
    
    // Distribute points
    int col, row;
    struct LL_node* crawler = graph->LL;
    for (row = 1; row <= rows; row++) {
        for (col = 1; col <= columns; col++) {
            if (!crawler) {
                return;
            }
            
            struct Node* node = (struct Node *) crawler->data;
            node->x = col * xGap;
            node->y = row * yGap;
            crawler = crawler->next;
        }
    }
}

struct Node* get_clicked(struct Graph* graph, int x, int y) {
    for (struct LL_node* crawler = graph->LL; crawler; crawler = crawler->next) {
        struct Node* node = (struct Node *) crawler->data;

        if (dis(x,y,node->x, node->y) <= node->r) {
            return node;
        }
    }
    return NULL;
}

 int edge_exist(struct Node* n1, struct Node* n2) {
    for (struct LL_node* crawler = n1->adj; crawler; crawler = crawler->next) {
        struct Edge* edge = (struct Edge *) crawler->data;
        if (edge->next == n2)
            return 1;
    }

    return 0;
}

// ##########################################
// MANIPULATE STRUCTURE OF GRAPH
// ##########################################

