# server code from: https://shakeelosmani.wordpress.com/2015/04/13/python-3-socket-programming-example/

import socket                                   # import python sockets library

def Main():                                     # define the main function
    host = "127.0.0.1"                       # CHANGE THIS!!! - Define host variable as IP address of server (use IPCONFIG to get your IP address on the network) - Use 127.0.0.1 if client/server on same computer
    port = 51234                                # define port to listen for a connection (> 1024)

    mySocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # define mySocket as an instance of a python socket, socket.socket(AF_INET, SOCK_DGRAM for UDP or SOCK_STREAM for TCP)
    mySocket.bind((host, port))                 # bind take a tuple as input (bind the host and port to the socket created above) 

    mySocket.listen(1)                          # 1 means perpetually listen until the connection is closed
    conn, addr = mySocket.accept()              # conn and addr hold the connection and address of the client
    print("Connection from: " + str(addr))      # print the clients address
    while True:
        data = conn.recv(1024).decode()         # decode() necessary in python 3
        if not data:
            break
        print("from connected user: " + str(data))

        data = str(data).upper()
        print("sending: " + str(data))
        conn.send(data.encode())
    conn.close()

if __name__ == '__main__':
    Main()
