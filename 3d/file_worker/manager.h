#ifndef SEM1_LAB4_MANAGER_H
#define SEM1_LAB4_MANAGER_H

#include "../table/table.h"

KeySpace read_keyspace(long block_offset, FILE* file);
void write_keyspace(KeySpace key, long block_offset, FILE* file);

char * read_key(long offset, FILE* file);
long write_key(char *key, FILE* file);

#endif //SEM1_LAB4_MANAGER_H
