
//SCT211-0722/2021
//MAXWELL CHANZU

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>




// Define a custom signal handler function
void customSignalHandler(int signal) {
    if (signal == SIGUSR1) {
        printf("Child: Custom signal received from parent.\n");
    }
}

int main() {
    pid_t child_pid;

    child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (child_pid == 0) {
        // Child process
        signal(SIGUSR1, customSignalHandler);
        printf("Child: Waiting for a custom signal from the parent...\n");
        pause();
    } else {
        // Parent process
        sleep(1);  // Wait for the child to set up the signal handler
        printf("Parent: Sending a custom signal to the child...\n");
        kill(child_pid, SIGUSR1);
    }

    return 0;
}

