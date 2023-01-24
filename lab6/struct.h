#ifndef LAB4_STRUCT_H
#define LAB4_STRUCT_H

typedef struct Node {
    char data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
} List;

List *initList();
void swap(Node* node1, Node* node2);
void swap_words(List *list, Node* word1, Node* word2);
void addNext(List *list, char element);
Node * next_word(Node *word);
int compareWords(Node *word1, Node *word2);

#endif //LAB4_STRUCT_H
