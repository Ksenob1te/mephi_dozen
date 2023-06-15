#ifndef SEM1_LAB4_REMOVAL_LIST_H
#define SEM1_LAB4_REMOVAL_LIST_H

typedef struct RemovalNode {
    long offset;
    struct RemovalNode *next;
} RemovalNode;

typedef struct RemovalList {
    RemovalNode *head;
} RemovalList;

#endif //SEM1_LAB4_REMOVAL_LIST_H
