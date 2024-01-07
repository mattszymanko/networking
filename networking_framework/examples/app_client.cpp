#include "networking/client.h"
#include <iostream>

int main() {
    Client client("127.0.0.1", 12345);
    client.Connect();

    std::string message;
    while (true) {
        std::getline(std::cin, message);
        client.Send(message);
    }

    return 0;
}
