#include "Server.hpp"
#include <iostream>
#include <string>
using namespace std;
Server::Server() {
   
}

void Server::startListening(int port) {

    if (listener.listen(port, sf::IpAddress::Any) != sf::Socket::Done) {
        cout << "Cant bind server to port" << endl;
        // Handle error...
    }
    else {
        sf::IpAddress ipAddress = sf::IpAddress::getLocalAddress(); // Get the local IP address of the server
        cout << "Server started listening on IP: " << ipAddress << " Port: " << port << endl;
    }
}

void Server::messageToClients(string message) {
    std::vector<char> charMessage(message.begin(), message.end());
    charMessage.push_back('\0');

    for (auto& client : clients) {
        if (client->send(charMessage.data(), charMessage.size()) != sf::Socket::Done) {
            cout << "Failed to send message to client" << endl;
        }
    }
}

void Server::messageToClient(string message, size_t clientIndex) {
    if (clientIndex < clients.size()) {
        std::vector<char> charMessage(message.begin(), message.end());
        charMessage.push_back('\0');

        if (clients[clientIndex]->send(charMessage.data(), charMessage.size()) != sf::Socket::Done) {
            cout << "Failed to send message to client " << clientIndex << endl;
        }
    }
    else {
        cout << "Invalid client index" << endl;
    }
}

void Server::handleConnections() {
    while (true) {
        auto client = std::make_unique<sf::TcpSocket>();
        if (listener.accept(*client) == sf::Socket::Done) {
            sf::IpAddress ipAddress = client->getRemoteAddress();
            unsigned short port = client->getRemotePort();

            std::lock_guard<std::mutex> lock(clientsMutex); // Lock the mutex to access the clients vector
            cout << "Client connected from IP: " << ipAddress << " Port: " << port << endl;
            clients.push_back(std::move(client));
            if (clients.size() > 0) {
                running = true;
            }
        }
    }
}


void Server::receiveMessages() {
    while (running) {
        for (auto& client : clients) {
            char buffer[1024];
            std::size_t received;
            if (client->receive(buffer, sizeof(buffer), received) == sf::Socket::Done) {
                cout << "Received message from client: " << buffer << endl;
                if(std::strncmp(buffer, "Draw", 0) == 0) {
                    std::cout << "draw" << std::endl;
                }
            }
        }
    }
}

void Server::run() {

    std::thread connectionsThread(&Server::handleConnections, this);
    while (true) {
        receiveMessages();
    }

}

void Server::stop() {
    running = false;
    if (connectionsThread.joinable()) {
        connectionsThread.join(); 
    }
}