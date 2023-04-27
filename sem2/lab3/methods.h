#ifndef SEM1_LAB4_METHODS_H
#define SEM1_LAB4_METHODS_H
#include "table/table.h"

void print_table(const char *input, Table *table);
void add_key(const char *file_name, Table *table);
void add_element_key(const char *file_name, Table *table);
void search_interval(const char *file_name, Table *table);
void search_key(const char *file_name, Table *table);
void search_element_version(const char *file_name, Table *table);
void delete_key(const char *file_name, Table *table);
void delete_element_version(const char *file_name, Table *table);

#endif //SEM1_LAB4_METHODS_H
