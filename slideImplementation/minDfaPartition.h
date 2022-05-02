#ifndef MIN_DFA_PARTITION_H
#define MIN_DFA_PARTITION_H

struct Partition{
    int card;   //number of nodes
    int master;
    struct ElemPartition* head;
};

struct ElemPartition{
    int value;
    struct ElemPartition* next;
};

struct PartitionGraph{
    int maxV;           //max number of vertices
    int currentV;       //actual number of nodes
    struct Partition* adjList;
};

void addPartitionElement(struct Partition* p, int v);

#endif
