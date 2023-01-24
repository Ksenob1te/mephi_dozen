#include "stdio.h"
#include "struct.h"
#include "stdlib.h"

int main() {
    char temp = (char) getchar();
    List *list = initList();
    while (temp != EOF) {
        addNext(list, temp);
        temp = (char) getchar();
    }

    Node *current_word = list->head;
    printf("%c", next_word(current_word)->data);

    for (Node *i = list->head; i != NULL; i = i->next) {
        printf("%c", i->data);
        free(i->prev);
    }
    free(list->tail);
    free(list);
}