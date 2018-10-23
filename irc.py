# -*- coding: utf-8 -*-
import requests
import sys
import socket
import thread

class Str :
    def _init_(self):
        self.str = ""

def webCrawler(query) :
    r = query
    s = 'https://www.youtube.com/results?search_query='
    s = s + r
    s = bytes(s.encode('utf8'))
    r = requests.get(s)
    s = r.text.encode('utf8', 'ignore')
    s = str(s)
    delim = 'href="/watch?v='
    index = s.find(delim)
    index2 = s.find('"', index+len(delim))
    temp = 'https://www.youtube.com'
    output = temp + s[index+6:index2]
    return output

def signUpIRC(channelName, clientSocket) :
    message = "NICK bot\r\nUSER b03204032\r\n"
    clientSocket.send(bytes(message.decode('utf8').encode('utf8')))
    message = "JOIN #" + channelName + "\r\nPRIVMSG #" + channelName + " :I'm b03204032\r\n"
    clientSocket.send(bytes(message.decode('utf8').encode('utf8')))

def sendThread(clientSocket, nameToSend) :
    isExit = False
    buff = ""
    while True:
        strToInput = raw_input()
        if strToInput == "!e" :
            isExit = True
        if isExit == True :
            break
        # strToInput = "PRIVMSG " + nameToSend.str + " :" + strToInput.str + "\r\n"
        clientSocket.send("PRIVMSG ")
        clientSocket.send(bytes(nameToSend.str.decode('utf8').encode('utf8')))
        clientSocket.send(" :")
        clientSocket.send(bytes(strToInput.decode('utf8').encode('utf8')))
        clientSocket.send("\r\n")
    print("你離開了聊天室")
    return

def recvMsgParsing(msg) :
    orgMessage = msg.str
    delim = "PRIVMSG bot :"
    index = msg.str.find(delim)
    if index == -1 :
        return 0
    index += len(delim)
    msg.str = orgMessage[index:len(orgMessage)]
    while msg.str[len(msg.str)-1] == '\n' or msg.str[len(msg.str)-1] == '\r':
        msg.str = msg.str[0:len(msg.str)-1]

def recvNumParsing(msg) :
    orgMessage = msg.str
    isDigit = True
    delim = "PRIVMSG bot :"
    index = msg.str.find(delim)
    if index == -1 :
        return 0
    index += len(delim)
    msg.str = orgMessage[index:len(orgMessage)]
    while msg.str[len(msg.str)-1] == '\n' or msg.str[len(msg.str)-1] == '\r':
        msg.str = msg.str[0:len(msg.str)-1]
    if msg.str.isdigit() == False :
        return 0
    else :
        return int(msg.str)

def messageQuery(message, response, clientSocket, nameToSend) :
    if message.str == "Capricorn" :
        response.str = "nice day!"
        return True;
    elif message.str == "Aquarius" :
        response.str = "nice day!"
        return True;
    elif message.str == "Pisces" :
        response.str = "nice day!"
        return True;
    elif message.str == "Aries" :
        response.str = "nice day!"
        return True;
    elif message.str == "Taurus" :
        response.str = "nice day!"
        return True;
    elif message.str == "Gemini" :
        response.str = "nice day!"
        return True;
    elif message.str == "Cancer" :
        response.str = "nice day!"
        return True;
    elif message.str == "Leo" :
        response.str = "nice day!"
        return True;
    elif message.str == "Virgo" :
        response.str = "nice day!"
        return True;
    elif message.str == "Libra" :
        response.str = "nice day!"
        return True;
    elif message.str == "Scorpio" :
        response.str = "nice day!"
        return True;
    elif message.str == "Sagittarius" :
        response.str = "nice day!"
        return True;

    if message.str == "!chat" :
        while nameToSend.str[len(nameToSend.str)-1] == '\n' or nameToSend.str[len(nameToSend.str)-1] == '\r':
            nameToSend.str = nameToSend.str[0:len(nameToSend.str)-1]
        print(nameToSend.str)
        print("加入了聊天室！")
        garbNum = -1
        thread.start_new_thread(sendThread, (clientSocket, nameToSend, ))
        while True:
            msg = Str()
            msg.str = clientSocket.recv(4096).decode('utf8')
            garbNum = recvMsgParsing(msg)
            if garbNum == 0 :
                continue
            if msg.str == "!bye" :
                print(nameToSend.str)
                print("離開了聊天室\n")
                break
            print(msg.str)

    if message.str == "!guess" :
        down = 1
        bingo = 5
        up = 10
        isLose = True
        response = "PRIVMSG " + nameToSend.str + " :" + "guess a number between 1 and 10!(not include 1 and 10)\r\n"
        clientSocket.send(bytes(response.decode('utf8').encode('utf8')))
        while isLose == True :
            msg = Str()
            msg.str = clientSocket.recv(4096).decode('utf8')
            staus = recvNumParsing(msg)
            if staus == 0 :
                continue
            if staus == bingo :
                response = "PRIVMSG " + nameToSend.str + " :bingo!\r\n"
                clientSocket.send(bytes(response.decode('utf8').encode('utf8')))
                isLose = False
                break;
            if staus > bingo and staus < up :
                up = staus
                response = "PRIVMSG " + nameToSend.str + " :between " + str(down) + " and " + str(up) + "!\r\n"
                clientSocket.send(bytes(response.decode('utf8').encode('utf8')))
            elif staus < bingo and staus > down :
                down = staus
                response = "PRIVMSG " + nameToSend.str + " :between " + str(down) + " and " + str(up) + "!\r\n"
                clientSocket.send(bytes(response.decode('utf8').encode('utf8')))



    if message.str[0:5] == "!song" :
        response.str = webCrawler(message.str[6:len(message.str)])
        return True;
        # response.str = webCrawler()
    return False;

def messageParsing(message, nameToSend) :
    orgMessage = message.str
    delim = "PRIVMSG bot :"
    index = message.str.find(delim)
    if index == -1 :
        return 0
    index += len(delim)
    message.str = orgMessage[index:len(orgMessage)]
    while message.str[len(message.str)-1] == '\n' or message.str[len(message.str)-1] == '\r':
        message.str = message.str[0:len(message.str)-1]
    delim = "!"
    index = orgMessage.find(delim)
    nameToSend.str = orgMessage[1:index]
    return 1
def sendString(clientSocket, message) :
    nameToSend = Str()
    response = Str()
    statusNum = messageParsing(message, nameToSend)
    if statusNum == 0 :
        return
    isSendMessage = True;
    isSendMessage = messageQuery(message, response, clientSocket, nameToSend)
    if isSendMessage == False :
        return
    stringToSend = "PRIVMSG " + nameToSend.str + " :" + response.str + "\r\n"
    clientSocket.send(bytes(stringToSend.decode('utf8').encode('utf8')))
def main() :
    #lack gethostname
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    hostIp = "127.0.0.1"
    portNumber = 6667
    channelName = "demo"
    clientSocket.connect((hostIp, portNumber))
    signUpIRC(channelName, clientSocket)
    while True :
        msg = clientSocket.recv(4096).decode('utf8')
        message = Str()
        message.str = msg
        sendString(clientSocket, message)
    return

main()
