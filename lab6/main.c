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
    int selected_one = 0;
    for (Node *i = current_word; i != NULL; i = next_word(i)) {
        for (Node *j = next_word(i); j != NULL; j = next_word(j)) {
            if (compareWords(i, j)) {
//                if (!selected_one) {swap_words(list, list->head, i); selected_one = 1;}
//                swap_words(list, next_word(i), j);
                break;
            }
        }

    }

    for (Node *i = list->head; i != NULL; i = i->next) {
        printf("%c", i->data);
        free(i->prev);
    }
    free(list->tail);
    free(list);
}