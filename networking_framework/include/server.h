#pragma once

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

class Server {
public:
    Server(int port);
    ~Server();

    void Start();
    void Stop();
    void Broadcast(const std::string& message);

private:
    void ListenForClients();

    int port;
    int serverSocket;
    std::vector<int> clientSockets;
    std::thread listenThread;
    std::mutex mutex;
    bool running;
};
