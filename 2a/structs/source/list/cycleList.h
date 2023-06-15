#ifndef MEPHI_DOZEN_CYCLELIST_H
#define MEPHI_DOZEN_CYCLELIST_H
#include "stdlib.h"

struct Node {
    void *data;
    size_t sizeOfData;
    struct Node *next;
};

struct List {
    struct Node *tail;
};

#endif //MEPHI_DOZEN_CYCLELIST_H
