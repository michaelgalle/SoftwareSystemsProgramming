#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid = fork();     // Create child process

    if(pid == 0) {          
        // Child process - fork call returns 0 in the child process
        printf("\nChild process PID using getpid(): %d\n", getpid());   // Absolute PID
        printf("Child process PID value: %d\n", pid);                   // 0 since fork call returns this in child process

        // Test out one of the the exec*() functions (i.e. execl()) that replace the current (child) process with another 
        execl("/bin/ls", "ls", NULL);                                   // Replace child process with 'ls' and run it (show files in current folder)

    } else if (pid > 0) {   
        // Parent process - fork call returns absolute process ID in parent
        printf("\nParent process PID: %d\n", getpid());                 // Absolute PID
        printf("Parent process PID value: %d\n", pid);                  // Absolute PID

    } else {
        perror("fork failed");
        
    }
    return 0;
}
