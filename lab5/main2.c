#include <stdio.h>
#include "stdlib.h"
#include <unistd.h>
#include "string.h"
#include "methods.h"
#include "voter.h"
#include "time.h"

static char *elementsCount = NULL, *arraysCount = NULL, *sortType = NULL, *sortDir = NULL, *sortField = NULL;

int parseArgs(int argc, char *argv[]) {
    int status = 0, tempOptind = 0;
    while (optind < argc && tempOptind < argc) {
        tempOptind = optind;
        status = getopt(argc, argv, "s:t:d:");
        if (status != -1) {
            switch (status) {
                case 's':
                    sortType = optarg;
                    break;
                case 't':
                    sortField = optarg;
                    break;
                case 'd':
                    sortDir = optarg;
                    break;
                default:
                    break;
            }
        } else {
            optind = tempOptind;
            if (!elementsCount) elementsCount = argv[tempOptind];
            else arraysCount = argv[tempOptind];
            optind++;
        }
    }
//    printf("%s\n", elementsCount);
    if (checkAge(elementsCount) || checkAge(arraysCount)) {
        fprintf(stderr, "incorrect elements count or arrays count parameters\n");
        return 1;
    }
    if (sortType && strcmp(sortType, "bubble") && strcmp(sortType, "insertion") && strcmp(sortType, "qsort")) {
        fprintf(stderr, "Wrong sort method selection, it should be \"bubble\", \"insertion\" or \"qsort\"\n");
        return 2;
    }
    if (!sortType) sortType = "qsort";

    if (sortDir && strcmp(sortDir, "incremental") && strcmp(sortDir, "decremental")) {
        fprintf(stderr, "Wrong sort direction selection, it should be \"incremental\" or \"decremental\"\n");
        return 3;
    }
    if (!sortDir) sortDir = "incremental";

    if (sortField && strcmp(sortField, "name") && strcmp(sortField, "place") && strcmp(sortField, "age")) {
        fprintf(stderr, "Wrong sort direction selection, it should be \"place\", \"name\" or \"age\"\n");
        return 4;
    }
    if (!sortField) sortField = "name";

    return 0;
}

int main(int argc, char *argv[]) {
    int status = parseArgs(argc, argv);
    if (status) return 132;
    for (int counter = 1000; counter <= 10000; counter += 200) {
        clock_t timer = 0;
        for (int j = 0; j < convertInt(arraysCount); ++j) {
            srand(time(NULL));
            int len = counter;
            struct Voter *array = malloc(len * sizeof(struct Voter));
            for (int i = 0; i < len; ++i) {
                array[i] = generateRandom();
            }
            int (*comp)() = NULL;
            if (!strcmp(sortField, "name") && !strcmp(sortDir, "incremental")) comp = usernameComparatorInc;
            if (!strcmp(sortField, "name") && !strcmp(sortDir, "decremental")) comp = usernameComparatorDec;
            if (!strcmp(sortField, "place") && !strcmp(sortDir, "incremental")) comp = placeComparatorInc;
            if (!strcmp(sortField, "place") && !strcmp(sortDir, "decremental")) comp = placeComparatorDec;
            if (!strcmp(sortField, "age") && !strcmp(sortDir, "incremental")) comp = ageComparatorInc;
            if (!strcmp(sortField, "age") && !strcmp(sortDir, "decremental")) comp = ageComparatorDec;
            if (!comp) {
                fprintf(stderr, "Error occurred within commandline parameters\n");
                return 132;
            }
            clock_t begin = clock();
            if (!strcmp(sortType, "qsort")) qsort((void *) array, len, sizeof(struct Voter), comp);
            if (!strcmp(sortType, "bubble")) bubbleSort((void *) array, len, sizeof(struct Voter), comp);
            if (!strcmp(sortType, "insertion")) pairInsertionSort((void *) array, len, sizeof(struct Voter), comp);
            clock_t end = clock();
            for (int i = 0; i < len; ++i) {
                array[i].clear(array + i);
            }
            timer += (end - begin);
            free(array);
//            printf("Time %d: %lf\n", j + 1, (double)(end - begin) / CLOCKS_PER_SEC);
        }
        printf("%d done by %lf\n", counter, (double)timer / CLOCKS_PER_SEC);
        fprintf(fopen("output.txt", "a+"), "%.4lf\n", (double)timer / CLOCKS_PER_SEC / convertInt(arraysCount));
    }
}