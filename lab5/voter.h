#ifndef LAB4_VOTER_H
#define LAB4_VOTER_H


struct Voter {
    char *username;
    char *place;
    char *age;

    void (*clear) (struct Voter*);
};

extern const struct VoterClass {
    struct Voter (*new)(char *username, char *place, char *age);
} Voter;


static struct Voter newVoter(char *username, char *place, char *age);

#endif //LAB4_VOTER_H
