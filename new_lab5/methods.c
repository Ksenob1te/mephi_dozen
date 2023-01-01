#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "abonent.h"


int check_phone(const char *phone) {
    if (phone[0] != '+') return 1;
    int i = 0;
    for (i = 1; phone[i] && i < 16; ++i) {
        if (!isdigit(phone[i]) && phone[i] != ' ') return 1;
    }
    if (phone[i] != '\0') return 1;
    return 0;
}

int check_number(const char *time) {
    for (int i = 0; time[i]; ++i) {
        if (!isdigit(time[i])) return 1;
    }
    return 0;
}

int up_name_comparator(const void *p1, const void *p2) {
    return strcmp(((Abonent *) p1)->name, ((Abonent *) p2)->name);
}

int down_name_comparator(const void *p1, const void *p2) {
    return -strcmp(((Abonent *) p1)->name, ((Abonent *) p2)->name);
}

int up_phone_comparator(const void *p1, const void *p2) {
    const char *l = ((Abonent *) p1)->phone;
    const char *r = ((Abonent *) p2)->phone;
    int i = 0, k = 0;
    for (; l[i] && r[k] && l[i] == r[k];) {
        if (l[i] != ' ') i++;
        if (r[i] != ' ') k++;
    }
    if (!l[i] && !r[k]) return 0;
    if (l[i] < r[k]) return -1;
    else return 1;
}

int down_phone_comparator(const void *p1, const void *p2) {
    const char *l = ((Abonent *) p1)->phone;
    const char *r = ((Abonent *) p2)->phone;
    int i = 0, k = 0;
    for (; l[i] && r[k] && l[i] == r[k];) {
        if (l[i] != ' ') i++;
        if (r[i] != ' ') k++;
    }
    if (!l[i] && !r[k]) return 0;
    if (l[i] < r[k]) return 1;
    else return -1;
}

size_t str_to_size_t(const char *str) {
    size_t ans = 0;
    for (int i = 0; str[i]; ++i) {
        ans *= 10;
        ans += (size_t)(str[i] - '0');
    }
    return ans;
}

int up_time_comparator(const void *p1, const void *p2) {
    size_t l = str_to_size_t(((Abonent *) p1)->time);
    size_t r = str_to_size_t(((Abonent *) p2)->time);
    if (l > r) return 1;
    else if (l == r) return 0;
    else return -1;
}

int down_time_comparator(const void *p1, const void *p2) {
    size_t l = str_to_size_t(((Abonent *) p1)->time);
    size_t r = str_to_size_t(((Abonent *) p2)->time);
    if (l > r) return -1;
    else if (l == r) return 0;
    else return 1;
}

int (*get_comparator(int field, int reverse)) (const void *, const void *) {
    int (*comp)(const void*, const void*);
    if (!reverse) {
        if (field == 0) comp = up_name_comparator;
        if (field == 1) comp = up_phone_comparator;
        if (field == 2) comp = up_time_comparator;
    } else {
        if (field == 0) comp = down_name_comparator;
        if (field == 1) comp = down_phone_comparator;
        if (field == 2) comp = down_time_comparator;
    }
    return comp;
}

void swap(void *a, void *b, size_t len) {
    unsigned char *f = a, *s = b, temp;
    for (size_t i = 0; i != len; ++i) {
        temp = f[i];
        f[i] = s[i];
        s[i] = temp;
    }
}

void shaker_sort(void *array, size_t size, size_t sizeOfElement, int (*comparator)(const void*, const void*)) {
    for (size_t j = 1; j <= size / 2; j++) {
        for (size_t i = j - 1; i < size - j; i++) {
            if (comparator(array + i * sizeOfElement, array + (i + 1) * sizeOfElement) > 0) {
                swap(array + i * sizeOfElement, array + (i + 1) * sizeOfElement, sizeOfElement);
            }
        }

        for (size_t i = size - j - 1; i >= j; i--)
            if (comparator(array + (i - 1) * sizeOfElement, array + i * sizeOfElement) > 0)
                swap(array + i * sizeOfElement, array + (i - 1) * sizeOfElement, sizeOfElement);
    }
}

void shell_sort(void *array, size_t size, size_t sizeOfElement, int (*comparator)(const void*, const void*)) {
    array = realloc(array, (size + 1) * sizeOfElement);
    for (size_t interval = size / 2; interval > 0; interval /= 2) {
        for (size_t i = interval; i < size; i += 1) {
            memmove(array + size * sizeOfElement, array + i * sizeOfElement, sizeOfElement);
            void *temp = array + size * sizeOfElement;
            size_t j;
            for (j = i; j >= interval && comparator(array + (j - interval) * sizeOfElement, temp) > 0; j -= interval) {
                memmove(array + j * sizeOfElement, array + (j - interval) * sizeOfElement, sizeOfElement);
            }
            memmove(array + j * sizeOfElement, temp, sizeOfElement);
        }
    }
}


void (*get_sort(int sort_type))
        (void* arr, size_t size, size_t sizeOfElement, int (*comparator)(const void*, const void*)) {
    if (sort_type == 0) return qsort;
    if (sort_type == 1) return shaker_sort;
    if (sort_type == 2) return shell_sort;
    return qsort;
}

