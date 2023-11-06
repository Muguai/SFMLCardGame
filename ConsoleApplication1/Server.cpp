#include "Server.hpp"
#include <iostream>
using namespace std;
Server::Server() {
   
}

void Server::startListening(int port) {
    if (listener.listen(53000) != sf::Socket::Done) {
        cout << "Cant bind server to port" << endl;
        // Handle error...
    }
}

void Server::handleConnections() {
    while (true) {
        auto client = std::make_unique<sf::TcpSocket>();
        cout << "Server test:" << endl;
        if (listener.accept(*client) == sf::Socket::Done) {
            cout << "Client connected" << endl;
            clients.push_back(std::move(client));
        }

        // Handle client messages and game logic here
    }
}

void Server::run() {
    handleConnections();
}