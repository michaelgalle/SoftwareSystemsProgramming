#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_READ 100                                                            // Max number of bytes to read from file

int main() {
    int fd;

    // Open file for reading and writing (create it if it does not exist)
    if( (fd = open("textfile.txt", O_RDWR | O_CREAT | O_APPEND, 0644))  <  0 ) {           // Open for read/write or create file - permissions 644 (USER, GROUP, OTHER)
        perror("\nError opening file");                                         // Remove the | O_APPEND flag if you want to start writing from the begining of the file every time
        exit(1);
    }

    // Write to the file 
    const char* text = "Hello, world!\n";                                       // write buffer
    ssize_t B_written = write(fd, text, strlen(text)); 
    if(B_written < 0) {
        perror("\nError writing to file");
        close(fd);
        exit(1);
    } else {
        printf("\nSuccessful write of %zd bytes to file", strlen(text)); 
    }

    // Reset the file offset to the beggining of the file
    lseek(fd, 0, SEEK_SET);

    // Read from the file
    char buf[MAX_READ];                                                         // Read buffer - only reads first MAX_READ bytes of the file
    ssize_t B_read;
    
    if( (B_read = read(fd, buf, MAX_READ)) < 0  ) {
        perror("\nError reading from file");
        close(fd);
        exit(1); 
    }

    buf[B_read] = '\0';                                                        // Add string termination char needed by printf()
    printf("\nSuccessfully read %zd bytes from file", B_read);                 // Display results
    printf("\n\nFIRST %d BYTES OF FILE: \n %s", MAX_READ, buf);
    close(fd);                                                                 // Close the file

    return 0;
}
