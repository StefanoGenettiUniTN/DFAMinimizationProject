#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "minDfaPartition.h"

/**Add element to a partition*/
void addPartitionElement(struct Partition* p, int v){
    struct ElemPartition* pe = (struct ElemPartition*)malloc(sizeof(struct ElemPartition));
    pe->value=v;
    pe->next=p->head;
    p->head=pe;
}