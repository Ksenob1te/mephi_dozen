#include "arrayList.h"
#include "../../list.h"

Node * get_head(List *list) {
    return *(list->array);
}
Node * get_tail(List *list) {
    return (list->array)[list->current_size];
}
void * get_data(Node *node) {
    return node->data;
}
int is_last(List *list, Node *node) {
    if (get_tail(list) == node) return 1;
    return 0;
}
Node * createNode(void *data, size_t sizeOfData);
List * createList();
