#include "methods.h"
#include "file_worker/manager.h"
#include "stdio.h"

ull input_ull() {
    ull key;
    int status;
    input:
        status = scanf("%llu", &key);
        if (status == EOF || status < 0) return -1;
        if (status == 0) {
            fprintf(stderr, "\033[0;31mError in input, try again\033[0m\n");
            scanf("%*[^\n]");
            goto input;
        }
    return key;
}

void print_table(const char *input, Table *table) {
    FILE *file = fopen(input, "rb");
    printf("\033[0;33m.\033[0m\n");
    KeySpace current;
    int status = read_keyspace(file, table->key_offset, &current);
    for (; !status; status = read_keyspace(file, current.link_offset, &current)) {
        if (current.link_offset != -1) printf("├"); else printf("└");
        printf("── \033[0;33m%llu\033[0m\n", current.key);
        Node node;
        int status_node = read_node(file, current.first_offset, &node);
        for (; !status_node; status_node = read_node(file, node.next_offset, &node)) {
            if (current.link_offset != -1) printf("│"); else printf(" ");
            printf("   ");
            if (node.next_offset != -1) printf("├"); else printf("└");
            printf("── \033[1;90m%llu:\033[0m%llu\n", node.release, node.info);
        }
    }
}


void add_key(const char *file_name, Table *table) {
    printf("Type in key value (int): ");
    ull key = input_ull();
    if (key == -1) return;
    FILE *file = fopen(file_name, "rb+");
    KeySpace checker;

    if (!table->find_key(file, table, &checker, key)) {
        fprintf(stderr, "\033[0;31mThis keyspace already exists\033[0m\n");
        return;
    }

    KeySpace keyspace = {key, -1, -1, -1};
    table->add_key(file, table, &keyspace);
    write_table(file, table);
    fclose(file);
    printf("Done!\n");
}

void add_element_key(const char *file_name, Table *table) {
    printf("Type in key value (int): ");
    ull key = input_ull();
    if (key == -1) return;
    FILE *file = fopen(file_name, "rb+");
    KeySpace keyspace;
    select_funcs(&keyspace);
    int status = table->find_key(file, table, &keyspace, key);
    if (status) {
        fprintf(stderr, "\033[0;31mNo key has been found\033[0m\n");
        fclose(file);
        return;
    }
    printf("Type in element value (int): ");
    ull value = input_ull();
    if (value == -1) return;
    Node node = {value, -1, -1};
    long block_offset = find_key_address(file, table, &keyspace);
    keyspace.add_node(file, &keyspace, &node);
    update_keyspace(file, block_offset, &keyspace);
    fclose(file);
    printf("Done!\n");
}

void search_interval(const char *file_name, Table *table) {
    printf("Type in left interval value (int): ");
    ull left = input_ull();
    if (left == -1) return;
    printf("Type in right interval value (int): ");
    ull right = input_ull();
    if (right == -1) return;

    FILE *file = fopen(file_name, "rb");
    Table *tmp_result = table->find_key_range(file, "tmp/tmp1.bin", table, left, right);

//    FILE *res = fopen("tmp/tmp1.bin", "rb");
//    Table *result = table->find_key_range(res, "tmp/tmp.bin", tmp_result, left, right);

    fclose(file);
//    fclose(res);
//    free(tmp_result);
    printf("Result of the search: \n");
    print_table("tmp/tmp1.bin", tmp_result);
//    free(result);
}

void search_key(const char *file_name, Table *table) {
    printf("Type in key value (int): ");
    ull key = input_ull();
    if (key == -1) return;

    FILE *file = fopen(file_name, "rb");
    KeySpace keyspace;
    int status = table->find_key(file, table, &keyspace, key);
    if (status) {
        fprintf(stderr, "\033[0;31mNo key has been found\033[0m\n");
        fclose(file);
        return;
    }

    printf("\033[0;33m%llu\033[0m\n", keyspace.key);
    Node node;
    int status_node = read_node(file, keyspace.first_offset, &node);
    for (; !status_node; status_node = read_node(file, node.next_offset, &node)) {
        if (node.next_offset != -1) printf("├"); else printf("└");
        printf("── \033[1;90m%llu:\033[0m%llu\n", node.release, node.info);
    }

    fclose(file);
}

void search_element_version(const char *file_name, Table *table) {
    printf("Type in key value (int): ");
    ull key = input_ull();
    if (key == -1) return;

    FILE *file = fopen(file_name, "rb");
    KeySpace keyspace;
    select_funcs(&keyspace);
    int status = table->find_key(file, table, &keyspace, key);
    if (status) {
        fprintf(stderr, "\033[0;31mNo key has been found\033[0m\n");
        fclose(file);
        return;
    }

    printf("Type in release version (int): ");
    ull release = input_ull();
    if (release == -1) return;
    Node node;
    status = keyspace.find_node(file, &keyspace, &node, release);
    if (status) {
        fprintf(stderr, "\033[0;31mNo node has been found\033[0m\n");
        fclose(file);
        return;
    }
    printf("Found node:\n\033[1;90m%llu:\033[0m%llu\n", node.release, node.info);
    fclose(file);
}

void delete_key(const char *file_name, Table *table) {
    printf("Type in key value (int): ");
    ull key = input_ull();
    if (key == -1) return;
    FILE *file = fopen(file_name, "rb+");
    int status = table->remove_key(file, table, key);
    if (status == 2) write_table(file, table);
    if (!status)
        fprintf(stderr, "\033[0;31mNo key has been found\033[0m\n");
    else
        printf("Done!\n");
    fclose(file);
}

void delete_element_version(const char *file_name, Table *table) {
    printf("Type in key value (int): ");
    ull key = input_ull();
    if (key == -1) return;

    FILE *file = fopen(file_name, "rb+");
    KeySpace keyspace;
    select_funcs(&keyspace);
    int status = table->find_key(file, table, &keyspace, key);
    if (status) {
        fprintf(stderr, "\033[0;31mNo key has been found\033[0m\n");
        fclose(file);
        return;
    }

    printf("Type in release version (int): ");
    ull release = input_ull();
    if (release == -1) return;
    status = keyspace.remove_node(file, &keyspace, release);
    if (status == 2) {
        long block_offset = find_key_address(file, table, &keyspace);
        update_keyspace(file, block_offset, &keyspace);
    }
    fclose(file);
    if (!status) {
        fprintf(stderr, "\033[0;31mNo node has been found\033[0m\n");
        return;
    }
    printf("Done!\n");
}
