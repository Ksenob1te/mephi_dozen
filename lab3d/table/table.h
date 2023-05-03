
#ifndef MEPHI_DOZEN_TABLE_H
#define MEPHI_DOZEN_TABLE_H
#include "stdlib.h"
#include "stdio.h"

#define ull unsigned long long
#define MIXING_STEP 1
#define TABLE_SIZE 10
#define BLOCK_SIZE (sizeof(long) + sizeof(ull) + sizeof(int))
#define DEFAULT_OFFSET sizeof(long)


// file struct:
// _______ {file_name}_table.tmp _______
// _msize_ {_busy_ _key_ptr_ _info_} for i in _msize_
// _____________________________________
//
// _______ {file_name}_keys.tmp ________
// just write keys at the end
// _____________________________________

typedef struct KeySpace {
    int busy;
    long key_offset;
    ull info;
} KeySpace;

typedef struct Table {
    char *file_name;
    long msize;
} Table;

//KeySpace * create_keyspace() {
//    KeySpace *key = malloc(sizeof(KeySpace));
//    key->busy = 0;
//    key->key = NULL;
//    key->info = -1;
//    return key;
//}

Table * create_table(char *file_name);


long str_linear_hash(const char *key, long module);
int insert_element(Table *table, char *key, ull info);

long find_element(Table *table, const char *key, KeySpace* result);
int remove_element(Table *table, const char *key);

void clear_table(Table *table);


#endif //MEPHI_DOZEN_TABLE_H
