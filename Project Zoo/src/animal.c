#include "animal.h"
#include <string.h>

Animal createAnimal(const char* name, int age, const char* type) {
    Animal animal;
    strncpy(animal.name, name, sizeof(animal.name) - 1);
    animal.name[sizeof(animal.name) - 1] = '\0';
    animal.age = age;
    strncpy(animal.type, type, sizeof(animal.type) - 1);
    animal.type[sizeof(animal.type) - 1] = '\0';
    return animal;
}
