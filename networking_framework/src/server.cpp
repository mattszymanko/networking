#include "server.h"
#include <arpa/inet.h>
#include <unistd.h>

Server::Server(int port) : port(port), running(false) {}

Server::~Server() {
    Stop();
}

void Server::Start() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    listenThread = std::thread(&Server::ListenForClients, this);
    running = true;
}

void Server::Stop() {
    running = false;
    close(serverSocket);
    listenThread.join();

    for (int clientSocket : clientSockets) {
        close(clientSocket);
    }
}

void Server::ListenForClients() {
    while (running) {
        sockaddr_in clientAddress{};
        socklen_t clientAddressLen = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLen);

        std::lock_guard<std::mutex> lock(mutex);
        clientSockets.push_back(clientSocket);

        // Handle client in a separate thread or function
        // For simplicity, we just broadcast messages to all clients
    }
}

void Server::Broadcast(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex);
    for (int clientSocket : clientSockets) {
        send(clientSocket, message.c_str(), message.size(), 0);
    }
}
