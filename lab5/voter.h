#ifndef LAB4_VOTER_H
#define LAB4_VOTER_H


struct Voter {
    char *username;
    char *place;
    int age;
};

extern const struct VoterClass {
    struct Voter (*new)(char *username, char *place, int age);
} Voter;


static struct Voter newVoter(char *username, char *place, int age);

#endif //LAB4_VOTER_H
