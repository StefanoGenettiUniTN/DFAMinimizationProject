#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "common.h"

void addEdge(struct Graph* G, int src, int dest, char label){
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));

    newNode->value=dest;
    newNode->label=label;

    newNode->next = G->adjList[src].head;
    G->adjList[src].head = newNode;
}

/*Print graph
    Parameters:
        -G: target graph
*/
void printGraph(struct Graph* G){
    int v;
    for(v=0; v<(G->V); ++v){
        printf("\n===\nAdjList NODE: %d\n", v);
        struct Node* nextNode = G->adjList[v].head;
        while(nextNode!=NULL){
            printf("--[%c]--> %d\n", nextNode->label, nextNode->value);
            nextNode=nextNode->next;
        }
        printf("\n===\n");
    }
    printf("END\n");
}