// server.c - Server side of the client serversockets example
// By: Michael Galle

// Common C headers with common functions and constants  
#include <stdio.h>			// BUFSIZ defined here 
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Headers with definition and implementation of socket functions in Linux
#include <unistd.h>
#include <sys/types.h>		// defines u_short
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>		// htons() function defined here
#include <netdb.h>

// Additional server side functions
#include <signal.h>
#include <sys/wait.h>		// Server must wait for communication from client 

#define PORT 5000			// Server set up to listen to port 5000

int main(void) { 
    char buffer[BUFSIZ]; 
    int server_socket;       // Listening socket
    int client_socket;       // Unique socket for every client
    int client_len; 
    struct sockaddr_in  client_addr;    // Struct containing the address info for socket set up for each client
    struct sockaddr_in  server_addr;    // Server address to listen for incoming connections
    int len, i;

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0))< 0) {
        printf("\nError: cannot create server socket\n");
        return(1); 
    } 

    // Bind the created socket to an address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl (INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if(bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr))< 0) {
        printf("\nError: Binding to server socket\n");
        close(server_socket);
        return(2);
    }

    // Listen for incoming connections on port (PORT)
    if( listen(server_socket, 1) < 0) {                   // 1 means maximum clients is only 1 (one connection at a time)
        printf("\nError: listening\n"); 
        close(server_socket);
        return(3);
    }

    // If client connection incoming (listen() command successful)
    client_len = sizeof(client_addr); 
    if((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len))< 0) {
        printf("Error: accepting client connection");
        close(server_socket);
        return(4);
    }

    // Read from client socket (data sent from client)
    read(client_socket, buffer, BUFSIZ); 
    printf("Message from client: %s\n", buffer);

    // Send message back to the client
    strcat(buffer, " is the message recieved by the server\n");
    len = strlen(buffer); 
    write(client_socket, buffer, len);

    // Close the socket
    close(client_socket);           // Closes connection between client and server
    close(server_socket);           // Closes the servers listening socket

    return(0);                      // success



}
