#include "graph.h"

// ##########################################
// START OF LIST ASSIST FUNCTIONS
// ##########################################

void init_graph(Graph* graph) {
    graph->LL = NULL;
    graph->num_nodes = 0;
}

Node* add_node(Graph* graph, key_t key) {

    // create new Node
    Node* temp = (Node *) malloc( sizeof(Node) );

    if (!temp)
        perror("malloc error in add_node\n");
    
    // initalize data
    temp->key = key;
    temp->adj = NULL;
    temp->x = 0;
    temp->y = 0;
    temp->r = 30;
    temp->col[0] = 255;
    temp->col[1] = 255;
    temp->col[2] = 255;

    // add node to graph
    graph->LL = LL_add_node(graph->LL, temp);

    // increment node counter
    graph->num_nodes++;

    set_node_pos(graph);

    return temp;
}

Edge* add_edge(Graph* graph, Node* n1, Node* n2, int weight) {

    // init data
    Edge* edge = (Edge *) malloc( sizeof(Edge) );
    edge->next = n2;
    edge->weight = weight;
    edge->col[0] = 255;
    edge->col[1] = 255;
    edge->col[2] = 255;

    // add to edge to n1 adj LL
    n1->adj = LL_add_node(n1->adj, edge);
    return edge;
}

void remove_node(Graph* graph, Node* node) {
    // first remove all occurances of this node in other's edges
    for (LL_node* node_crawler = graph->LL; node_crawler; node_crawler = node_crawler->next) {
        Node* n = (Node *) node_crawler->data;
        
        // no need to check itself
        if (n == node)
            continue;
        
        for (LL_node* edge_crawler = n->adj; edge_crawler; edge_crawler = edge_crawler->next) {
            Edge* edge = (Edge *) edge_crawler->data;

            if (edge->next == node) {
                remove_edge(graph, n, node);
                break;
            }
        }
    }

    // deallocate the adj LL
    LL_deconstruct(node->adj);

    // remove data from graph's LL
    LL_node* crawler = graph->LL;
    while (crawler) {
        if (crawler->data == node) {
            // deallocate
            free(crawler->data);

            // move pointers around
            graph->LL = LL_remove_node(graph->LL, crawler);
            break;
        }

        crawler = crawler->next;
    }

    // decrement number of nodes
    if (crawler)
        graph->num_nodes--;
    
    // reposition the rest of the nodes
    set_node_pos(graph);
}

void remove_edge(Graph* graph, Node* n1, Node* n2) {

    // find edge in LL and remove
    LL_node* crawler = n1->adj;
    while (crawler) {
        Edge* tmp = (Edge *) crawler->data;
        if (tmp->next == n2) {
            // remove this edge
            free(tmp);
            
            // remove from LL
            n1->adj = LL_remove_node(n1->adj, crawler);
            break;
        }
    }
}

Node* search_node(Graph* graph, key_t key) {
    // search for node and return pointer to that node
    LL_node* crawler = graph->LL;
    while (crawler) {
        // must cast to Node * because of void* for data
        Node* tmp = (Node *) crawler->data;
        if (tmp->key == key)
            return tmp;
        
        crawler = crawler->next;
    }

    return NULL;
}

void print_graph(Graph* graph) {

    if (!graph->LL){
        printf("Graph empty\n");
        return;
    }

    LL_node* node_crawler = graph->LL;
    while (node_crawler) {
        Node* node = (Node *) node_crawler->data;
        printf("%d -> ", node->key);

        LL_node* edge_crawler = node->adj;
        while (edge_crawler) {
            Edge* edge = (Edge *) edge_crawler->data;

            printf("%d, ", edge->next->key);

            edge_crawler = edge_crawler->next;
        }
        printf("\n");

        node_crawler = node_crawler->next;
    }
}

void destruct_graph(Graph* graph) {
    LL_node* crawler = graph->LL;

    // remove all edges from all verticies
    while (crawler) {
        Node* tmp = (Node *) crawler->data;
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

void display_graph(Graph* graph) {

    // loop through each node and display
    LL_node* node_crawler = graph->LL;
    while (node_crawler) {

        Node* node = (Node *) node_crawler->data;

        // displays the node
        l_color(node->col[0],node->col[1],node->col[2], 0);
        l_circle(node->x, node->y, node->r);

        l_color(0,0,0,0);
        l_text(node->x, node->y, "%d", node->key);

        // now display the node's edges
        for (LL_node* edge_crawler = node->adj; edge_crawler; edge_crawler = edge_crawler->next) {
            Node* edge_node = ((Edge *) edge_crawler->data)->next;
            
            Edge* edge = (Edge *) edge_crawler->data;
            l_color(edge->col[0], edge->col[1], edge->col[2], 0);
            display_edge(node, edge_node, edge->weight);
        }

        node_crawler = node_crawler->next;
    }
}

void display_edge(Node* n1, Node* n2, int weight) {
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

    // display edge weight
    px = n2->x-h*cosf(a)/5*2;
    py = n2->y-h*sinf(a)/5*2;
    // l_color(255,255,255,0);
    l_text(px, py, "%d", weight);
}

void set_node_pos(Graph* graph) {
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
    LL_node* crawler = graph->LL;
    for (row = 1; row <= rows; row++) {
        for (col = 1; col <= columns; col++) {
            if (!crawler) {
                return;
            }
            
            Node* node = (Node *) crawler->data;
            node->x = col * xGap;
            node->y = row * yGap;
            crawler = crawler->next;
        }
    }
}

Node* get_clicked(Graph* graph, int x, int y) {
    for (LL_node* crawler = graph->LL; crawler; crawler = crawler->next) {
        Node* node = (Node *) crawler->data;

        if (dis(x,y,node->x, node->y) <= node->r) {
            return node;
        }
    }
    return NULL;
}

 int edge_exist(Node* n1, Node* n2) {
    for (LL_node* crawler = n1->adj; crawler; crawler = crawler->next) {
        Edge* edge = (Edge *) crawler->data;
        if (edge->next == n2)
            return 1;
    }

    return 0;
}

// ##########################################
// DIJKSRAS ALGO
// ##########################################

void find_dis(Graph* graph, Node* start, Node* target) {
    // reset all visited flags
    reset_visited(graph);

    // init tree to keep track of path taken
    Tree tree;
    init_tree(&tree);
    tree_add_node(&tree, NULL, start->key);

    // init PQ
    PQ pq;
    PQ_init(&pq);

    Node* curr = start;
    int last_priority = 0;
    while (1) {
        if (curr == target) {
            printf("Shortest Distance: %d\n", last_priority);
            printf("Shortest Path: ");

            Tree_node* crawler = tree_search_node(&tree, curr->key);
            int prev = -1;
            while (crawler) {
                if (prev != -1) {
                    color_edge(graph, crawler->key, prev);
                }
                prev = crawler->key;
                printf("%d <- ", crawler->key);
                crawler = crawler->parent;
            }
            printf("root\n");
            break;
        }
        curr->visited = true;

        // add all current edges to the queue
        for (LL_node* crawler = curr->adj; crawler; crawler = crawler->next) {
            Edge* edge = (Edge *) crawler->data;
            
            if (edge->next->visited)
                continue;
            
            // enqueue next node
            enqueue(&pq, edge, edge->weight + last_priority);

            // add path to tree
            Tree_node* searched = tree_search_node(&tree, curr->key); 
            tree_add_node(&tree, searched, edge->next->key);
        }

        if (isEmpty(&pq))
            break;

        PQ_node* pq_node = dequeue(&pq);
        last_priority = pq_node->priority;
        Edge* edge = (Edge *) pq_node->data;

        curr = edge->next;
    }

    Tree_gc(&tree);
    PQ_gc(&pq);
}

void reset_visited(Graph* graph) {
    for (LL_node* crawler = graph->LL; crawler; crawler = crawler->next) {
        Node* node = (Node *) crawler->data;
        node->visited = 0;
    }
}

void color_edge(Graph* graph, int start, int target) {
    LL_node* node_crawler = graph->LL;
    while (node_crawler) {
        Node* node = (Node *) node_crawler->data;
        if (node->key == start) {
            LL_node* edge_crawler = node->adj;
            while (edge_crawler) {
                Edge* edge = (Edge *) edge_crawler->data;
                if (edge->next->key == target) {
                    edge->col[0] = 0;
                    edge->col[1] = 255;
                    edge->col[2] = 0;
                    return;
                }

                edge_crawler = edge_crawler->next;
            }
        }

        node_crawler = node_crawler->next;
    }
}