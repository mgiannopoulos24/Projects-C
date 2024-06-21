#ifndef UNION_FIND_H
#define UNION_FIND_H

typedef struct {
    int *parent;
    int *rank;
    int size;
} UnionFind;

void uf_init(UnionFind *uf, int size);
void uf_destroy(UnionFind *uf);
int uf_find(UnionFind *uf, int vertex);
void uf_union(UnionFind *uf, int root1, int root2);

#endif