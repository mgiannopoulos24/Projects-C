#ifndef PARSER_H
#define PARSER_H

// Define a simple structure for a command (to be expanded)
typedef struct {
    char *command;
    // Additional fields as needed
} Command;

// Function prototype for parsing a line of IPL code
Command parse_line(const char *line);

#endif // PARSER_H
