#include "mysh.h"

int main() {
    char *line;
    char *args[MAX_ARGS];
    int should_run = 1;

    printf("Welcome to mysh! Type 'exit' to quit.\n");
    while (should_run) {
        print_prompt();
        line = read_line();
        if (line == NULL) continue;

        if (strcmp(line, "exit") == 0) {
            free(line);
            break;
        }

        int num_args = parse_line(line, args);
        if (num_args == 0) {
            free(line);
            continue;
        }

        // ▼▼▼ ADD COUNTC COMMAND HANDLING HERE ▼▼▼
        if (strcmp(args[0], "countc") == 0) {
            count_c_files();
        } else if (is_trace_command(args)) {
        // ▲▲▲ END OF ADDED CODE ▲▲▲
            char pipeline_cmd[MAX_INPUT_LENGTH] = "";
            for (int i = 1; i < num_args; i++) {
                if (i > 1) strcat(pipeline_cmd, " ");
                strcat(pipeline_cmd, args[i]);
            }

            char *pipeline_args[MAX_ARGS];
            int pipeline_arg_count = parse_line(pipeline_cmd, pipeline_args);
            if (pipeline_arg_count > 0) {
                char ***commands;
                int num_commands = parse_pipeline(pipeline_args, &commands);
                execute_pipeline_with_timing(commands, num_commands);
                
                for (int i = 0; i < num_commands; i++) {
                    free(commands[i]);
                }
                free(commands);
            }
        } else {
            int has_pipe = 0;
            for (int i = 0; i < num_args; i++) {
                if (strcmp(args[i], "|") == 0) {
                    has_pipe = 1;
                    break;
                }
            }

            if (has_pipe) {
                char ***commands;
                int num_commands = parse_pipeline(args, &commands);
                execute_pipeline(commands, num_commands);
                
                for (int i = 0; i < num_commands; i++) {
                    free(commands[i]);
                }
                free(commands);
            } else {
                execute_command(args);
            }
        }

        free(line);
    }

    return 0;
}