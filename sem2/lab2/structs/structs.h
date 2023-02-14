#ifndef SEM1_LAB4_STRUCTS_H
#define SEM1_LAB4_STRUCTS_H
#include "list.h"

// Stack struct
// ===============================
typedef struct Stack {
    List *list;
    Node * (*get_top) (struct Stack *stack);
    void (*push)(struct Stack *stack, Node *node);
    Node * (*pop)(struct Stack *stack);
} Stack;

Stack* createStack();
Node * get_top_stack (Stack *stack);
void push_stack(Stack *stack, Node *node);
Node* pop_stack(Stack *stack);
// ===============================


// Queue struct
// ===============================
typedef struct Queue {
    List *list;
    Node * (*get_top) (struct Queue *queue);
    void (*push)(struct Queue *queue, Node *node);
    Node * (*pop)(struct Queue *queue);
} Queue;

Queue* createQueue();
Node * get_top_queue (Queue *queue);
void push_queue(Queue *queue, Node *node);
Node * pop_queue(Queue *queue);
// ===============================


// Deque struct
// ===============================
typedef struct Deque {
    List *list;
    Node * (*get_top) (struct Deque *deque);
    Node * (*get_bottom) (struct Deque *deque);
    void (*push_back)(struct Deque *deque, Node *node);
    void (*push_front)(struct Deque *deque, Node *node);
    Node * (*pop_front)(struct Deque *deque);
    Node * (*pop_back)(struct Deque *deque);
} Deque;

Deque* createDeque();
Node * get_top_deque (Deque *deque);
Node * get_bottom_deque (Deque *deque);
void push_back_deque(Deque *deque, Node *node);
void push_front_deque(Deque *deque, Node *node);
Node * pop_front_deque(Deque *deque);
Node * pop_back_deque(Deque *deque);
// ===============================

#endif //SEM1_LAB4_STRUCTS_H
