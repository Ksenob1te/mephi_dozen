//
// Created by Ksenob1te on 27.04.2023.
//

#include "table.h"
#include "string.h"

Table * create_table(ull msize) {
    Table *table = malloc(sizeof(Table));
    table->msize = msize;
    table->keys = malloc(sizeof(KeySpace) * msize);
    for (int i = 0; i < msize; i++) {
        KeySpace *key = (table->keys) + i;
        key->busy = 0;
        key->key = NULL;
        key->info = -1;
    }
    table->cur_size = 0;
    return table;
}



ull str_linear_hash(const char *key, ull module) {
    ull result = 0;
    for (int i = 0, el = (int) key[0]; el != '\0'; i++, el = (int) key[i]) {
        result += el;
    }
    return result % module;
}

int insert_element(Table *table, char *key, ull info) {
    ull field_hash = str_linear_hash(key, table->msize);
    KeySpace *keys = table->keys;
    ull counter = 0;
    while (keys[field_hash].busy > 0 && counter < table->msize) {
        if (strcmp(keys[field_hash].key, key) == 0) return 2;
        field_hash = (field_hash + MIXING_STEP) % table->msize;
        counter++;
    }
    if (counter < table->msize) {
        if (keys[field_hash].busy == -1) free(keys[field_hash].key);
        keys[field_hash].busy = 1;
        keys[field_hash].key = key;
        keys[field_hash].info = info;
        return 0;
    }
    return 1;
}

KeySpace * find_element(Table *table, const char *key) {
    ull field_hash = str_linear_hash(key, table->msize);
    KeySpace *keys = table->keys;
    ull counter = 0;
    while (abs(keys[field_hash].busy) != 0 && counter < table->msize) {
        if (keys[field_hash].busy == 1 && strcmp(keys[field_hash].key, key) == 0)
            return (keys + field_hash);
        field_hash = (field_hash + MIXING_STEP) % table->msize;
        counter++;
    }
    return NULL;
}

int remove_element(Table *table, const char *key) {
    KeySpace *keyspace = find_element(table, key);
    if (keyspace) {
        keyspace->busy = -1;
        return 0;
    }
    return 1;
}

void clear_table(Table *table) {
    for (int i = 0; i < table->msize; i++) {
        KeySpace current = (table->keys)[i];
        free(current.key);
    }
    free(table->keys);
    free(table);
}

