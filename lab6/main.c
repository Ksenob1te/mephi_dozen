#include "stdio.h"
#include "struct.h"

int main() {
    char temp = (char) getchar();
    List *list = initList();
    while (temp != EOF) {
        addNext(list, temp);
        temp = (char) getchar();
    }
    for (Node *i = list->head; i->next != NULL; i = i->next) {
        printf("%c", i->data);
    }
}