#include "manager.h"

void write_table(FILE *file, Table *table) {
    fwrite(table, sizeof(Table), 1, file);
}

void read_table(FILE *file, Table *table) {
    fread(table, sizeof(Table), 1, file);
}
