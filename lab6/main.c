#include "stdio.h"
#include "struct.h"

int main() {
    char temp = (char) getchar();
    List *list = initList();
    while (temp != EOF) {
        addNext(list, temp);
        temp = (char) getchar();
        if (temp == EOF) break;
        printf("data: %c\n", temp);
    }
}