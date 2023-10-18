//SCT211-0722/2021
//MAXWELL CHANZU

#include <stdio.h>
#include <unistd.h>

int main() {
    // Getting  the Process ID (PID)
    pid_t pid = getpid();

    // Getting the Parent Process ID (PPID)
    pid_t ppid = getppid();

    printf("Process ID (PID): %d\n", pid);
    printf("Parent Process ID (PPID): %d\n", ppid);

    return 0;
}

