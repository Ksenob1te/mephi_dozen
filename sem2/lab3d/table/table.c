//
// Created by Ksenob1te on 27.04.2023.
//

#include "table.h"
#include "string.h"
#include "stdlib.h"
#include "../file_worker/manager.h"

void init_table(Table *table) {
    char str[1000] = "tmp/";
    strcat(str, table->file_name);
    strcat(str, "_table.tmp");
    FILE *file = fopen(str, "a+b");
    fwrite(&(table->msize), sizeof(long), 1, file);
    KeySpace key = {0, -1, 0};
    for (long i = 0; i < table->msize; i++) {
        write_keyspace(key, i, file);
    }
    fclose(file);
}

Table * create_table(char *file_name) {
    char str[1000] = "tmp/";
    strcat(str, file_name);
    strcat(str, "_table.tmp");
    FILE *file = fopen(str, "ab+");
    fseek(file, 0, SEEK_SET);

    char full_keyspace_name[1000] = "tmp/";
    strcat(full_keyspace_name, file_name);
    strcat(full_keyspace_name, "_keys.tmp");
    fopen(full_keyspace_name, "a+b");

    long msize;
    ull status = fread(&msize, sizeof(long), 1, file);
    if (!status)
        msize = TABLE_SIZE;
    Table *table = malloc(sizeof(Table));
    table->msize = msize;
    table->file_name = file_name;
    fclose(file);
    if (!status)
        init_table(table);
    return table;
}

long str_linear_hash(const char *key, long module) {
    long result = 0;
    for (int i = 0, el = (int) key[0]; el != '\0'; i++, el = (int) key[i]) {
        result += el;
    }
    return result % module;
}

int insert_element(Table *table, char *key, ull info) {
    char *file_name = table->file_name;
    char full_table_name[1000] = "tmp/";
    strcat(full_table_name, file_name);
    strcat(full_table_name, "_table.tmp");
    FILE *file = fopen(full_table_name, "r+b");

    char full_keyspace_name[1000] = "tmp/";
    strcat(full_keyspace_name, file_name);
    strcat(full_keyspace_name, "_keys.tmp");
    FILE *file_keys = fopen(full_keyspace_name, "a+b");

    long field_hash = str_linear_hash(key, table->msize);
    KeySpace keyspace = read_keyspace(field_hash, file);
    long counter = 0;
    while (keyspace.busy > 0 && counter < table->msize) {
        char *current_key = read_key(keyspace.key_offset, file_keys);
        if (strcmp(current_key, key) == 0)  {
            free(current_key);
            fclose(file);
            fclose(file_keys);
            return 2;
        }
        field_hash = (field_hash + MIXING_STEP) % table->msize;
        counter++;
        free(current_key);
        keyspace = read_keyspace(field_hash, file);
    }
    if (counter < table->msize) {
        keyspace.busy = 1;
        keyspace.key_offset = write_key(key, file_keys);
        keyspace.info = info;
        write_keyspace(keyspace, field_hash, file);
        fclose(file);
        fclose(file_keys);
        return 0;
    }
    fclose(file);
    fclose(file_keys);
    return 1;
}

long find_element(Table *table, const char *key, KeySpace* result) {
    char *file_name = table->file_name;
    char full_table_name[1000] = "tmp/";
    strcat(full_table_name, file_name);
    strcat(full_table_name, "_table.tmp");
    FILE *file = fopen(full_table_name, "rb");

    char full_keyspace_name[1000] = "tmp/";
    strcat(full_keyspace_name, file_name);
    strcat(full_keyspace_name, "_keys.tmp");
    FILE *file_keys = fopen(full_keyspace_name, "rb");

    long field_hash = str_linear_hash(key, table->msize);
    *result = read_keyspace(field_hash, file);
    long counter = 0;
    while (abs((*result).busy) != 0 && counter < table->msize) {
        char *current_key = read_key((*result).key_offset, file_keys);
        if ((*result).busy == 1 && strcmp(current_key, key) == 0) {
            free(current_key);
            fclose(file);
            fclose(file_keys);
            return field_hash;
        }
        field_hash = (field_hash + MIXING_STEP) % table->msize;
        counter++;
        (*result) = read_keyspace(field_hash, file);
        free(current_key);
    }
    fclose(file);
    fclose(file_keys);
    return -1;
}

int remove_element(Table *table, const char *key) {
    char *file_name = table->file_name;
    char full_table_name[1000] = "tmp/";
    strcat(full_table_name, file_name);
    strcat(full_table_name, "_table.tmp");
    FILE *file = fopen(full_table_name, "r+b");
    KeySpace keyspace;
    int offset = find_element(table, key, &keyspace);
    if (keyspace.key_offset > 0) {
        keyspace.busy = -1;
        write_keyspace(keyspace, offset, file);
        fclose(file);
        return 0;
    }
    fclose(file);
    return 1;
}

void clear_table(Table *table) {
    free(table->file_name);
    free(table);
}

