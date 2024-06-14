#include "zookeeper.h"
#include <string.h>

Zookeeper createZookeeper(const char* name, const char* expertise) {
    Zookeeper zookeeper;
    strncpy(zookeeper.name, name, sizeof(zookeeper.name) - 1);
    zookeeper.name[sizeof(zookeeper.name) - 1] = '\0';
    strncpy(zookeeper.expertise, expertise, sizeof(zookeeper.expertise) - 1);
    zookeeper.expertise[sizeof(zookeeper.expertise) - 1] = '\0';
    return zookeeper;
}
