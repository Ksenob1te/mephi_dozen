
#ifndef MEPHI_DOZEN_TABLE_H
#define MEPHI_DOZEN_TABLE_H
#include "stdlib.h"
#include "stdio.h"

#define ull unsigned long long
#define MIXING_STEP 1


typedef struct KeySpace {
    int busy;
    char *key;
    ull info;
} KeySpace;

typedef struct Table {
    KeySpace *keys;
    ull msize;
    ull cur_size;
} Table;

//KeySpace * create_keyspace() {
//    KeySpace *key = malloc(sizeof(KeySpace));
//    key->busy = 0;
//    key->key = NULL;
//    key->info = -1;
//    return key;
//}

Table * create_table(ull msize);


ull str_linear_hash(const char *key, ull module);
int insert_element(Table *table, char *key, ull info);

KeySpace * find_element(Table *table, const char *key);
int remove_element(Table *table, const char *key);

void clear_table(Table *table);


#endif //MEPHI_DOZEN_TABLE_H
