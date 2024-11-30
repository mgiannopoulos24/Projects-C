#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Function to check if a file exists
int file_exists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

// Function to print error messages
void print_error(const char *msg) {
    perror(msg);
}

// Function to check if a path is a directory
int is_directory(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

// Function to check if a process has execute permission
int can_execute(const char *path) {
    return access(path, X_OK) == 0;
}

// Function to redirect input from a file
int redirect_input(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 0; // Failed to open file
    }
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("dup2");
        close(fd);
        return 0; // Failed to redirect stdin
    }
    close(fd);
    return 1; // Success
}

// Function to redirect output to a file
int redirect_output(const char *filename) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 0; // Failed to open file
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(fd);
        return 0; // Failed to redirect stdout
    }
    close(fd);
    return 1; // Success
}
