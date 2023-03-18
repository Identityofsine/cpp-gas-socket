#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include "fuelorder.h"
#define PORT 6969          // Port number used for the connection


// Namespace for encapsulating functions and variables related to sockets
namespace CPPSOCKET {
    int server_fd, new_socket, valread;      // File descriptors and variable for storing bytes read
    struct sockaddr_in address;              // Structure for storing the address information
    int opt = 1;                             // Option variable used for setting socket options
    int addrlen = sizeof(address);           // Length of the address
    char buffer[1024] = { 0x00 };            // Buffer for storing received data
    char* hello = "Message Received";        // Message to be sent back to the client

    // Function for initializing the socket
    bool startSocket() {
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            // If socket creation fails, display error message and return false
            perror("Socket Failed...");
            return false;
        }
        
        // Set the address family, IP address and port number for the connection
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = htons(INADDR_ANY);
        address.sin_port = htons(PORT);
        
        // Return true if socket initialization is successful
        return true;
    }
    
    // Function for starting the connection
    bool startConnection() {
        // Bind the socket to the specified address and port
        if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
            // If binding fails, display error message and return false
            perror("bind failed");
            return false;
        }
        
        // Listen for incoming connections
        if (listen(server_fd, 1) < 0) {
            // If listening fails, display error message and return false
            perror("listen");
            return false;
        }
        
        // Loop continuously to handle incoming connections
        while (1) {
            bool isExit = true; // Boolean flag to keep track of whether the connection has ended
            // Accept a new connection
            int new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
            if (new_socket > 0) {
                isExit = false;
            }

            // Receive data from the client and send a response back
            while (new_socket > 0 && !isExit) {
                while (*buffer != 0x11) {
                    // Receive data from the client and store it in the buffer
                    int count = recv(new_socket, buffer, 1024, 0);
                    // Send a response back to the client
                    int sendMSG = send(new_socket, hello, strlen(hello), 0);
                    if (sendMSG == -1) {
                        // If sending fails, close the connection and exit the loop
                        close(new_socket);
                    }
                    if (count == -1) {
                        // If receiving fails, close the connection and exit the loop
                        close(new_socket);
                        isExit = true;
                        break;
                    }
                    else if (count == 0) {
                        // If the client has closed the connection, close the connection and exit the loop
                        close(new_socket);
                        isExit = true;
                        continue;
                    }
                    else {
                        interpertMessage(buffer, sizeof(buffer));   
                    }
                }
            }

        }

        return true;


    }

    bool shutdownServer(){
        // closing the connected socket
        close(new_socket);
        // closing the listening socket
        shutdown(server_fd, SHUT_RDWR);
    }


    void interpertMessage(char* buffer, int size){

        Fuel::FuelType ft = NULL;
        if(buffer[0] != 0x00){
            perror("Invalid Message\n");
            return;
        } else if(buffer[0] == 0x11){
            return;
        }
        switch(buffer[1]){
            case 0x01:
                printf("gas : e87\n");
                break;
            case 0x02:
                printf("gas : e89\n");
                break;
            case 0x03:
                printf("gas : e91\n");
                break;
            case 0x04:
                printf("gas : disel\n");
                break;
            default:
                perror("Invalid Second Byte!\n");
                return;
        }
        ft = Fuel::FuelType(buffer[1]);
        double price = (int)buffer[2];
        price += ((int)buffer[3]) / 100;
        int pump = (int)buffer[4];
        Fuel::FuelOrder fuelOrder = Fuel::FuelOrder(ft, price, pump);
        printf("%s, cost : %f on pump : %d\n", fuelOrder.getFuelType().name, fuelOrder.getPrice(), fuelOrder.getPump());


    }

}

