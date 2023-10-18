//SCT211-0722/2021
//MAXWELL CHANZU

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid;
    int status;

    child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (child_pid == 0) {
        // Child process
        printf("Normal implementation:Child process: My PID is %d.\n", getpid());
        exit(42); 
        // Child exits with status 42
    } else {
        // Parent process
        printf("Parent process: My PID is %d.\n", getpid());

        // Using waitpid
        if (waitpid(child_pid, &status, 0) > 0) {
            if (WIFEXITED(status)) {
                printf("Waitpid implementation: process exited with status: %d\n", WEXITSTATUS(status));
            }
        }

        // Using wait
        //if (wait(&status) > 0) {
        //     if (WIFEXITED(status)) {
        //         printf("Wait implementation: Child process exited with status: %d\n", WEXITSTATUS(status));
        //     }
        // }
    }

    return 0;
}

