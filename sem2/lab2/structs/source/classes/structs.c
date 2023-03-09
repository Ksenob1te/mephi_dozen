#include "../../structs.h"

// Stack struct methods
// ===============================
Stack* createStack() {
    Stack *stack = malloc(sizeof(Stack));
    stack->list = createList();
    stack->get_top = get_top_stack;
    stack->pop = pop_stack;
    stack->push = push_stack;
    return stack;
}

Node * get_top_stack (Stack *stack) {
    return get_head(stack->list);
}

void push_stack(Stack *stack, Node *node) {
    List *list = stack->list;
    add_prev(list, get_head(list), node);
}

Node * pop_stack(Stack *stack) {
    List *list = stack->list;
    Node *node = get_head(list);
    remove_selected(list, node);
    return node;
}
// ===============================


// Queue struct methods
// ===============================
Queue * createQueue() {
    Queue *queue = malloc(sizeof(Queue));
    queue->list = createList();
    queue->get_top = get_top_queue;
    queue->pop = pop_queue;
    queue->push = push_queue;
    queue->is_full = is_full_queue;
    return queue;
}

int is_full_queue(Queue *queue) {
    return 0;
}

Node * get_top_queue(Queue *queue) {
    return get_head(queue->list);
}

void push_queue(Queue *queue, Node *node) {
    List *list = queue->list;
    add_next(list, get_tail(list), node);
}

Node * pop_queue(Queue *queue) {
    List *list = queue->list;
    Node *node = get_head(list);
    remove_selected(list, node);
    return node;
}
// ===============================


// Deque struct methods
// ===============================
Deque * createDeque() {
    Deque *deque = malloc(sizeof(Deque));
    deque->list = createList();
    deque->get_top = get_top_deque;
    deque->get_bottom = get_bottom_deque;
    deque->push_back = push_back_deque;
    deque->push_front = push_front_deque;
    deque->pop_back = pop_back_deque;
    deque->pop_front = pop_front_deque;
    return deque;
}

Node * get_top_deque(Deque *deque) {
    return get_head(deque->list);
}

Node * get_bottom_deque(Deque *deque) {
    return get_tail(deque->list);
}

void push_back_deque(Deque *deque, Node *node) {
    List *list = deque->list;
    add_next(list, get_tail(list), node);
}

void push_front_deque(Deque *deque, Node *node) {
    List *list = deque->list;
    add_prev(list, get_head(list), node);
}

Node * pop_back_deque(Deque *deque) {
    List *list = deque->list;
    Node *node = get_tail(list);
    remove_selected(list, node);
    return node;
}

Node * pop_front_deque(Deque *deque) {
    List *list = deque->list;
    Node *node = get_head(list);
    remove_selected(list, node);
    return node;
}
// ===============================
