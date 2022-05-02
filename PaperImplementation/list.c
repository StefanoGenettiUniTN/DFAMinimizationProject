#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "list.h"

void addPair(struct PDataStructure* P, int state1, int state2, int level){
    struct PStatePair* newPair = (struct PStatePair*) malloc(sizeof(struct PStatePair));
    newPair->p=state1;
    newPair->q=state2;
    
    newPair->next = P->lists[level].head;
    P->lists[level].head = newPair;
    if((P->lists[level].length)==0){    //first element inserted --> mark as list's tail
        P->lists[level].tail = newPair;
    }
    
    P->lists[level].length++;
}

int PIndex(struct PDataStructure* P, int state1, int state2){
    int v;
    int p,q;

    for(v=0; v<(P->size); ++v){
        struct PStatePair* nextPair = P->lists[v].head;
        while(nextPair!=NULL){
            p=nextPair->p;
            q=nextPair->q;
            if((p==state1 && q==state2) || (p==state2 && q==state1)){
                return v;
            }
            nextPair=nextPair->next;
        }
    }

    return -1;
}

void LevelUnion(struct PDataStructure* P, int level1, int level2){
    if(P->lists[level2].length>0){
        P->lists[level1].tail->next=P->lists[level2].head;  //attach a list to another in constant time
        P->lists[level1].tail=P->lists[level2].tail;    //new tail of level1 list
        P->lists[level1].length+=P->lists[level2].length;
    }
}

void resetLevel(struct PDataStructure* P, int level){
    P->lists[level].head=NULL;
    P->lists[level].tail=NULL;
    P->lists[level].length=0;
}