#include "client.h"

Client::Client(const std::string& serverIP, int serverPort) : serverIP(serverIP), serverPort(serverPort), connected(false) {}

Client::~Client() {
    Disconnect();
}

void Client::Connect() {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(serverIP.c_str());
    serverAddress.sin_port = htons(serverPort);

    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    receiveThread = std::thread(&Client::ReceiveMessages, this);
    connected = true;
}

void Client::Disconnect() {
    connected = false;
    close(clientSocket);
    receiveThread.join();
}

void Client::Send(const std::string& message) {
    send(clientSocket, message.c_str(), message.size(), 0);
}

void Client::ReceiveMessages() {
    char buffer[4096];
    while (connected) {
        memset(buffer, 0, sizeof(buffer));
        recv(clientSocket, buffer, sizeof(buffer), 0);

        // Process received messages, e.g., display them
        std::cout << "Received: " << buffer << std::endl;
    }
}
