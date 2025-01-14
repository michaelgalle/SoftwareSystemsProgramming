#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0) {                 // Child process
        printf("Child process running ...\n");
        sleep(2);                   // Simulate work in child - parent must wait for it to complete
        printf("Child process complete.\n");
    
    } else if (pid > 0) {           // Parent process
        printf("Parent waiting for child process to complete ...\n");
        wait(NULL);                 // Wait for child to die

    } else {                        // Error in fork
        perror("fork failed");
    }

    return 0;
}