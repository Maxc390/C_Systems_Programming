//SCT211-0722/2021
//MAXWELL CHANZU

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Define a custom signal handler function
void customSignalHandler(int signal) {
    if (signal == SIGUSR1) {
        printf("Custom signal received.\n");
    }
}
int main() {

    char character[10];
    //input character
    printf("input character: ");
    scanf("%s",character);

    //checks if / is pressed by user
    if (character == "/"){
    // Setting up the custom signal handler
    signal(SIGUSR1, customSignalHandler);
    
    }
    
    printf("Sending a custom signal...\n");
    kill(getpid(), SIGUSR1); // Send the custom signal to itself

    pause(); // Wait for the signal handler to execute

    return 0;
}

