#ifndef ZOOKEEPER_H
#define ZOOKEEPER_H

typedef struct {
    char name[50];
    char expertise[100];
} Zookeeper;

Zookeeper createZookeeper(const char* name, const char* expertise);

#endif /* ZOOKEEPER_H */
