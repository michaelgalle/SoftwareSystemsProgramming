#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define MSG_SIZE 15

int main() {
    int p[2];                       // pipe read and write ends
    char buf[MSG_SIZE];             // read end buffer

    // Create pipe
    if(pipe(p) < 0) {
        perror("pipe creation error");
        exit(1); 
    }

    pid_t pid = fork();             // Duplicate process and create child

    if(pid == 0) {                  // Child process: write to the pipe (Note: child process inherits a COPY of the parents file descriptor table, including the pipe descriptors p[0] and p[1])
        close(p[0]);                // Close the unused read end in child, child will only write
        // Child writes - defensive
        if(write(p[1], "Hello, Parent!", MSG_SIZE) != MSG_SIZE) {     
            perror("pipe write error");
            exit(1);  
        }
        close(p[1]);                // Close write end on child

    } else if (pid > 0) {           // Parent process: Read from pipe
        // COMPLETE: close unused write p[1] end in the parent

        // COMPLETE: Parent reads from pipe 
        
        // COMPLETE: Display buffer contents
        
        // COMPLETE: Close read p[0] end of parent
    }

    return 0;
}

/************************* Solution - No peeking :) ****************************************** */
/* 
int main() {
    int p[2];                       // pipe read and write ends
    char buf[MSG_SIZE];             // read end buffer

    // Create pipe
    if(pipe(p) < 0) {
        perror("pipe creation error");
        exit(1); 
    }

    pid_t pid = fork();             // Duplicate process and create child

    if(pid == 0) {                  // Child process: write to the pipe (Note: child process inherits a COPY of the parents file descriptor table, including the pipe descriptors p[0] and p[1])
        close(p[0]);                // Close the unused read end in child, child will only write
        // Child writes - defensive
        if(write(p[1], "Hello, Parent!", MSG_SIZE) != MSG_SIZE) {     
            perror("pipe write error");
            exit(1);  
        }
        close(p[1]);                // Close write end on child

    } else if (pid > 0) {           // Parent process: Read from pipe
        close(p[1]);                // close unused write end in the parent

        // Parent reads from pipe - defensive
        if(read(p[0], buf, MSG_SIZE) != MSG_SIZE) {
            perror("pipe read error");
            exit(1);  
        }

        // Display buffer contents
        write(STDOUT_FILENO, buf, MSG_SIZE);
        printf("\nParent received: %s\n", buf);   
        
        // Close read end
        close(p[0]);                
    }

    return 0;
}
*/
