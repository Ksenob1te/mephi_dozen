#ifndef SEM1_LAB4_MANAGER_H
#define SEM1_LAB4_MANAGER_H

#include "stdlib.h"
#include "stdio.h"
#include "../table/table.h"

#define BLOCK_SIZE 24
#define GLOBAL_OFFSET 1

void write_table(FILE *file, Table *table);
void read_table(FILE *file, Table *table);

long write_keyspace(FILE *file, Table *table, KeySpace *key);
int read_keyspace(FILE *file, long block_offset, KeySpace *key);
long write_node(FILE *file, KeySpace *key, Node *node);
int read_node(FILE *file, long block_offset, Node *node);
void update_node(FILE *file, long block_offset, Node *node);
void update_keyspace(FILE *file, long block_offset, KeySpace *key);
void remove_block(long block_offset);

#endif //SEM1_LAB4_MANAGER_H
