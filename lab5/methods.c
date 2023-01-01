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

int convertInt(const char *str) {
    int k = 0;
    for (int i = 0; str[i]; ++i) {
        k *= 10;
        k += (int)(str[i] - '0');
    }
    return k;
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

void swap(void *a, void *b, size_t len) {
    unsigned char *p = a, *q = b, tmp;
    for (size_t i = 0; i != len; ++i) {
        tmp = p[i];
        p[i] = q[i];
        q[i] = tmp;
    }
}

void set(void *a, void *b, size_t len) {
    unsigned char *p = a, *q = b;
    for (size_t i = 0; i != len; ++i)
        p[i] = q[i];
}


void bubbleSort(void *arr, int len, size_t sizeofElement, int (*comp)()) {
    for (int i = 0; i < len - 1; i++)
        for (int j = 0; j < len - i - 1; j++)
            if (comp(arr + j * sizeofElement, arr + (j + 1) * sizeofElement, sizeofElement) > 0)
                swap(arr + j * sizeofElement, arr + (j + 1) * sizeofElement, sizeofElement);
}

void pairInsertionSort(void *arr, int len, size_t sizeofElement, int (*comp)()) {
            int left = 0, right = len - 1;
            for (int i = left; ++left <= right; i = ++left) {
                void *arr_1 = malloc(sizeofElement), *arr_2 = malloc(sizeofElement);
                memcpy(arr_1, arr + i * sizeofElement, sizeofElement);
                memcpy(arr_2, arr + left * sizeofElement, sizeofElement);

                if (comp(arr_1, arr_2, sizeofElement) < 0)
                    swap(arr_1, arr_2, sizeofElement);

                while ((--i >= 0) && comp(arr_1, arr + i * sizeofElement) < 0) {
                    set(arr + (i + 2) * sizeofElement, arr + i * sizeofElement, sizeofElement);
                }

                set(arr + (++i + 1) * sizeofElement, arr_1, sizeofElement);
//        printf("%s %s\n", ((struct Voter*) (arr + (i + 1) * sizeofElement))->place, ((struct Voter*) arr_2)->place);

                while ((--i >= 0) && comp(arr_2, arr + i * sizeofElement) < 0) {
            set(arr + (i + 1) * sizeofElement, arr + i * sizeofElement, sizeofElement);
        }
        set(arr + (i + 1) * sizeofElement, arr_2, sizeofElement);
        free(arr_1);
        free(arr_2);
    }
    void *last = malloc(sizeofElement);
    memcpy(last, arr + right * sizeofElement, sizeofElement);
    while ((--right >= 0) && comp(last, arr + right * sizeofElement) < 0) {
        set(arr + (right + 1) * sizeofElement, arr + right * sizeofElement, sizeofElement);
    }
    set(arr + (right + 1) * sizeofElement, last, sizeofElement);
    free(last);
}


struct Voter generateRandom() {
    char *place = malloc(8 * sizeof(char));
    place[0] = (char)('A' + (rand() % 26));
    place[1] = (char)('A' + (rand() % 26));
    place[2] = (char)('A' + (rand() % 26));
    place[3] = '-';
    place[4] = (char)('0' + (rand() % 10));
    place[5] = (char)('0' + (rand() % 10));
    place[6] = (char)('0' + (rand() % 10));
    place[7] = '\0';

    char *name = malloc(4 * sizeof(char));
    name[0] = (char)('A' + (rand() % 26));
    name[1] = (char)('A' + (rand() % 26));
    name[2] = (char)('A' + (rand() % 26));
    name[3] = '\0';

    char *age = malloc(3 * sizeof(char));
    age[0] = (char)('0' + (rand() % 10));
    age[1] = (char)('0' + (rand() % 10));
    age[2] = '\0';

    return Voter.new(name, place, age);
}
