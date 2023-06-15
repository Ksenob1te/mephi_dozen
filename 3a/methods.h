#ifndef SEM1_LAB4_METHODS_H
#define SEM1_LAB4_METHODS_H
#include "table/table.h"

void print_table(Table *table);
void add_key(Table *table);
void add_element_key(Table *table);
void search_interval(Table *table);
void search_key(Table *table);
void search_element_version(Table *table);
void delete_key(Table *table);
void delete_element_version(Table *table);

#endif //SEM1_LAB4_METHODS_H
