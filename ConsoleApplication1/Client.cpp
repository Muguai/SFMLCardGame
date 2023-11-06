#include "Client.hpp"

Client::Client(const sf::IpAddress& serverIP) {
    if (socket.connect(serverIP, 53000) != sf::Socket::Done) {
        // Handle connection error...
    }
}

void Client::run() {
    while (true) {
        // Handle user input and send messages to the server

        // Receive messages from the server and update game state
        char buffer[1024];
        std::size_t received;
        if (socket.receive(buffer, sizeof(buffer), received) == sf::Socket::Done) {
            // Process received data from the server
        }
    }
}