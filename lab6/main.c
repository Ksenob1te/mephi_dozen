#include "stdio.h"
#include "struct.h"
#include "stdlib.h"

int main() {
    char temp = (char) getchar();
    List *list = initList();
    int checker = 0;
    while (temp != EOF && temp != '\n') {
        if (checker || (temp != ' ' && temp != '\t')) {
            addNext(list, temp);
            checker = 1;
        }
        temp = (char) getchar();
    }
    printf("\nInput string: \"");
    for (Node *i = list->head; i != NULL; i = i->next)
        printf("%c", i->data);
    printf("\"\n");
    Node *current_word = list->head;
    for (Node *i = next_word(current_word); i != NULL; i = next_word(i)) {
        Node *j;
        for (j = i; j && (j->data == ' ' || j->data == '\t');) j = removeEl(list, j);
        i = j;
    }
    Node *selected_last = NULL;
    for (Node *i = current_word; i != NULL; i = next_word(i)) {
        for (Node *j = next_word(i); j != NULL; j = next_word(j)) {
            if (compareWords(i, j)) {
                if (!selected_last) swap_words(list, list->head, i);
                else if (selected_last != i) swap_words(list, next_word(selected_last), i);
                swap_words(list, next_word(i), j);
                selected_last = j;
                break;
            }
        }
    }
    printf("Result string: \"");
    for (Node *i = list->head; i != NULL; i = i->next) {
        printf("%c", i->data);
        free(i->prev);
    }
    free(list->tail);
    free(list);
    printf("\"\n");
}