//SCT211-0722/2021
//MAXWELL CHANZU

#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t child_pid;

    child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (child_pid == 0) {
        // This code is executed by the child process
        printf("Child process: My PID is %d. My parent's PID is %d.\n", getpid(), getppid());
    } else {
        // This code is executed by the parent process
        printf("Parent process: My PID is %d. My child's PID is %d.\n", getpid(), child_pid);
    }

    return 0;
}

