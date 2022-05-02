#ifndef STACK_H
#define STACK_H

/**Description: */
/*
    Array implementation of Stack S.
    The structure contains elements of type StatePair (defined in this file).
    This type is used to represent pair of states {p, q}.
    These are the kind of elements pushed and popped from stack S.
*/
/**---*/

/**StatePair definition and methods*/
struct StatePair{
    int p;
    int q;
};
typedef struct StatePair StatePair;
/**
 * @brief 
 * Check if pair of states p1 is equal to pair of states p2
 * 
 * @param p1 first pair
 * @param p2 second pair
 */
bool isEqual(StatePair* p1, StatePair* p2);

/**
 * @brief Print the pair of states
 */
void printPair(StatePair* pair);
/**---*/


/**Stack*/
struct Stack {
    int top;
    int capacity;
    StatePair* array;
};

/**
 * @brief Create a Stack object
 * 
 * @param _size : dimensione dello stack
 * @return struct Stack* 
 */
struct Stack* createStack(int _size);

/**
 * @brief Check if the stack is empty
 */
bool StackIsEmpty(struct Stack* stack);

/**
 * @brief Check if the stack is full
 */
bool StackIsFull(struct Stack* stack);

/**
 * @brief Push an element into the stack
 * 
 * @param stack : stack pointer
 * @param elem : element to insert
 */
void Push(struct Stack* stack, StatePair elem);

/**
 * @brief Pop an element from the stack
 * 
 * @param stack : stack pointer
 */
StatePair* Pop(struct Stack* stack);

/**
 * @brief Print the stack content
 */
void PrintStack(struct Stack* stack);

/**
 * @brief Returns true iff param stack contains param elem
 */
bool StackContains(struct Stack* stack, StatePair* elem);

/**
 * @brief
 * If param stack contains param elem --> return index of param elem in the array
 * else return -1 
 */
int StackIndex(struct Stack* stack, StatePair* elem);
/**...*/
#endif
