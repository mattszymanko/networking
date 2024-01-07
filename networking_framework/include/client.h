#pragma once

#include <iostream>
#include <thread>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

class Client {
public:
    Client(const std::string& serverIP, int serverPort);
    ~Client();

    void Connect();
    void Disconnect();
    void Send(const std::string& message);

private:
    void ReceiveMessages();

    std::string serverIP;
    int serverPort;
    int clientSocket;
    std::thread receiveThread;
    bool connected;
};
