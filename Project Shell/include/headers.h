#ifndef HEADERS_H
#define HEADERS_H

#define MAX_INPUT 1024
#define MAX_ARGS 64

void display_prompt();
int read_input(char *line);
int parse_input(char *line, char **args);
void execute_command(char **args, int num_args);
int handle_builtin(char **args);

int file_exists(const char *filename);
void print_error(const char *msg);
int is_directory(const char *path);
int can_execute(const char *path);
int redirect_input(const char *filename);
int redirect_output(const char *filename);

#endif /* HEADERS_H */
