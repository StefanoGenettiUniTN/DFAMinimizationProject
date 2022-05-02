#ifndef LIST_H
#define LIST_H

/**Description: */
/*
    The data structure named P in the pseudocode is actually implemented
    as a list of lists.

    PDataStructure --> a list of lists (PList)
    PList --> a list of pair of states (PStatePair)
    PStatePair --> a pair of state {p,q} with a pointer to the next element of the list
*/
/**---*/

struct PStatePair{
    int p;
    int q;
    struct PStatePair* next;
};

struct PList{
    int length;
    struct PStatePair* head;
    struct PStatePair* tail;
};

struct PDataStructure{
    int size;  //number of lists
    struct PList* lists;
};

/*Add a pair of state to list number param level
    Parameters:
        -P: target P data structure
        -state1, state2: pair of states
        -level: number of the target list
*/
void addPair(struct PDataStructure* P, int state1, int state2, int level);

/**
 * @brief
 * If param P contains param {state1, state2} --> return list number of param {state1, state2}
 * else return -1  
 */
int PIndex(struct PDataStructure* P, int state1, int state2);

/**
 * @brief Add to level1 list elements of level2 list
 */
void LevelUnion(struct PDataStructure* P, int level1, int level2);

/**
 * @brief Deletes all the elements stored in list number level
 */
void resetLevel(struct PDataStructure* P, int level);

#endif
