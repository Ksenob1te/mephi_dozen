#include <stdio.h>
#include <unistd.h>
#include "string.h"

static char *fInput = NULL, *fOutput = NULL, *sortType = NULL, *sortDir = NULL, *sortField = NULL;

int parseArgs(int argc, char *argv[]) {
    int status;
    while (optind < argc) {
        if ((status = getopt(argc, argv, "s:t:d:")) != -1)
            switch (status) {
                case 's': sortType = optarg; break;
                case 't': sortField = optarg; break;
                case 'd': sortDir = optarg; break;
                default:
                    break;
            }
        else {
            if (!fInput) fInput = argv[optind];
            else fOutput = argv[optind];
            optind++;
        }
    }
    if (!fInput || !fOutput) {
        printf("No Input/Output file in the arguments\n");
        return 1;
    }
    if (sortType && strcmp(sortType, "bubble") && strcmp(sortType, "insertion") && strcmp(sortType, "qsort")) {
        printf("Wrong sort method selection, it should be \"bubble\", \"insertion\" or \"qsort\"\n");
        return 2;
    }
    if (!sortType) sortType = "qsort";

    if (sortDir && strcmp(sortDir, "incremental") && strcmp(sortDir, "decremental")) {
        printf("Wrong sort direction selection, it should be \"incremental\" or \"decremental\"\n");
        return 3;
    }
    if (!sortDir) sortDir = "incremental";

    if (sortField && strcmp(sortField, "name") && strcmp(sortField, "place") && strcmp(sortField, "age")) {
        printf("Wrong sort direction selection, it should be \"place\", \"name\" or \"age\"\n");
        return 4;
    }
    if (!sortField) sortField = "name";

    return 0;
}


int main(int argc, char *argv[]) {
    parseArgs(argc, argv);
    printf("%s", sortType);
}