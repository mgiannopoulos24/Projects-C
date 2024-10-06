#ifndef MYSORT_H
#define MYSORT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#define MAX_RECORDS 10000
#define NAME_SIZE 20
#define ZIP_SIZE 6

typedef struct {
    int id;
    char surname[NAME_SIZE];
    char name[NAME_SIZE];
    char zip[ZIP_SIZE];
} Record;

void parse_args(int argc, char *argv[], char **input_file, int *k, char **sort_exec1, char **sort_exec2);
void create_hierarchy(const char *input_file, int k, const char *sort_exec1, const char *sort_exec2);
void coordinator(const char *input_file, int k, const char *sort_exec1, const char *sort_exec2);
void splitter_merger(const char *input_file, int k, const char *sort_exec);
void sorter(const char *input_file, const char *output_file, const char *sort_exec);

#endif // MYSORT_H
