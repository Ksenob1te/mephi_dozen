#ifndef SEM1_LAB4_TASK_H
#define SEM1_LAB4_TASK_H
#include "../structs/task.h"

void joinTerminal(Terminal *terminal, Node *node);
Node * leaveTerminal(Terminal *terminal);
Terminal * selectTerminal(Terminal **array, int len);
void printStatus(Terminal **array, int len);
int scanN(int *n);
int handleTask(Queue* queue, Terminal **array, int n);
Terminal ** initTerminals(int n);

#endif //SEM1_LAB4_TASK_H
