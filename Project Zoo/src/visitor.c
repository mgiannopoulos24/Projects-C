#include "visitor.h"
#include <string.h>

Visitor createVisitor(const char* name, int age) {
    Visitor visitor;
    strncpy(visitor.name, name, sizeof(visitor.name) - 1);
    visitor.name[sizeof(visitor.name) - 1] = '\0';
    visitor.age = age;
    return visitor;
}
