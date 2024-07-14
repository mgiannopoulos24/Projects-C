#ifndef VOTER_H
#define VOTER_H

typedef struct Voter {
    int pin;
    char lname[50];
    char fname[50];
    int zip;
    char voted;
} Voter;

#endif // VOTER_H
