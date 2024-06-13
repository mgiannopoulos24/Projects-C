#ifndef ROUTE_H
#define ROUTE_H

#define MAX_ROUTES 50

typedef struct {
    int route_id;
    char source[50];
    char destination[50];
    int bus_id;
    // Add more fields as needed
} Route;

extern Route routes[MAX_ROUTES];  // Declare routes array
extern int num_routes;  // Declare num_routes variable

void display_routes();
Route* find_route(int route_id);

#endif
