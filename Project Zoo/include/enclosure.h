#ifndef ENCLOSURE_H
#define ENCLOSURE_H

#include "animal.h"
#include "zookeeper.h"

#define MAX_ANIMALS_PER_ENCLOSURE 10 // Example maximum capacity

typedef struct {
    char name[50];
    char habitat[50];
    Animal* animals; // Dynamic array of animals in the enclosure
    int numAnimals;
    int maxCapacity;
    Zookeeper* assignedZookeeper;
} Enclosure;

Enclosure createEnclosure(const char* name, const char* habitat);
void addAnimalToEnclosure(Animal* animal, Enclosure* enclosure);
void assignZookeeperToEnclosure(Zookeeper* zookeeper, Enclosure* enclosure);
void printEnclosureDetails(Enclosure* enclosure);

#endif /* ENCLOSURE_H */
