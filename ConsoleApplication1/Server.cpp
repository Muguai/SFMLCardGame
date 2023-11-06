#include "Server.hpp"
#include <iostream>
using namespace std;
Server::Server() {
   
}

void Server::startListening(int port) {

    if (listener.listen(port) != sf::Socket::Done) {
        cout << "Cant bind server to port" << endl;
        // Handle error...
    }
    else {
        sf::IpAddress ipAddress = sf::IpAddress::getLocalAddress(); // Get the local IP address of the server
        cout << "Server started listening on IP: " << ipAddress << " Port: " << port << endl;
    }
}

void Server::handleConnections() {
    while (true) {
        auto client = std::make_unique<sf::TcpSocket>();
        cout << "Server test:" << endl;
        if (listener.accept(*client) == sf::Socket::Done) {
            sf::IpAddress ipAddress = client->getRemoteAddress();
            unsigned short port = client->getRemotePort();

            cout << "Client connected from IP: " << ipAddress << " Port: " << port << endl;
            clients.push_back(std::move(client));
        }

        // Handle client messages and game logic here
    }
}

void Server::run() {
    handleConnections();
}