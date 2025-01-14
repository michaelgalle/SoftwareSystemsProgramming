#include <stdio.h>                              
#include <stdlib.h>
#include <unistd.h>                             // File I/O system calls

#define MSG_SIZE 14                             // small static size used (will study writes larger than buffer later)
char* msg = "hello, world\n";                   // send buffer for write end of the single process pipe

// Exercise - Complete the missing sections of code
int main() {
    char buf[MSG_SIZE];                         // receive buffer for read end of the single process pipe
    int p[2];                                   // pipe read p[0] and write p[1] ends

    if(pipe(p) < 0) {                           // Defensive
        perror("pipe failed");
        exit(1);
    }

    // COMPLETE: write msg to pipe at p[1] to a max of MSG_SIZE
    

    // COMPLETE: read from pipe at p[0] and store in buf, to a max of MSG_SIZE
    

    // COMPLETE: Print the contents of the buffer to the console (printf() equivalent)
    
    
    // COOMPLETE: Close both pipe ends
    

    return 0;
}


/********************** Solution - No peeking *****************************/
/*
int main() {
    char buf[MSG_SIZE];                         // receive buffer for read end of the single process pipe
    int p[2];                                   // pipe read p[0] and write p[1] ends

    if(pipe(p) < 0) {                           // Defensive
        perror("pipe failed");
        exit(1);
    }

    // write msg to pipe at p[1] to a max of MSG_SIZE
    if(write(p[1], msg, MSG_SIZE) != MSG_SIZE) {        // Defensive write
        perror("write failed");
        exit(1);
    }

    // read from pipe at p[0] and store in buf, to a max of MSG_SIZE
    if(read(p[0], buf, MSG_SIZE) != MSG_SIZE) {         // Defensive read
        perror("read failed");
        exit(1);
    }

    // Print the contents of the buffer to the console (printf() equivalent)
    printf("\nReceived message is: %s \n", buf);
    write(STDOUT_FILENO, buf, MSG_SIZE);
    
    // Close both pipe ends
    close(p[0]);
    close(p[1]);

    return 0;
}
*/