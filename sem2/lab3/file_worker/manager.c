#include "manager.h"
#include "removal_list.h"

static RemovalList removalList = {NULL};

void read_table(FILE *file, Table *table) {
    fseek(file, 0, SEEK_SET);
    fread(&(table->key_offset), sizeof(long), 1, file);
}

void write_table(FILE *file, Table *table) {
    fseek(file, 0, SEEK_SET);
    fwrite(&(table->key_offset), sizeof(long), 1, file);
}

long write_keyspace(FILE *file, Table *table, KeySpace *key) {
    key->link_offset = table->key_offset;
    long end_offset;
    if (!removalList.head) {
        fseek(file, 0, SEEK_END);
        end_offset = ftell(file);
        end_offset = (end_offset % BLOCK_SIZE != 0 ? BLOCK_SIZE : 0) + ((long) (end_offset / BLOCK_SIZE)) * BLOCK_SIZE;
    } else {
        end_offset = removalList.head->offset;
        RemovalNode *node = removalList.head;
        removalList.head = removalList.head->next;
        free(node);
    }
    if (end_offset == 0) end_offset += (GLOBAL_OFFSET * BLOCK_SIZE);
    fseek(file, end_offset, SEEK_SET);
    table->key_offset = end_offset / BLOCK_SIZE;
    fwrite(&(key->key), sizeof(ull), 1, file);
    fwrite(&(key->first_offset), sizeof(long), 1, file);
    fwrite(&(key->link_offset), sizeof(long), 1, file);
    fwrite(&(key->last_release), sizeof(ull), 1, file);
    return end_offset;
}

int read_keyspace(FILE *file, long block_offset, KeySpace *key) {
    if (block_offset == -1) return 1;
    fseek(file, block_offset * BLOCK_SIZE, SEEK_SET);
    fread(&(key->key), sizeof(ull), 1, file);
    fread(&(key->first_offset), sizeof(long), 1, file);
    fread(&(key->link_offset), sizeof(long), 1, file);
    fread(&(key->last_release), sizeof(ull), 1, file);
    return 0;
}

long write_node(FILE *file, KeySpace *key, Node *node) {
    node->next_offset = key->first_offset;
    long end_offset;
    if (!removalList.head) {
        fseek(file, 0, SEEK_END);
        end_offset = ftell(file);
        end_offset = (end_offset % BLOCK_SIZE != 0 ? BLOCK_SIZE : 0) + ((long) (end_offset / BLOCK_SIZE)) * BLOCK_SIZE;
    } else {
        end_offset = removalList.head->offset * BLOCK_SIZE;
        RemovalNode *removalNode = removalList.head;
        removalList.head = removalList.head->next;
        free(removalNode);
    }
    if (end_offset == 0) end_offset += (GLOBAL_OFFSET * BLOCK_SIZE);
    fseek(file, end_offset, SEEK_SET);
    key->first_offset = end_offset / BLOCK_SIZE;
    (key->last_release)++;
    node->release = key->last_release;
//    update_node(file, )
    fwrite(&(node->info), sizeof(ull), 1, file);
    fwrite(&(node->next_offset), sizeof(long), 1, file);
    fwrite(&(node->release), sizeof(ull), 1, file);
    return end_offset;
}

void update_node(FILE *file, long block_offset, Node *node) {
    fseek(file, block_offset * BLOCK_SIZE + 8, SEEK_SET); // we can not update info and release
    fwrite(&(node->next_offset), sizeof(long), 1, file);
}

void update_keyspace(FILE *file, long block_offset, KeySpace *key) {
    fseek(file, block_offset * BLOCK_SIZE + 8, SEEK_SET); // we can not update key value
    fwrite(&(key->first_offset), sizeof(long), 1, file);
    fwrite(&(key->link_offset), sizeof(long), 1, file);
    fwrite(&(key->last_release), sizeof(ull), 1, file);
}

int read_node(FILE *file, long block_offset, Node *node) {
    if (block_offset == -1) return 1;
    fseek(file, block_offset * BLOCK_SIZE, SEEK_SET);
    fread(&(node->info), sizeof(ull), 1, file);
    fread(&(node->next_offset), sizeof(long), 1, file);
    fread(&(node->release), sizeof(ull), 1, file);
    return 0;
}

void remove_block(long block_offset) {
    if (block_offset < 0) return;
    RemovalNode *removalNode = malloc(sizeof(RemovalNode));
    removalNode->offset = block_offset;
    removalNode->next = removalList.head;
    removalList.head = removalNode;
}
