#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "stack.h"

/**StatePair*/
bool isEqual(StatePair* p1, StatePair* p2){
    return ((p1->p)==(p2->p) && (p1->q)==(p2->q)) || ((p1->p)==(p2->q) && (p1->q)==(p2->p));
}

void printPair(StatePair* pair){
    printf("{%d, %d}", pair->p, pair->q);
}
/**---*/

/**Stack*/
struct Stack* createStack(int _size)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = _size;
    stack->top = 0;
    stack->array = (StatePair*)malloc(stack->capacity*sizeof(StatePair));
    return stack;
}

bool StackIsEmpty(struct Stack* stack){
    return (stack->top == 0);
}

bool StackIsFull(struct Stack* stack){
    return (stack->top == stack->capacity);
}

void Push(struct Stack* stack, StatePair elem){
    if(StackIsFull(stack)){
        printf("Attempting to add an element to a full stack\n");
        exit(1);
    }
    stack->array[stack->top]=elem;
    stack->top=stack->top+1;
}

StatePair* Pop(struct Stack* stack){
    if(StackIsEmpty(stack)){
        printf("Attempting to remove an element from an empty stack\n");
        exit(1);
    }
    stack->top=stack->top-1;
    return &(stack->array[stack->top]);
}

void PrintStack(struct Stack* stack){
    int i=0;
    if(StackIsEmpty(stack)) printf("Stack is empty\n");
    else{
        for(i=0;i<stack->top;i++){
            printPair(&(stack->array[i]));
            printf("\n");
        }
    }
    printf("End of Stack\n");
}

bool StackContains(struct Stack* stack, StatePair* elem){
    int i=0;
    StatePair* currentStatePair;

    if(!StackIsEmpty(stack)){
        for(i=0;i<stack->top;i++){
            currentStatePair=&(stack->array[i]);
            if(isEqual(currentStatePair, elem)){
                return true;
            }
        }
    }
    return false;
}

int StackIndex(struct Stack* stack, StatePair* elem){
    int i=0;
    StatePair* currentStatePair;

    if(!StackIsEmpty(stack)){
        for(i=0;i<stack->top;i++){
            currentStatePair=&(stack->array[i]);
            if(isEqual(currentStatePair, elem)){
                return i;
            }
        }
    }
    return -1;
}
/**---*/