#include "route.h"
#include <stdio.h>
#include <string.h>

Route routes[MAX_ROUTES];  // Define routes array
int num_routes = 0;  // Initialize num_routes

void display_routes() {
    printf("Available Routes:\n");
    for (int i = 0; i < num_routes; ++i) {
        printf("Route ID: %d, Source: %s, Destination: %s\n", routes[i].route_id, routes[i].source, routes[i].destination);
    }
}

Route* find_route(int route_id) {
    for (int i = 0; i < num_routes; ++i) {
        if (routes[i].route_id == route_id) {
            return &routes[i];
        }
    }
    return NULL; // Route ID not found
}
