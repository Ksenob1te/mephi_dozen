#include "stdio.h"
#include "struct.h"
#include "stdlib.h"

int main() {
    char temp = (char) getchar();
    List *list = initList();
    while (temp != '0') {
        addNext(list, temp);
        temp = (char) getchar();
    }

    Node *current_word = list->head;
    Node *selected_last = NULL;
    for (Node *i = current_word; i != NULL; i = next_word(i)) {
        for (Node *j = next_word(i); j != NULL; j = next_word(j)) {
            if (compareWords(i, j)) {
                if (!selected_last) swap_words(list, list->head, i);
                else swap_words(list, next_word(selected_last), i);
                swap_words(list, next_word(i), j);
                selected_last = j;
                break;
            }
        }

    }
    printf("\nResult:\n");
    for (Node *i = list->head; i != NULL; i = i->next) {
        printf("%c", i->data);
        free(i->prev);
    }
    free(list->tail);
    free(list);
    printf("\n");
}