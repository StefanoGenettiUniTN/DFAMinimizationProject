#ifndef MFSET_H
#define MFSET_H

/**Description: */
/*
    Merge find set data structure implemented with lists and weight heuristic
*/
/**---*/

struct SetElement{
    int val;
    struct SetElement* next;
    int root;    //represents the set to which val belongs and may be val itself
};

struct SetList{
    int length;
    bool isActive;  //isActive=1 the list is still a set ; isActive=0 means that this list has been merged with another list
    struct SetElement* head;
    struct SetElement* tail;
};

struct MfSet{
    int size;  //number of lists
    struct SetList* lists;
};

/**
 * @brief Create n components {1},...,{n}
 */
void MfsetInitialization(struct MfSet* set, int n);

/**
 * @brief Returns the root node of component x
 */
int find(struct MfSet* set, int x);

/**
 * @brief Merge components x and y
 * @param x root element of first set
 * @param y root element of a second set
 */
void merge(struct MfSet* set,int x,int y);

#endif
