#ifndef MYSH_H
#define MYSH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stddef.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64
#define MAX_COMMANDS 16

// Function Declarations
void print_prompt();
char *read_line();
int parse_line(char *line, char **args);
int is_trace_command(char **args);
void execute_command(char **args);
void execute_pipeline(char ***commands, int num_commands);
void execute_pipeline_with_timing(char ***commands, int num_commands);
int parse_pipeline(char **args, char ****commands_ptr);
void count_c_files();  // Add this with other function declarations
#endif