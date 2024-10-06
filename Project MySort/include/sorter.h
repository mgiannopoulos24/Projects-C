#ifndef SORTER_H
#define SORTER_H

#include "mysort.h"

void quicksort(Record *records, int low, int high);
int partition(Record *records, int low, int high);
void merge_sort(Record *records, int l, int r);
void merge(Record *records, int l, int m, int r);

#endif // SORTER_H
