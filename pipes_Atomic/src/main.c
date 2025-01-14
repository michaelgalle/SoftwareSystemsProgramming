#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#define TOTAL_SIZE (128 * 1024)                         // 128 kB (131,072 bytes) total message size 
#define CHUNK_SIZE  (32 * 1024)                         // 32 kB chunks

int main()
{
    int p[2];
    if(pipe(p) < 0) {
        perror("pipe creation error");
        exit(1); 
    }

    pid_t pid = fork();                                 // Create child process as duplicate of parent from this point

    if (pid == 0) {                                     
        // Child process (Reader) - Reads data in 32 kB chunks at a time
        char chunk_buf[CHUNK_SIZE];                     // chunk buffer (32 kB)
        char* received = (char*)malloc(TOTAL_SIZE);     // receive buffer (128 kB)
        ssize_t B_read;                                 // Bytes read in single read operation                    
        ssize_t total = 0;                              // Bytes read - running total

        
        close(p[1]);                                    // Close unused write end

        // Copy all chunks to the 'receive' buffer 
        while((B_read = read(p[0], chunk_buf, CHUNK_SIZE)) > 0) {   // Read bytes from pipe to chunk buffer in 32 kB chunks
          if(total + B_read <= TOTAL_SIZE) {                        // Overflow check
            memcpy(received + total, chunk_buf, B_read);            // Copy from chunk buffer to the receive buffer 
            total += B_read;                            // Update total count of bytes in receive buffer  
          } else {
            perror("buffer overflow detected");
            exit(1);
          }
        }

        printf("Child read: %zd bytes in receive buffer\n", total); 
        free(received);                                 // Free the received buffer
        close(p[0]);                                    // Close read end of pipe       

    } else if(pid > 0) {
        // Parent process (Writer) - First write operation in the loop fille the pipe buffer completely (64 kB) and then stops writing to prevent overflow
        //                         - Need to keep track of bytes not yet written to send in subsequent write operations
        //                         - Since the read operation in the child frees the pipe buffer in 32 kB chunks, subsequent write operations can only write in 32 kB chunks 
        char buf[TOTAL_SIZE];                           // write buffer
        memset(buf, 'A', TOTAL_SIZE);                   // Fill write buffer with 128k 'A' characters
        ssize_t B_written;                              // Bytes written in single write operation
        ssize_t total = 0;                              // Bytes written - running total

        close(p[0]);                                    // Close unused read end

        while(total < TOTAL_SIZE) {                     // Initially total = 0, write sends 64 kB (max buffer) on first write operation
            B_written = write(p[1], buf + total, TOTAL_SIZE - total);
            if(B_written < 0) { 
                perror("write error"); 
                exit(1); 
            }
            total += B_written;
        }
        printf("Parent wrote a total of %zd bytes\n", total);
        close(p[1]);                                    // Close write end of pipe


    } else { 
        perror("fork failed"); 
        exit(1);
    }

    return 0;
}
