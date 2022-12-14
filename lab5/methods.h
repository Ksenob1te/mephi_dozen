#ifndef MEPHI_DOZEN_METHODS_H
#define MEPHI_DOZEN_METHODS_H

#include "stdio.h"

char *freadline(FILE *file);
int checkPlace(char *str);
int checkAge(char *str);
int convertInt(const char *str);

int usernameComparatorInc(const void *p1, const void *p2);
int usernameComparatorDec(const void *p1, const void *p2);
int placeComparatorInc(const void *p1, const void *p2);
int placeComparatorDec(const void *p1, const void *p2);
int ageComparatorInc(const void *p1, const void *p2);
int ageComparatorDec(const void *p1, const void *p2);

void bubbleSort(void *arr, int len, size_t sizeofElement, int (*comp)());
void pairInsertionSort(void *arr, int len, size_t sizeofElement, int (*comp)());
void set(void *a, void *b, size_t len);
struct Voter generateRandom();

#endif //MEPHI_DOZEN_METHODS_H
