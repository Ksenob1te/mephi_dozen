#ifndef MEPHI_DOZEN_METHODS_H
#define MEPHI_DOZEN_METHODS_H

int check_phone(const char *phone);
int check_number(const char *time);
int (*get_comparator(int field, int reverse)) (const void *, const void *);
void swap(void *a, void *b, size_t len);

#endif
