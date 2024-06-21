#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"

#define MAX_DISTANCE 999999

void dijkstra(Graph *graph, int start_vertex, int *distances);

#endif