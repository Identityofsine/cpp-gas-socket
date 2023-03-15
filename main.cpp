#include<stdio.h>
#include<iostream>
#include "socket-server.h"

int main(){
    printf("socket launched\n");
   
    CPPSOCKET::startSocket();
    CPPSOCKET::startConnection();
    
    
    return 0;
}