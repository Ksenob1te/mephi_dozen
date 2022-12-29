#include "voter.h"

const struct VoterClass Voter = {.new=&newVoter};

static struct Voter newVoter(char *username, char *place, int age) {
    return (struct Voter) {
        .username=username,
        .place=place,
        .age=age
    };
}


