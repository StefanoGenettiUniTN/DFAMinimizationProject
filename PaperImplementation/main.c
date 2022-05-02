/**
 * DFA minimization - Watson-Daciuk algorithm
 * @author Stefano Genetti (stefano.genetti@studenti.unitn.it)
 * @date Academic year 2021-2022
 */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "common.h"
#include "stack.h"
#include "list.h"
#include "mfset.h"

#define FILENAME "input.txt"
#define OUTPUT "output.txt"

//DFA
int N;                      //number of nodes
int M;                      //number of edges
struct Graph* graph;        //automata
int so;                     //start state
int cardA;                  //number of terminals
char A[MAXLETTER];          //alphabet
int cardF;                  //number of final states
int* F;                     //array: final states

int* class;                 //array: class[i] is the class of state i
int** memoizationTable;     //data structure as a support for memoization (Def_Ineq U Def_Equiv)
struct Stack* S;            //stack to detect cycles

int rl;                     //The variable indicates the level of recursion at which a pair of states can be
                            //found that the current pair depends upon. If S is seen as stack, then variable rl is an
                            //index in that stack, indicating a position of the pair the current pair depends upon.
                            //If the current pair depends on nothing, variable rl is set to |Q|.

int level;                  //Recursion level (number of items in S) for the current pair

int* in;                    //array: in[i] is the in-degree of node i

struct PDataStructure* P;   //P data structure

bool equiv(int p, int q, int k);

int main(int argc, char** argv){
    //Support variables (counters, ecc...)
    int i,j;
    int tmpState;
    struct SetElement* tmpSetElement;
    int from;
    int to;
    char label;    
    int partitionNumber;

    FILE* fp;                   //input file [FILENAME]

    struct MfSet* partitions;   //set of equivalent states
    int rootElement1;
    int rootElement2;

    /**Input parsing: read DFA from FILENAME*/
    fp=fopen(FILENAME, "r");
    
    fscanf(fp,"%d %d",&N,&M);

    class=(int*)malloc(N*sizeof(int));

    memoizationTable=(int**)malloc(N*sizeof(int*));
    for(i=0; i<N; i++) memoizationTable[i] = (int*)malloc(N*sizeof(int));

    fscanf(fp, "%d", &so);
    fscanf(fp, "%d", &cardF);
    F=(int*)malloc(cardF*sizeof(int));

    for(i=0; i<cardF; i++){
        fscanf(fp, "%d", &F[i]);
        class[F[i]]=0;  //set final states' class to 0
    }

    for(i=0; i<(N-cardF); i++){ //set not final states' class to 1
        fscanf(fp, "%d", &tmpState);
        class[tmpState]=1;
    }

    fscanf(fp, "%d", &cardA);

    for(i=0; i<cardA; i++){     //read alphabet letters
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

    in=(int*)malloc(N*sizeof(int));

    for(i=0; i<M; i++){
        fscanf(fp, "%d %d %c", &from, &to, &label);
        addEdge(graph, from, to, label);
        graph->adjList[from].edgeLables[label-97]=to;
        in[to]++;
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
    printf("NODE'S IN-DEGREE\n");
    for(i=0; i<N; i++){
        printf("Deg[%d]: %d\n", i, in[i]);
    }
    */
    /**---*/

    /**Memoization table initialization*/
    // * {p,p}<--TRUE : self-equality
    // * { {p, q} | p in S\F AND q in F}<--FALSE : final states cannot be equivalent to not-final states
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            if(class[i]!=class[j]){
                memoizationTable[i][j]=0;
            }else if(i==j){
                memoizationTable[i][j]=1;
            }else{
                memoizationTable[i][j]=-1;
            }
        }
    }

    /**DFA minimization*/
    /**Initialize variables*/
    rl=0;
    level=0;
    S=createStack(N);

    P=(struct PDataStructure*) malloc(sizeof(struct PDataStructure));
    P->size=N;    //the number of states is the max number of levels in P
    P->lists=(struct PList*) malloc((P->size)*sizeof(struct PList));
    for(i=0; i<N; i++){
        P->lists[i].head=NULL;
        P->lists[i].tail=NULL;
        P->lists[i].length=0;
    }
    /**---*/

    for(i=0; i<N; i++){
        for(j=(i+1); j<N; j++){
            if(memoizationTable[i][j]==-1){    //let p,q : (p,q) in ((QxQ)\(Def_Ineq U Def_Equiv))
                if(equiv(i, j, max((N-2), 0))){
                    memoizationTable[i][j]=1;
                    memoizationTable[j][i]=1;
                }else{
                    memoizationTable[i][j]=0;
                    memoizationTable[j][i]=0;
                }
            }
        }
    }

    //Debug: print final memoization table
    /*
    printf("\n FINAL MEMOIZATION TABLE\n");
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            printf("%d\t", memoizationTable[i][j]);
        }
        printf("\n");
    }
    printf("\n ...end\n\n");
    */
   
    //Merge states according to Def_Equiv
    partitions=(struct MfSet*) malloc(sizeof(struct MfSet));
    MfsetInitialization(partitions, N);

    for(i=0; i<N; i++){
        for(j=(i+1); j<N; j++){
            if(memoizationTable[i][j]==1){
                //Get root element of i and j
                rootElement1=find(partitions, i);
                rootElement2=find(partitions, j);
                
                //If i and j have different roots, they must be merged
                if(rootElement1!=rootElement2){
                    merge(partitions, rootElement1, rootElement2);
                }
            }
        }
    }

    //Final step: print sets of equivalent states in output.txt
    fp=fopen(OUTPUT, "w");
    partitionNumber=0;
    for(i=0; i<N; i++){
        if(partitions->lists[i].isActive){
            fprintf(fp,"PARTITION[%d] - SIZE=%d\n", partitionNumber++, partitions->lists[i].length);
            fprintf(fp,"{\n");
            tmpSetElement = partitions->lists[i].head;
            while(tmpSetElement!=NULL){
                fprintf(fp,"%d\n",tmpSetElement->val);
                tmpSetElement=tmpSetElement->next;
            }
            fprintf(fp,"}\n");
        }
    }
    fclose(fp);
    /**------*/

    return 0;
}

bool equiv(int p, int q, int k){
    bool eq;
    bool pushed=false;

    //Support variables
    int i;
    int tmpRl;
    StatePair pair;
    int rlPrime;
    int pDestination;
    int qDestination;
    struct PStatePair* nextPair;
    int nextPairFirst;  //first state of the pair
    int nextPairSecond; //second state of the pair

    //initialization of the pair {p, q}
    pair.p=p;
    pair.q=q;

    if(p==q){
        eq=true;
    }else if(class[p]!=class[q]){
        eq=false;
    }else if(k==0){
        eq=true;
        rl=0;
    }else if(StackContains(S, &pair)){
        eq=true;
        rl=StackIndex(S, &pair);
    }else if(memoizationTable[p][q]==0){
        eq=false;
    }else if((tmpRl=PIndex(P,p,q))>=0){
        eq=true;
        rl=tmpRl;
    }else{  //...End of memoization        
        if(level==0 || in[p]>1 || in[q]>1){ //add to the stack only pair of states that can start a cycle
            Push(S, pair);
            level=level+1;
            pushed=true;
        }
        rlPrime=N;  //N is the number of nodes~states in the automata (|Q| in the paper pseudocode)
        eq=true;

        for(i=0; i<cardA; i++){ //DFA has total transition function so every node as a transition for every terminal
            pDestination=graph->adjList[p].edgeLables[A[i]-97];
            qDestination=graph->adjList[q].edgeLables[A[i]-97];
            eq = eq && equiv(pDestination, qDestination, k-1);
            rlPrime=(rlPrime<rl) ? rlPrime : rl;    //rlPrime=min(rlPrime, rl)
        }
        rl=rlPrime;
        if(pushed){
            Pop(S);
            level=level-1;
        }
        if(eq){
            if(rl>level){
                //Mark that states p and q will have to be merged
                memoizationTable[p][q]=1;
                memoizationTable[q][p]=1;
            }else{
                addPair(P, p, q, rl);   //P[rl]:=P[rl] U {{p,q}}
            }
        }else{
            //def_Ineq:=Def_Ineq U {{p,q}}
            memoizationTable[p][q]=0;
            memoizationTable[q][p]=0;
        }
        if(rl==level){
            rl=N;   //N is the number of nodes~states in the automata (|Q| in the paper pseudocode)
        }
        if(eq){
            if(rl==N){
                //foreach {r,s} in P[level] mark that states r and s will have to be merged
                nextPair = P->lists[level].head;
                while(nextPair!=NULL){
                    nextPairFirst=nextPair->p;
                    nextPairSecond=nextPair->q;
                    
                    memoizationTable[nextPairFirst][nextPairSecond]=1;
                    memoizationTable[nextPairSecond][nextPairFirst]=1;
                    
                    nextPair=nextPair->next;
                }
            }else{
                //P[rl]=P[rl] U P[level]
                LevelUnion(P, rl, level);
            }
        }else{
            //foreach {r,s} in P[level] Def_Ineq:=Def_Ineq U {{r,s}}
            nextPair = P->lists[level].head;
            while(nextPair!=NULL){
                nextPairFirst=nextPair->p;
                nextPairSecond=nextPair->q;
                
                //memoizationTable[nextPairFirst][nextPairSecond]=0;
                //memoizationTable[nextPairSecond][nextPairFirst]=0;
                
                nextPair=nextPair->next;
            }
        }
        //P[level]:={}
        resetLevel(P, level);
    }
    return eq;
}