#ifndef ANIMAL_H
#define ANIMAL_H

typedef struct {
    char name[50];
    int age;
    char type[50];
} Animal;

Animal createAnimal(const char* name, int age, const char* type);

#endif /* ANIMAL_H */
