//
// Created by Ksenob1te on 28.04.2023.
//

#include "manager.h"
#include "string.h"

KeySpace read_keyspace(long block_offset, FILE* file) {
    fseek(file, DEFAULT_OFFSET + (BLOCK_SIZE * block_offset), SEEK_SET);
    KeySpace key;
    fread(&(key.busy), sizeof(int), 1, file);
    fread(&(key.key_offset), sizeof(long), 1, file);
    fread(&(key.info), sizeof(ull), 1, file);
    return key;
}

void write_keyspace(KeySpace key, long block_offset, FILE* file) {
    fseek(file, DEFAULT_OFFSET + (BLOCK_SIZE * block_offset), SEEK_SET);
    fwrite(&(key.busy), sizeof(int), 1, file);
    fwrite(&(key.key_offset), sizeof(long), 1, file);
    fwrite(&(key.info), sizeof(ull), 1, file);
}

char * read_key(long offset, FILE* file) {
    char *ptr = (char *) calloc(1, sizeof(char));
    char buf[81];
    int len = 0;
    int end = 0, i = 0;
    fseek(file, offset, SEEK_SET);
    do {
        for (; i < 80; i++) {
            fread(buf + i, sizeof(char), 1, file);
            if (buf[i] == '\0') {
                end = 1;
                break;
            }
            if (buf[i] == EOF) {
                end = -1;
                break;
            }
        }
        if (end == -1) {
            free(ptr);
            ptr = NULL;
            continue;
        } else if (end == 1 && i == 0)
            continue;
        else {
            len += i;
            ptr = (char *) realloc(ptr, len + 1);
            strcat(ptr, buf);
        }
    } while (end != 1);
    ptr[len] = '\0';
    return ptr;
}

long write_key(char *key, FILE* file) {
    fseek(file, 0, SEEK_END);
    int offset = ftell(file);
    char k;
    for (k = *key; k != '\0'; k = *(++key))
        fwrite(&k, sizeof(char), 1, file);
    fwrite(&k, sizeof(char), 1, file);
    return offset;
}
