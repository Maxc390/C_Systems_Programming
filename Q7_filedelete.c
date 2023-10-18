//SCT211-0722/2021
//MAXWELL CHANZU

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_alarm(int signal) {
    if (unlink("JUJU") == 0) {
        printf("File 'JUJU' has been deleted.\n");
    } else {
        perror("Error deleting the file.");
    }
    exit(0);
}

int main() {
    FILE *file = fopen("JUJU", "w");
    if (file == NULL) {
        perror("Error creating the file.");
        return 1;
    }
    fclose(file);

    printf("File 'JUJU' has been created.\n");

    printf("You have 5 seconds before the file is deleted \n");
    signal(SIGALRM, handle_alarm);
    
    alarm(5);
    
    while (1) {
        // Keep the program running to allow time for the signal to trigger
        // You can add additional logic here if needed
        
    }

    return 0;
}

