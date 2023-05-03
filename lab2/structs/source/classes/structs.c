#include "../../structs.h"
#include "../list/doubleList.h"

// Stack struct methods
// ===============================
Stack* createStack() {
    Stack *stack = malloc(sizeof(Stack));
    stack->list = createList(0);
    stack->get_top = get_top_stack;
    stack->pop = pop_stack;
    stack->push = push_stack;
    return stack;
}

Node * get_top_stack (Stack *stack) {
    if (!stack->list) return NULL;
    return stack->list->head;
}

void push_stack(Stack *stack, Node *node) {
    List *list = stack->list;
    add_prev(list, list->head, node);
}

Node * pop_stack(Stack *stack) {
    List *list = stack->list;
    Node *node = list->head;
    list->remove(list, node);
    return node;
}
// ===============================


// Queue struct methods
// ===============================
Queue * createQueue(size_t size) {
    Queue *queue = malloc(sizeof(Queue));
    queue->list = createList(size);
    queue->get_top = get_top_queue;
    queue->pop = pop_queue;
    queue->push = push_queue;
    return queue;
}

Node * get_top_queue(Queue *queue) {
    if (!queue->list) return NULL;
    return queue->list->head;
}

int push_queue(Queue *queue, Node *node) {
    List *list = queue->list;
    list->add_next(list, list->tail, node);
    return 1;
}

Node * pop_queue(Queue *queue) {
    List *list = queue->list;
    Node *node = list->head;
    list->remove(list, node);
    return node;
}
// ===============================


// Deque struct methods
// ===============================
Deque * createDeque() {
    Deque *deque = malloc(sizeof(Deque));
    deque->list = createList(0);
    deque->get_top = get_top_deque;
    deque->get_bottom = get_bottom_deque;
    deque->push_back = push_back_deque;
    deque->push_front = push_front_deque;
    deque->pop_back = pop_back_deque;
    deque->pop_front = pop_front_deque;
    return deque;
}

Node * get_top_deque(Deque *deque) {
    if (!deque->list) return NULL;
    return deque->list->head;
}

Node * get_bottom_deque(Deque *deque) {
    if (!deque->list) return NULL;
    return deque->list->tail;
}

void push_back_deque(Deque *deque, Node *node) {
    List *list = deque->list;
    add_next(list, list->tail, node);
}

void push_front_deque(Deque *deque, Node *node) {
    List *list = deque->list;
    add_prev(list, list->head, node);
}

Node * pop_back_deque(Deque *deque) {
    List *list = deque->list;
    Node *node = list->tail;
    list->remove(list, node);
    return node;
}

Node * pop_front_deque(Deque *deque) {
    List *list = deque->list;
    Node *node = list->head;
    list->remove(list, node);
    return node;
}
// ===============================
