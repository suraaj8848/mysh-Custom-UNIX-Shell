#include "mysh.h"

void execute_pipeline(char ***commands, int num_commands) {
    int pipes[num_commands - 1][2];
    pid_t pids[num_commands];

    for (int i = 0; i < num_commands - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe failed");
            return;
        }
    }

    for (int i = 0; i < num_commands; i++) {
        pids[i] = fork();
        
        if (pids[i] == 0) {
            if (i > 0) {
                dup2(pipes[i-1][0], STDIN_FILENO);
            }
            
            if (i < num_commands - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
            }
            
            for (int j = 0; j < num_commands - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            
            execvp(commands[i][0], commands[i]);
            perror("execvp failed");
            exit(1);
        }
    }

    for (int i = 0; i < num_commands - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for (int i = 0; i < num_commands; i++) {
        waitpid(pids[i], NULL, 0);
    }
}

void execute_pipeline_with_timing(char ***commands, int num_commands) {
    int pipes[num_commands - 1][2];
    pid_t pids[num_commands];
    struct timeval start_times[num_commands], end_times[num_commands];

    for (int i = 0; i < num_commands - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe failed");
            return;
        }
    }

    for (int i = 0; i < num_commands; i++) {
        gettimeofday(&start_times[i], NULL);
        pids[i] = fork();
        
        if (pids[i] == 0) {
            if (i > 0) {
                dup2(pipes[i-1][0], STDIN_FILENO);
            }
            
            if (i < num_commands - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
            }
            
            for (int j = 0; j < num_commands - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            
            execvp(commands[i][0], commands[i]);
            perror("execvp failed");
            exit(1);
        }
    }

    for (int i = 0; i < num_commands - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for (int i = 0; i < num_commands; i++) {
        waitpid(pids[i], NULL, 0);
        gettimeofday(&end_times[i], NULL);
    }

    printf("\n--- Execution Profile ---\n");
    for (int i = 0; i < num_commands; i++) {
        double elapsed = (end_times[i].tv_sec - start_times[i].tv_sec) * 1000.0;
        elapsed += (end_times[i].tv_usec - start_times[i].tv_usec) / 1000.0;
        
        printf("[%s] PID: %d, Time: %.3fms\n", 
               commands[i][0], pids[i], elapsed);
    }
    printf("-------------------------\n");
}