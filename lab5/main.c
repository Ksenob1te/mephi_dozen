#include <stdio.h>
#include <unistd.h>
#include "stdlib.h"
#include "math.h"

int main(int argc, char *argv[]) {
    int status, countPos = 0;
    char *fInput = NULL, *fOutput = NULL, *sortType = NULL, *sortDir = NULL, *sortField = NULL;
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
    printf("s = '%s', in = '%s', op = '%s'", sortType, fInput, fOutput);
}