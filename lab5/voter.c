#include "voter.h"
#include "stdlib.h"

const struct VoterClass Voter = {.new=&newVoter};

void clear(struct Voter *this) {
    free(this->username);
    free(this->place);
    free(this->age);
}


static struct Voter newVoter(char *username, char *place, char *age) {
    return (struct Voter) {
        .username=username,
        .place=place,
        .age=age,
        .clear=clear
    };
}



