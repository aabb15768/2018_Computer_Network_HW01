
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <string>
#include <arpa/inet.h>
#include <vector>
#include <thread>
using namespace std;

void receive(int socketFd) {
    char buff2[1024];
    while(true) {
        memset(buff2, 0, sizeof(buff2));
        if((recv(socketFd, buff2, sizeof(buff2), 0)) < 0) {
            cout << "Fail to receive" << endl;
        }
        cout << buff2 << endl;
    }
}


int main(void) {
    // get ip from hostname
    struct hostent* hostToConnet;
    if((hostToConnet = gethostbyname("irc.freenode.net")) == NULL) {
        printf("Unavailable host name\n");
    }
    in_addr* hostAddress = (in_addr*)hostToConnet->h_addr;
    const char* ipAddressFromHost = inet_ntoa(*hostAddress);
    // creat a socket
    int socketFd = 0;
    if((socketFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Fail to creat a socket\n");
    }
    // set servAddress and conncet
    int port = 6667;
    struct sockaddr_in address; //
    struct sockaddr_in servAddress;
    servAddress.sin_family= AF_INET; //set IPv4
    servAddress.sin_port = htons(port); // set port
    servAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // set ip address
    if((connect(socketFd, (struct sockaddr*)&servAddress, sizeof(servAddress))) < 0) {
        printf("Fail to connect");
    }
    //
    char buff[1024];
//    memset(buff, 0, sizeof(buff));
//    strcpy(buff, "NICK bot\r\n");
//    if((send(socketFd, buff, strlen(buff), 0)) < 0) {
//        cout << "Fail to send" << endl;
//    }
//    memset(buff, 0, sizeof(buff));
//    strcpy(buff, "USER b03204032\r\n");
//    if((send(socketFd, buff, strlen(buff), 0)) < 0) {
//        cout << "Fail to send" << endl;
//    }
//    memset(buff, 0, sizeof(buff));
//    strcpy(buff, "JOIN #demo\r\n");
//    if((send(socketFd, buff, strlen(buff), 0)) < 0) {
//        cout << "Fail to send" << endl;
//    }
//    memset(buff, 0, sizeof(buff));
//    strcpy(buff, "PRIVMSG #demo :I'm b03204032\r\n");
//    if((send(socketFd, buff, strlen(buff), 0)) < 0) {
//        cout << "Fail to send" << endl;
//    }
//    char buff2[1024];
//    while(true) {
//        if((recv(socketFd, buff2, strlen(buff2), 0)) < 0) {
//            cout << "Fail to receive" << endl;
//        }
//        cout << buff2 << "\n";
//    }

    
//    char buff2[1024];
    thread receiveThread(receive, socketFd);
    while(true) {
        memset(buff, 0, sizeof(buff));
        cin.getline(buff, sizeof(buff));
        buff[strlen(buff)] = '\n';
        buff[strlen(buff)] = '\0';
        if((send(socketFd, buff, strlen(buff), 0)) < 0) {
            cout << "Fail to send" << endl;
        }
    }
    return 0;
}













