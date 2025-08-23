#include "mysh.h"

void print_prompt() {
    printf("mysh> ");
    fflush(stdout);
}

char *read_line() {
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t read = getline(&line, &bufsize, stdin);
    
    if (read == -1) {
        free(line);
        return NULL;
    }
    
    if (line[read - 1] == '\n') {
        line[read - 1] = '\0';
    }
    
    return line;
}

int parse_line(char *line, char **args) {
    int argc = 0;
    char *token = strtok(line, " \t\n\r");
    
    while (token != NULL && argc < MAX_ARGS - 1) {
        args[argc] = token;
        argc++;
        token = strtok(NULL, " \t\n\r");
    }
    args[argc] = NULL;
    
    return argc;
}

int is_trace_command(char **args) {
    return args[0] != NULL && strcmp(args[0], "trace") == 0;
}

void execute_command(char **args) {
    pid_t pid = fork();
    
    if (pid == 0) {
        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    } else if (pid > 0) {
        waitpid(pid, NULL, 0);
    } else {
        perror("fork failed");
    }
}

int parse_pipeline(char **args, char ****commands_ptr) {
    int cmd_count = 0;
    char ***commands = malloc(MAX_COMMANDS * sizeof(char **));
    
    commands[cmd_count] = malloc(MAX_ARGS * sizeof(char *));
    int arg_index = 0;
    
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "|") == 0) {
            commands[cmd_count][arg_index] = NULL;
            cmd_count++;
            arg_index = 0;
            commands[cmd_count] = malloc(MAX_ARGS * sizeof(char *));
        } else {
            commands[cmd_count][arg_index] = args[i];
            arg_index++;
        }
    }
    commands[cmd_count][arg_index] = NULL;
    cmd_count++;
    
    *commands_ptr = commands;
    return cmd_count;
}
void count_c_files() {
    printf("Counting C files...\n");
    
    // Method 1: Using system call (simpler)
    system("ls *.c 2>/dev/null | wc -l | xargs echo 'Found:'");
    
    // Method 2: Using fork/exec (more educational)
    /*
    pid_t pid = fork();
    if (pid == 0) {
        // Child process: execute the counting command
        execl("/bin/sh", "sh", "-c", "ls *.c 2>/dev/null | wc -l | xargs echo 'Found:'", NULL);
        perror("execl failed");
        exit(1);
    } else if (pid > 0) {
        waitpid(pid, NULL, 0);
    }
    */
}