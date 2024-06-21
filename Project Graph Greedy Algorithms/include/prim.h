#ifndef PRIM_H
#define PRIM_H

#include "graph.h"

#define MAX_DISTANCE 999999

void prim(Graph *graph, int start_vertex, int *parent);

#endif