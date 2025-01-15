// client.c - Client side of the client serversockets example
// By: Michael Galle

// Commmon C headers 
#include <stdio.h>           
#include <string.h> 
#include <ctype.h> 
#include <stdlib.h>

// Headers for socket functions
#include <unistd.h>
#include <sys/types.h>      
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>       
#include <netdb.h>

#define PORT 5000      

int main(int argc, char *argv[]) {
    // Set up sockets 
    char buffer[BUFSIZ]; 
    int client_socket;
    int len;
    int addr;
    struct sockaddr_in server_addr; 
    struct hostent* host;

    if ((host = gethostbyname(argv[1])) == NULL) {
        printf("\nPlease enter a valid server IP address\n");
        return(2); 
    }

    memcpy(&addr, host->h_addr_list[0], host->h_length);           // #define h_addr h_addr_list[0]

    // Create socket

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nError setting up client socket\n"); 
        return(3); 
    }

    // Connect the client to the server
    
    // Set up the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;                              
    server_addr.sin_addr.s_addr = addr; 
    server_addr.sin_port = htons(PORT);

    // Attempt to connect to server
    if(connect(client_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) { 
        printf("\nError: can't connect to server\n"); 
        close(client_socket); 
        return(4);
    }

    // Create a message to send to server
    printf("\nEnter message for server: ");
    fflush(stdout);
    fgets(buffer, sizeof(buffer), stdin); 
    if(buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = '\0';
    }

    // Send the message using the write() command
    write(client_socket, buffer, strlen(buffer)); 


    // Read back any messages that return from the server
    len = read(client_socket, buffer, sizeof(buffer)); 
    printf("\nServer response: %s\n", buffer); 

    // Close connection
    close(client_socket);
    printf("\nConnection terminated\n");

    return(0);                          // success

}     


