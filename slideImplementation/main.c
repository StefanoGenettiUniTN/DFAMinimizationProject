/**
 * DFA minimization - Partition refinement
 * @author Stefano Genetti (stefano.genetti@studenti.unitn.it)
 * @date Academic year 2021-2022
 */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "minDfaPartition.h"
#include "common.h"

#define FILENAME "input.txt"
#define OUTPUT "output.txt"

int main(int argc, char** argv){
    //Support variables (counters, ecc...)
    int tmpState;
    int i,j,k;
    bool equivalent;
    bool canSplit;
    int from, to;
    int masterDest;
    int master;
    char label;
    struct ElemPartition* elemPartition;
    struct ElemPartition* elemPartition1;
    int targetClass;
    char targetLetter;
    int* classTmp;

    //DFA
    int N;                              //number of nodes
    int M;                              //number of edges
    struct Graph* graph;                //automata
    int so;                             //start state
    int cardF;                          //number of final states
    int cardA;                          //number of terminals
    char A[MAXLETTER];                  //alphabet
    int* F;                             //array: final states

    int* class;                         //each node belongs to a "class of equivalence"
    int classNumber=2;                  //number of classes

    struct Partition** partitionList;   //partition to be refined
    int partitionListSize;              //number of partitions

    FILE* fp;                           //input file [see instructions]

    /**Input parsing: read DFA from FILENAME*/
    fp=fopen(FILENAME, "r");
    
    fscanf(fp,"%d %d",&N,&M);
    class=(int*)malloc(N*sizeof(int));
    classTmp=(int*)malloc(N*sizeof(int));

    fscanf(fp, "%d", &so);
    fscanf(fp, "%d", &cardF);
    F=(int*)malloc(cardF*sizeof(int));

    //Initial partitions: B0={Final states} B1={Not final states}
    partitionList = (struct Partition**) malloc(N*sizeof(struct Partition*));
    partitionListSize=2;
    partitionList[0]=(struct Partition*) malloc(sizeof(struct Partition));
    partitionList[0]->card=0;
    partitionList[0]->head=NULL;
    partitionList[1]=(struct Partition*) malloc(sizeof(struct Partition));
    partitionList[1]->card=0;
    partitionList[1]->head=NULL;

    for(i=0; i<cardF; i++){     //read final states
        fscanf(fp, "%d", &F[i]);
        class[F[i]]=0;  //set final states' class to 0
        addPartitionElement(partitionList[0], F[i]);
        partitionList[0]->card+=1;
    }
    partitionList[0]->master=partitionList[0]->head->value;

    for(i=0; i<(N-cardF); i++){ //read not-final states
        fscanf(fp, "%d", &tmpState);
        class[tmpState]=1;  //set not final states' class to 1
        addPartitionElement(partitionList[1], tmpState);
        partitionList[1]->card+=1;
    }
    partitionList[1]->master=partitionList[1]->head->value;

    fscanf(fp, "%d", &cardA);   //number of terminals

    for(i=0; i<cardA; i++){     //read alphabet letter
        fscanf(fp, "%*c");
        fscanf(fp, "%c", &A[i]);
    }
    
    //Graph initialization
    graph=(struct Graph*) malloc(sizeof(struct Graph));
    graph->V=N;
    graph->adjList=(struct AdjList*) malloc(N*sizeof(struct AdjList));

    for(i=0; i<N; i++){
        graph->adjList[i].head=NULL;
    }

    for(i=0; i<M; i++){
        fscanf(fp, "%d %d %c", &from, &to, &label);
        addEdge(graph, from, to, label);
        graph->adjList[from].edgeLables[label-97]=to;
    }
    
    fclose(fp);
    /**---*/

    /**Debug: print the graph*/
    /*
    printGraph(graph);

    printf("\ns0: %d\n---\n", so);
    printf("Final states: \n");
    for(i=0; i<cardF; i++){
        printf("%d\n", F[i]);
    }
    */
    /**---*/

    /**DFA minimization*/
    canSplit=true;
    while(canSplit){    //the algorithm continue until it is possible to split some partition
        canSplit=false;
        for(i=0; i<partitionListSize; i++){
            partitionList[partitionListSize]=(struct Partition*) malloc(sizeof(struct Partition));
            partitionList[partitionListSize]->card=0;
            partitionList[partitionListSize]->head=NULL;
            
            master=partitionList[i]->master;

            elemPartition = partitionList[i]->head; //iterate through all partition elements
            while(elemPartition!=NULL && !canSplit){
                int nodeNumber=elemPartition->value;
                if(class[master]==class[nodeNumber]){   //nodeNumber still belongs to master's partition?
                    for(j=0; j<cardA; j++){
                        masterDest=class[graph->adjList[master].edgeLables[A[j]-97]];   //master destination through letter A[j]

                        if(class[graph->adjList[nodeNumber].edgeLables[A[j]-97]] != masterDest){  //nodeNumber and Partition's master are not equivalent
                            canSplit=true;
                            
                            targetClass=class[graph->adjList[nodeNumber].edgeLables[A[j]-97]];
                            targetLetter=A[j];

                            //Take a picture of class and store it in classTmp
                            for(k=0; k<N; k++){
                                classTmp[k]=class[k];
                            }

                            //Add element to new partition
                            partitionList[partitionListSize]->card+=1;
                            addPartitionElement(partitionList[partitionListSize], nodeNumber);
                            class[nodeNumber]=classNumber;

                            //Bring in the same partition all the elements that for targetLetter reaches targetClass
                            elemPartition1 = partitionList[i]->head; //iterate through all partition elements
                            while(elemPartition1!=NULL){
                                int nodeNumber1=elemPartition1->value;

                                if(nodeNumber1!=master && nodeNumber1!=nodeNumber){    //there is no need to check master behaviour and there is no need to check nodeNumber with itself
                                    if(classTmp[master]==classTmp[nodeNumber1]){   //nodeNumber still belongs to master's partition?
                                        if(classTmp[graph->adjList[nodeNumber1].edgeLables[targetLetter-97]] == targetClass){
                                            partitionList[partitionListSize]->card+=1;
                                            addPartitionElement(partitionList[partitionListSize], nodeNumber1);
                                            class[nodeNumber1]=classNumber;
                                        }
                                    }
                                }
                                elemPartition1=elemPartition1->next;     
                            }
                            break;
                        }
                    }
                }
                elemPartition=elemPartition->next;
            }

            //If a new partition has been filled with some values --> update partitionListSize
            if(partitionList[partitionListSize]->card>0){
                partitionList[partitionListSize]->master=partitionList[partitionListSize]->head->value;
                partitionListSize++;
                classNumber++;
            }
        }
    }
    /**---*/

    //Final step: print the graph in output.txt
    fp=fopen(OUTPUT, "w");
    
    for(i=0; i<partitionListSize; i++){
        fprintf(fp,"PARTITION[%d]\n{\n", i);
        struct ElemPartition* elemPartition = partitionList[i]->head;
        while(elemPartition!=NULL){
            if(class[elemPartition->value]==class[partitionList[i]->master]){
                fprintf(fp,"%d\n", elemPartition->value);
            }
            elemPartition=elemPartition->next;
        }
        fprintf(fp,"}\n");
    }

    fclose(fp);
    return 0;
}