#ifndef GRAPH_H
#define GRAPH_H

/**Description: */
/*
    --> A "Graph" is an array of "AdjList" (=adjacency lists)
    --> An "AdjList" is a list of "Node"
    --> A "Node" is structured by a value and a pointer to the next node of the list
*/
/**---*/

#define MAXLETTER 30

struct Node{
    int value;
    char label;
    struct Node* next;
};

struct AdjList{
    struct Node* head;
    int edgeLables[MAXLETTER];
};

struct Graph{
    int V;  //number of vertices
    struct AdjList* adjList;
};

/*Add an edge to the graph
    Parameters:
        -G: target graph
        -src: source node
        -dest: destination node
*/
void addEdge(struct Graph* G, int src, int dest, char label);


/*Print graph
    Parameters:
        -G: target graph
*/
void printGraph(struct Graph* G);
void printGraphToFile(struct Graph* G, FILE* file);

#endif
