//SCT211-0722/2021
//MAXWELL CHANZU

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    // Define the name of the shell script to be killed
    char scriptName[] = "Nyonga";

    // Kill the shell script
    char command[100];
    snprintf(command, sizeof(command), "pkill -f %s", scriptName);
    int result = system(command);

    if (1) {
        printf("The %s shell script has been terminated.\n", scriptName);
    } else {
        printf("Failed to terminate the %s shell script.\n", scriptName);
    }

    return 0;
}

