// Signal examples - SIGINT and SIGPIPE 
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

// SIGINT handler function
void sigint_h(int sig) {
    printf("\nReceived SIGINT (signal number: %d). Gracefully shutting down ...\n", sig);
    exit(0);                                                // exits the program cleanly
}

// Test SIGINT 
int sigint() {

    // Register the signal handler for SIGINT
    if(signal(SIGINT, sigint_h) == SIG_ERR) {
        perror("Error registering signal handler");
        return(1);
    }

    printf("\nPress Ctrl+C to trigger SIGINT. Use Ctrl+\\ to quit forcefully.\n");

    // Keep running program in infinite loop
    while(1) {
        printf("Program is running ... Press Ctrl+C to interrupt using SIGINT and exit gracefully, Ctrl+\\ to quit forcefully\n");
        sleep(2);
    }
    return 0;
}


// SIGPIPE handler function
void sigpipe_h(int sig) {
    printf("Caught SIGPIPE (signal number: %d). No readers on the pipe!\n", sig);
}

// Test SIGPIPE
int sigpipe() {
    int p[2];

    // Create a pipe
    if(pipe(p) < 0) {
        perror("Pipe creation error");
        return(1); // Error
    }

    // Register a signal handler for SIGPIPE
    if(signal(SIGPIPE, sigpipe_h) == SIG_ERR) {
        perror("Signal handler registration error"); 
        return(1); // Error
    }

    // Single process pipe where we close the read end to simulate no readers
    close(p[0]);

    // Now try writing to the pipe that has no readers (read end closed)
    if(write(p[1], "\nThis will trigger SIGPIPE signal", 33 ) < 0) {
        perror("Error writing to pipe"); 
    } 

    // Close the write end of the pipe
    close(p[1]);

    printf("\nProgram complete");
    return(0);

} 


int main() {
    // sigint();            // Uncomment to run
    sigpipe();              // uncomment to run

    return(0);
}