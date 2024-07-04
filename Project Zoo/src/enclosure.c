#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enclosure.h"


Enclosure* createEnclosure(const char* name, const char* habitat) {
    Enclosure* enclosure = (Enclosure*)malloc(sizeof(Enclosure));
    if (enclosure == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for enclosure.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(enclosure->name, name, sizeof(enclosure->name) - 1);
    enclosure->name[sizeof(enclosure->name) - 1] = '\0';

    strncpy(enclosure->habitat, habitat, sizeof(enclosure->habitat) - 1);
    enclosure->habitat[sizeof(enclosure->habitat) - 1] = '\0';

    enclosure->animals = NULL; // Initialize to NULL (no animals yet)
    enclosure->numAnimals = 0;
    enclosure->maxCapacity = MAX_ANIMALS_PER_ENCLOSURE;
    enclosure->assignedZookeeper = NULL;

    return enclosure;
}

void addAnimalToEnclosure(Animal* animal, Enclosure* enclosure) {
    if (enclosure->animals == NULL) {
        enclosure->animals = (Animal*)malloc(enclosure->maxCapacity * sizeof(Animal));
        if (enclosure->animals == NULL) {
            fprintf(stderr, "Error: Memory allocation failed for animals in enclosure.\n");
            exit(EXIT_FAILURE);
        }
    }

    if (enclosure->numAnimals < enclosure->maxCapacity) {
        enclosure->animals[enclosure->numAnimals] = *animal;
        enclosure->numAnimals++;
        printf("Added %s to enclosure %s.\n", animal->name, enclosure->name);
    } else {
        printf("Cannot add more animals to enclosure %s. Maximum capacity reached.\n", enclosure->name);
    }
}

void assignZookeeperToEnclosure(Zookeeper* zookeeper, Enclosure* enclosure) {
    enclosure->assignedZookeeper = zookeeper;
    printf("Assigned zookeeper %s to enclosure %s.\n", zookeeper->name, enclosure->name);
}

void printEnclosureDetails(Enclosure* enclosure) {
    printf("Enclosure Name: %s\n", enclosure->name);
    printf("Habitat: %s\n", enclosure->habitat);
    printf("Number of Animals: %d / %d\n", enclosure->numAnimals, enclosure->maxCapacity);
    if (enclosure->assignedZookeeper != NULL) {
        printf("Assigned Zookeeper: %s\n", enclosure->assignedZookeeper->name);
    } else {
        printf("No zookeeper assigned.\n");
    }
}
