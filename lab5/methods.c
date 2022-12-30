#include "stdlib.h"
#include "string.h"
#include "methods.h"
#include "ctype.h"
#include "voter.h"

char *freadline(FILE *file) {
    char *ptr = (char *) malloc(sizeof(char));
    char buf[81];
    int n, len = 0, bufLen;
    *ptr = '\0';
    do {
        n = fscanf(file, "%80[^\n]%n", buf, &bufLen);
        if (n < 0) {
            if (len > 0) n = 0;
            else {
                free(ptr);
                return NULL;
            }
        }
        if (n == 0)
            fscanf(file, "%*c");
        else {
            len += bufLen;
            ptr = (char *) realloc(ptr, len + 1);
            strcat(ptr, buf);
        }
    } while (n > 0);
    return ptr;
}

int checkPlace(char *str) {
    if (!str[0] || !isalpha(str[0])) return 1;
    if (!str[1] || !isalpha(str[1])) return 1;
    if (!str[2] || !isalpha(str[2])) return 1;
    if (!str[3] || (str[3] != '-')) return 1;
    if (!str[4] || !isdigit(str[4])) return 1;
    if (!str[5] || !isdigit(str[5])) return 1;
    if (!str[6] || !isdigit(str[6])) return 1;
    if (str[7]) return 1;
    return 0;
}

int checkAge(char *str) {
    for (int i = 0; str[i]; ++i) {
        if (!isdigit(str[i])) return 1;
    }
    return 0;
}

int usernameComparatorInc(const void *p1, const void *p2) {
    char *l = ((struct Voter *) p1)->username;
    char *r = ((struct Voter *) p2)->username;
    return strcmp(l, r);
}

int usernameComparatorDec(const void *p1, const void *p2) {
    char *l = ((struct Voter *) p1)->username;
    char *r = ((struct Voter *) p2)->username;
    return -strcmp(l, r);
}

int placeComparatorInc(const void *p1, const void *p2) {
    char *l = ((struct Voter *) p1)->place;
    char *r = ((struct Voter *) p2)->place;
    return strcmp(l, r);
}

int placeComparatorDec(const void *p1, const void *p2) {
    char *l = ((struct Voter *) p1)->place;
    char *r = ((struct Voter *) p2)->place;
    return -strcmp(l, r);
}

int ageComparatorInc(const void *p1, const void *p2) {
    char *l = ((struct Voter *) p1)->age;
    char *r = ((struct Voter *) p2)->age;
    return strcmp(l, r);
}

int ageComparatorDec(const void *p1, const void *p2) {
    char *l = ((struct Voter *) p1)->age;
    char *r = ((struct Voter *) p2)->age;
    return -strcmp(l, r);
}

void swap(void * a, void * b, size_t len)
{
    unsigned char * p = a, * q = b, tmp;
    for (size_t i = 0; i != len; ++i)
    {
        tmp = p[i];
        p[i] = q[i];
        q[i] = tmp;
    }
}


void bubbleSort(void *arr, int len, int sizeofElement, int (*comp)()) {
    for (int i = 0; i < len - 1; i++)
        for (int j = 0; j < len - i - 1; j++)
            if (comp(arr + j * sizeofElement, arr + (j + 1) * sizeofElement, sizeofElement) > 0)
                swap(arr + j * sizeofElement, arr + (j + 1) * sizeofElement, sizeofElement);
}
