
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <string>
#include <arpa/inet.h>
#include <vector>
#include <thread>
#include <ctype.h>
using namespace std;

// construct TCP connecting
int TCPConnect(char* hostName, char* ipAddress) {
    
    char hostNameToConnect[64];
    strcpy(hostNameToConnect, hostName);
    char ipAddressToConnect[64];
    strcpy(ipAddressToConnect, ipAddress);
    // get ip from hostname
    struct hostent* hostToConnet;
    if((hostToConnet = gethostbyname(hostNameToConnect)) == NULL) {
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
    servAddress.sin_addr.s_addr = inet_addr(ipAddressToConnect); // set ip address
    if((connect(socketFd, (struct sockaddr*)&servAddress, sizeof(servAddress))) < 0) {
        printf("Fail to connect");
    }
    
    return socketFd;
}

void signUpICR(int socketFd, string channel) {
    char buff[1024];
    memset(buff, 0, sizeof(buff));
    strcpy(buff, "NICK bot\r\n");
    if((send(socketFd, buff, strlen(buff), 0)) < 0) {
        cout << "Fail to send" << endl;
    }
    memset(buff, 0, sizeof(buff));
    strcpy(buff, "USER b03204032\r\n");
    if((send(socketFd, buff, strlen(buff), 0)) < 0) {
        cout << "Fail to send" << endl;
    }
    memset(buff, 0, sizeof(buff));
    string tempString = "JOIN #" + channel + "\r\n";
    strcpy(buff, tempString.c_str());
    if((send(socketFd, buff, strlen(buff), 0)) < 0) {
        cout << "Fail to send" << endl;
    }
    memset(buff, 0, sizeof(buff));
    tempString = "PRIVMSG #" + channel + " :I'm b03204032\r\n";
    strcpy(buff, tempString.c_str());
    if((send(socketFd, buff, strlen(buff), 0)) < 0) {
        cout << "Fail to send" << endl;
    }

}

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

bool isRecvBlock(string recvString) {
    string del = "PRIVMSG";
    size_t privmsgPos = recvString.find(del, 0);
    if( privmsgPos == string::npos) {
        return true;
    }
    return false;
}

int recvStringParsing(string recvString,string &nameToSend, string &messageReceived) {
    string del = "PRIVMSG bot :";
    size_t privmsgPos = recvString.find(del, 0);
    if(privmsgPos == string::npos) {
        return 0;
    }
    privmsgPos += del.length();
    messageReceived = recvString.substr(privmsgPos, recvString.length()-privmsgPos);
    messageReceived.pop_back(); // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    messageReceived.pop_back(); // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    del = "!";
    size_t exclaPos = recvString.find(del, 0);
    nameToSend = recvString.substr(1, exclaPos-1);
    return 1;
}

int recvNumParsing(string &recvString,string &messageRecv) {
    bool isDigit = true;
    string del = "PRIVMSG bot :";
    size_t privmsgPos = recvString.find(del, 0);
    if(privmsgPos == string::npos) {
        return 0;
    }
    privmsgPos += del.length();
    messageRecv = recvString.substr(privmsgPos, recvString.length()-privmsgPos);
    for(int i = 0; i < messageRecv.length()-2; i++) {
        if(isdigit(messageRecv[i]) == false) {
            isDigit = false;
            break;
        }
    }
    if(isDigit == false) {
        cout << "no";
        return 0;
    } else {
        cout << "yes";
        return atoi(messageRecv.c_str());
    }
    
}

bool messageQuery(string &messageReceived, string &messageResponse, int socketFd, string name) {
    // Capricorn, Aquarius, Pisces, Aries, Taurus, Gemini, Cancer, Leo, Virgo, Libra, Scorpio, Sagittarius
    if(messageReceived.compare("Capricorn") == 0) {
        messageResponse = "nice day!";
        return true;
    } else if (messageReceived.compare("Aquarius") == 0) {
        messageResponse = "nice day!";
        return true;
    } else if (messageReceived.compare("Pisces") == 0) {
        messageResponse = "nice day!";
        return true;
    } else if (messageReceived.compare("Aries") == 0) {
        messageResponse = "nice day!";
        return true;
    } else if (messageReceived.compare("Taurus") == 0) {
        messageResponse = "nice day!";
        return true;
    } else if (messageReceived.compare("Gemini") == 0) {
        messageResponse = "nice day!";
        return true;
    } else if (messageReceived.compare("Cancer") == 0) {
        messageResponse = "nice day!";
        return true;
    } else if (messageReceived.compare("Leo") == 0) {
        messageResponse = "nice day!";
        return true;
    } else if (messageReceived.compare("Virgo") == 0) {
        messageResponse = "nice day!";
        return true;
    } else if (messageReceived.compare("Libra") == 0) {
        messageResponse = "nice day!";
        return true;
    } else if (messageReceived.compare("Scorpio") == 0) {
        messageResponse = "nice day!";
        return true;
    } else if (messageReceived.compare("Sagittarius") == 0) {
        messageResponse = "nice day!";
        return true;
    }
    // guess number
    if(messageReceived.compare("!guess") == 0) {
        int down = 1;
        int bingo = 5;
        int up = 10;
        bool isLose = true;
        char buff[1024];
        memset(buff, 0, sizeof(buff));
        string stringGuess;
        stringGuess = "PRIVMSG " + name + " :" + "guess a number between 1 and 10!(not include 1 and 10)\r\n";
        strcpy(buff, stringGuess.c_str());
        if((send(socketFd, buff, strlen(buff), 0)) < 0) {
            cout << "Fail to send" << endl;
        }
        while (isLose) {
            memset(buff, 0, sizeof(buff));
            if((recv(socketFd, buff, sizeof(buff), 0)) < 0) {
                cout << "Fail to receive" << endl;
            }
            string recvString = buff;
            string messageRecv;
            int status = recvNumParsing(recvString, messageRecv);
            if(status == 0) {
                continue;
            }
            if(status > (up-1) || status < (down+1)) {
                continue;
            }
            if(status == bingo) {
                memset(buff, 0, sizeof(buff));
                stringGuess = "PRIVMSG " + name + " :bingo!\r\n";
                strcpy(buff, stringGuess.c_str());
                if((send(socketFd, buff, strlen(buff), 0)) < 0) {
                    cout << "Fail to send" << endl;
                }
                isLose = false;
                break;
            }
            if(status > bingo && status < up) {
                up = status;
                memset(buff, 0, sizeof(buff));
                stringGuess = "PRIVMSG " + name + " :between " + to_string(down) + " and " + to_string(up) + "!\r\n";
                strcpy(buff, stringGuess.c_str());
                if((send(socketFd, buff, strlen(buff), 0)) < 0) {
                    cout << "Fail to send" << endl;
                }
            } else if (status < bingo && status > down) {
                down = status;
                memset(buff, 0, sizeof(buff));
                stringGuess = "PRIVMSG " + name + " :between " + to_string(down) + " and " + to_string(up) + "!\r\n";
                strcpy(buff, stringGuess.c_str());
                if((send(socketFd, buff, strlen(buff), 0)) < 0) {
                    cout << "Fail to send" << endl;
                }
            }
        }
        return false;
    }
    return true;
}

void sendString(int socketFd, string recvString) {
    string messageReceived;
    string nameToSend;
    string messageResponse;
    int statusNum = recvStringParsing(recvString, nameToSend, messageReceived);
    if(statusNum == 0) {
        return;
    }
    bool isSendMessage = true;
    isSendMessage = messageQuery(messageReceived, messageResponse, socketFd, nameToSend);
    if(isSendMessage == false) {
        return;
    }
    string stringToSend = "PRIVMSG " + nameToSend + " :" + messageResponse + "\r\n";
    char buffSend[1024];
    memset(buffSend, 0, sizeof(buffSend));
    strcpy(buffSend, stringToSend.c_str());
    if((send(socketFd, buffSend, strlen(buffSend), 0)) < 0) {
        cout << "Fail to send" << endl;
    }
    return;
}

int main(void) {
    // Set connecting information
    char hostNameToConnect[64] = "irc.freenode.net";
    char ipAddressToConnect[64] = "127.0.0.1";
    string channel = "demo";
    // Construct TCP connecting
    int socketFd = TCPConnect(hostNameToConnect, ipAddressToConnect);
    // Set nickname, user, join channel
    signUpICR(socketFd, channel);
    char buffRec[1024];
//    thread receiveThread(receive, socketFd);
    while(true) {
        memset(buffRec, 0, sizeof(buffRec));
        if((recv(socketFd, buffRec, sizeof(buffRec), 0)) < 0) {
            cout << "Fail to receive" << endl;
        }
        string recvString = buffRec;
        sendString(socketFd, recvString);
        // do
    }
    return 0;
}













