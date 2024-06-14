#ifndef VISITOR_H
#define VISITOR_H

typedef struct {
    char name[50];
    int age;
} Visitor;

Visitor createVisitor(const char* name, int age);

#endif /* VISITOR_H */
