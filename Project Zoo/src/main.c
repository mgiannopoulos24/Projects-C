#include <stdio.h>
#include <stdlib.h> // For dynamic memory allocation
#include <string.h> // For string manipulation functions
#include "animal.h"
#include "enclosure.h"
#include "zookeeper.h"
#include "visitor.h"

#define MAX_ANIMALS 100 // Maximum number of animals the zoo can manage
#define MAX_ZOOKEEPERS 50 // Maximum number of zookeepers the zoo can have
#define MAX_VISITORS 50 // Maximum number of visitors the zoo can have

// Function prototypes
void printMenu();
void addAnimalMenu(Animal animals[], int *numAnimals, Enclosure enclosures[], int numEnclosures);
void createEnclosureMenu(Enclosure enclosures[], int *numEnclosures);
void addZookeeperMenu(Zookeeper zookeepers[], int *numZookeepers);
void addVisitorMenu(Visitor visitors[], int *numVisitors);
void assignZookeeperMenu(Zookeeper zookeepers[], Enclosure enclosures[], int numZookeepers, int numEnclosures);
void viewZooInfo(Enclosure enclosures[], int numEnclosures, Visitor visitors[], int numVisitors);

int main() {
    Animal animals[MAX_ANIMALS];
    Enclosure enclosures[MAX_ANIMALS];
    Zookeeper zookeepers[MAX_ZOOKEEPERS];
    Visitor visitors[MAX_VISITORS];

    int numAnimals = 0;
    int numEnclosures = 0;
    int numZookeepers = 0;
    int numVisitors = 0;

    int choice;
    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character left in input buffer

        switch (choice) {
            case 1:
                createEnclosureMenu(enclosures, &numEnclosures);
                break;
            case 2:
                addAnimalMenu(animals, &numAnimals, enclosures, numEnclosures);
                break;
            case 3:
                addZookeeperMenu(zookeepers, &numZookeepers);
                break;
            case 4:
                addVisitorMenu(visitors, &numVisitors);
                break;
            case 5:
                assignZookeeperMenu(zookeepers, enclosures, numZookeepers, numEnclosures);
                break;
            case 6:
                viewZooInfo(enclosures, numEnclosures, visitors, numVisitors);
                break;
            case 7:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a number from 1 to 7.\n");
        }

        printf("\n");

    } while (choice != 7);

    return 0;
}

void printMenu() {
    printf("\n===== Zoo Management System Menu =====\n");
    printf("1. Create an enclosure\n");
    printf("2. Add an animal\n");
    printf("3. Add a zookeeper\n");
    printf("4. Add a visitor\n");
    printf("5. Assign a zookeeper to an enclosure\n");
    printf("6. View zoo information\n");
    printf("7. Exit\n");
}

void addAnimalMenu(Animal animals[], int *numAnimals, Enclosure enclosures[], int numEnclosures) {
    if (*numAnimals >= MAX_ANIMALS) {
        printf("Cannot add more animals. Maximum capacity reached.\n");
        return;
    }

    char name[50], type[50];
    int age;
    printf("Enter animal name: ");
    scanf("%49s", name);
    getchar(); // Consume newline character left in input buffer

    printf("Enter animal age: ");
    scanf("%d", &age);
    getchar(); // Consume newline character left in input buffer

    printf("Enter animal type: ");
    scanf("%49s", type);
    getchar(); // Consume newline character left in input buffer

    // Print available enclosures to choose from
    printf("Available Enclosures:\n");
    for (int i = 0; i < numEnclosures; ++i) {
        printf("%d. %s\n", i + 1, enclosures[i].name);
    }

    int enclosureIndex;
    printf("Assign %s to which enclosure (by number): ", name);
    scanf("%d", &enclosureIndex);
    enclosureIndex--; // Convert to zero-indexed

    if (enclosureIndex < 0 || enclosureIndex >= numEnclosures) {
        printf("Invalid enclosure selection.\n");
        return;
    }

    // Add animal to the selected enclosure
    animals[*numAnimals] = createAnimal(name, age, type);
    addAnimalToEnclosure(&animals[*numAnimals], &enclosures[enclosureIndex]);
    enclosures[enclosureIndex].numAnimals++;

    (*numAnimals)++;
    printf("Animal added to enclosure '%s' successfully.\n", enclosures[enclosureIndex].name);
}

void createEnclosureMenu(Enclosure enclosures[], int *numEnclosures) {
    if (*numEnclosures >= MAX_ANIMALS) {
        printf("Cannot create more enclosures. Maximum capacity reached.\n");
        return;
    }

    char name[50], habitat[50];
    printf("Enter enclosure name: ");
    scanf("%49s", name);
    getchar(); // Consume newline character left in input buffer

    printf("Enter habitat: ");
    scanf("%49s", habitat);
    getchar(); // Consume newline character left in input buffer

    enclosures[*numEnclosures] = createEnclosure(name, habitat);
    (*numEnclosures)++;

    printf("Enclosure created successfully.\n");
}

void addZookeeperMenu(Zookeeper zookeepers[], int *numZookeepers) {
    if (*numZookeepers >= MAX_ZOOKEEPERS) {
        printf("Cannot add more zookeepers. Maximum capacity reached.\n");
        return;
    }

    char name[50], expertise[100];
    printf("Enter zookeeper name: ");
    scanf("%49s", name);
    getchar(); // Consume newline character left in input buffer

    printf("Enter zookeeper expertise: ");
    scanf("%99s", expertise);
    getchar(); // Consume newline character left in input buffer

    zookeepers[*numZookeepers] = createZookeeper(name, expertise);
    (*numZookeepers)++;

    printf("Zookeeper added successfully.\n");
}

void addVisitorMenu(Visitor visitors[], int *numVisitors) {
    if (*numVisitors >= MAX_VISITORS) {
        printf("Cannot add more visitors. Maximum capacity reached.\n");
        return;
    }

    char name[50];
    int age;
    printf("Enter visitor name: ");
    scanf("%49s", name);
    getchar(); // Consume newline character left in input buffer

    printf("Enter visitor age: ");
    scanf("%d", &age);
    getchar(); // Consume newline character left in input buffer

    visitors[*numVisitors] = createVisitor(name, age);
    (*numVisitors)++;

    printf("Visitor added successfully.\n");
}

void assignZookeeperMenu(Zookeeper zookeepers[], Enclosure enclosures[], int numZookeepers, int numEnclosures) {
    if (numZookeepers == 0 || numEnclosures == 0) {
        printf("Cannot assign zookeeper. Ensure there are zookeepers and enclosures created.\n");
        return;
    }

    int zookeeperIndex, enclosureIndex;

    printf("Zookeepers available:\n");
    for (int i = 0; i < numZookeepers; ++i) {
        printf("%d. %s\n", i + 1, zookeepers[i].name);
    }

    printf("Select a zookeeper (by number): ");
    scanf("%d", &zookeeperIndex);
    zookeeperIndex--; // Convert to zero-indexed

    if (zookeeperIndex < 0 || zookeeperIndex >= numZookeepers) {
        printf("Invalid zookeeper selection.\n");
        return;
    }

    printf("Available enclosures:\n");
    for (int i = 0; i < numEnclosures; ++i) {
        printf("%d. %s\n", i + 1, enclosures[i].name);
    }

    printf("Assign zookeeper %s to which enclosure (by number): ", zookeepers[zookeeperIndex].name);
    scanf("%d", &enclosureIndex);
    enclosureIndex--; // Convert to zero-indexed

    if (enclosureIndex < 0 || enclosureIndex >= numEnclosures) {
        printf("Invalid enclosure selection.\n");
        return;
    }

    assignZookeeperToEnclosure(&zookeepers[zookeeperIndex], &enclosures[enclosureIndex]);
    printf("Zookeeper assigned successfully.\n");
}

void viewZooInfo(Enclosure enclosures[], int numEnclosures, Visitor visitors[], int numVisitors) {
    printf("\n===== Zoo Information =====\n");

    printf("Enclosures:\n");
    for (int i = 0; i < numEnclosures; ++i) {
        printf("Enclosure Name: %s\n", enclosures[i].name);
        printf("Habitat: %s\n", enclosures[i].habitat);
        printf("Number of Animals: %d\n", enclosures[i].numAnimals);
        if (enclosures[i].assignedZookeeper != NULL) {
            printf("Assigned Zookeeper: %s\n", enclosures[i].assignedZookeeper->name);
        } else {
            printf("No zookeeper assigned.\n");
        }
        printf("\n");
    }

    printf("Visitors:\n");
    for (int i = 0; i < numVisitors; ++i) {
        printf("Visitor Name: %s\n", visitors[i].name);
        printf("Visitor Age: %d\n", visitors[i].age);
        printf("\n");
    }
}
