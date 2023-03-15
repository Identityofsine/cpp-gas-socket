#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include "fuelorder.h"
#define PORT 6969


namespace CPPSOCKET{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1; // option
    int addrlen = sizeof(address);
    char buffer[1024] = { 0x00 };
    char* hello = "Message Recieved";
    void interpertMessage(char* buffer, int size);



    bool startSocket(){
        if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
            perror("Socket Failed...");
            return false;
        }
        // if (setsockopt(server_fd, SOL_SOCKET,
        //            SO_REUSEADDR | SO_REUSEPORT, &opt,
        //            sizeof(opt))) {
        //     perror("setsockopt");
        //     return false;
        // }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = htons(INADDR_ANY);
        address.sin_port = htons(PORT);
        return true;
    }
    
    /*
        Only Start when startSocket returns true...
    */
    bool startConnection(){
            // Forcefully attaching socket to the port 6969
        if (bind(server_fd, (struct sockaddr*)&address,
                sizeof(address))
            < 0) {
            perror("bind failed");
            return false;
        }
        if (listen(server_fd, 1) < 0) {
            perror("listen");
            return false;
        }
        while(1){
            bool isExit = true;
            int new_socket = accept(server_fd, (struct sockaddr*)&address,
                        (socklen_t*)&addrlen);
            if(new_socket > 0){
                isExit = false;
            }

            while(new_socket > 0 && !isExit){
                while(*buffer != 0x11){
                    int count = recv(new_socket, buffer, 1024, 0);
                    int sendMSG = send(new_socket, hello, strlen(hello), 0);
                    if(sendMSG == -1){
                        close(new_socket);
                    }
                    if(count == -1) {
                        close(new_socket);
                        isExit = true;
                        break;
                    }
                    else if(count == 0) {
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

