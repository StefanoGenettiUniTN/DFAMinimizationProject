#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "mfset.h"

void MfsetInitialization(struct MfSet* set, int n){
    int i;
    struct SetElement* element;

    //set=(struct MfSet*) malloc(sizeof(struct MfSet));
    set->size=n;
    set->lists=(struct SetList*) malloc(n*sizeof(struct SetList));
    for(i=0; i<n; i++){
        element = (struct SetElement*) malloc(sizeof(struct SetElement));
        element->val=i;
        element->next=NULL;
        element->root=i;
        set->lists[i].head=element;
        set->lists[i].tail=element;
        set->lists[i].length=1;
        set->lists[i].isActive=true;
    }
}

int find(struct MfSet* set, int x){
    struct SetElement* targetElement = set->lists[x].head;
    return targetElement->root;
}

void merge(struct MfSet* set, int x,int y){
    int weightListX = set->lists[x].length;
    int weightListY = set->lists[y].length;
    
    struct SetElement* nextElem;
    int newRoot;

    //Concatenate the shortest list at the end of the longest list
    if(weightListX>weightListY){
        //Change root node for all elements of y set 
        newRoot=x;
        nextElem = set->lists[y].head;
        while(nextElem!=NULL){
            nextElem->root=newRoot;
            nextElem=nextElem->next;
        }

        //Attach list y at the end of list x
        set->lists[x].tail->next = set->lists[y].head;

        //Update tail of list x
        set->lists[x].tail = set->lists[y].tail;

        //Update length of list x
        set->lists[x].length+=weightListY;

        //Update isActive attribute of list y
        set->lists[y].isActive=false;
    }else{
        //Change root node for all elements of x set 
        newRoot=y;
        nextElem = set->lists[x].head;
        while(nextElem!=NULL){
            nextElem->root=newRoot;
            nextElem=nextElem->next;
        }

        //Attach list x at the end of list y
        set->lists[y].tail->next = set->lists[x].head;

        //Update tail of list y
        set->lists[y].tail = set->lists[x].tail;

        //Update length of list y
        set->lists[y].length+=weightListX;

        //Update isActive attribute of list x
        set->lists[x].isActive=false;
    }
}