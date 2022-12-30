#include <stdio.h>
#include "stdlib.h"
#include <unistd.h>
#include "string.h"
#include "methods.h"
#include "voter.h"

static char *fInput = NULL, *fOutput = NULL, *sortType = NULL, *sortDir = NULL, *sortField = NULL;

int parseArgs(int argc, char *argv[]) {
    int status, tempOptind;
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
            if (!fInput) fInput = argv[tempOptind];
            else fOutput = argv[tempOptind];
            optind++;
        }
    }
//    printf("%s\n", fInput);
    if (!fInput || !fOutput) {
        fprintf(stderr, "No Input/Output file in the arguments\n");
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
    FILE *IF = fopen(fInput, "r"), *OF = fopen(fOutput, "w");
    if (IF == NULL) {
        fprintf(stderr, "Error with opening files, check routes and try again\n");
        return 132;
    }
    int len = 0;
    status = 0;
    struct Voter *array = malloc(0);
    while (status == 0) {
        char *username = freadline(IF);
        char *place = freadline(IF);
        char *age = freadline(IF);
        if (!username || !place || !age) {
            status = 1;
        } else if (checkPlace(place) || checkAge(age)) {
            fprintf(stderr, "Error with %d input object, it won't be used\n", len + 1);
        } else {
            array = realloc(array, (len + 1) * sizeof(struct Voter));
            array[len] = Voter.new(username, place, age);
            len++;
        }
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
    if (!strcmp(sortType, "qsort")) qsort((void *) array, len, sizeof(struct Voter), comp);
    if (!strcmp(sortType, "bubble")) bubbleSort((void *) array, len, sizeof(struct Voter), comp);
    if (!strcmp(sortType, "insertion")) pairInsertionSort((void *) array, len, sizeof(struct Voter), comp);
    for (int i = 0; i < len; ++i) {
        printf("%s; %s; %s\n", array[i].username, array[i].place, array[i].age);
    }

}