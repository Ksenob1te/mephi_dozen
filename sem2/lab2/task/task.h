#ifndef SEM1_LAB4_TASK_H
#define SEM1_LAB4_TASK_H
#include "../structs/task.h"

void joinTerminal(Terminal *terminal, Node *node);
Node * leaveTerminal(Terminal *terminal);
Terminal * selectTerminal(Terminal **array, int len);
void printStatus(Terminal **array, int len);

#endif //SEM1_LAB4_TASK_H
