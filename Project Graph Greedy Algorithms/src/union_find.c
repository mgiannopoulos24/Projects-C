#include <stdlib.h>
#include "union_find.h"

void uf_init(UnionFind *uf, int size) {
    uf->parent = (int *)malloc((size + 1) * sizeof(int));
    uf->rank = (int *)malloc((size + 1) * sizeof(int));
    uf->size = size;

    for (int i = 1; i <= size; ++i) {
        uf->parent[i] = i;
        uf->rank[i] = 0;
    }
}

void uf_destroy(UnionFind *uf) {
    free(uf->parent);
    free(uf->rank);
}

int uf_find(UnionFind *uf, int vertex) {
    if (uf->parent[vertex] != vertex) {
        uf->parent[vertex] = uf_find(uf, uf->parent[vertex]); // Path compression
    }
    return uf->parent[vertex];
}

void uf_union(UnionFind *uf, int root1, int root2) {
    if (uf->rank[root1] > uf->rank[root2]) {
        uf->parent[root2] = root1;
    } else if (uf->rank[root1] < uf->rank[root2]) {
        uf->parent[root1] = root2;
    } else {
        uf->parent[root2] = root1;
        uf->rank[root1]++;
    }
}