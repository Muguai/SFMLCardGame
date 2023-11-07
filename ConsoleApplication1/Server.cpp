#include "Server.hpp"
#include <iostream>
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

void Server::messageToClient(char message[]){
    if (clients.size() > 0) {
        if (clients[0]->send(message, sizeof(message)) != sf::Socket::Done) {
            cout << "Failed to send message to client" << endl;
        }
    }
}

void Server::handleConnections() {
    auto client = std::make_unique<sf::TcpSocket>();
    cout << "Server test:" << endl;
    if (listener.accept(*client) == sf::Socket::Done) {
        sf::IpAddress ipAddress = client->getRemoteAddress();
        unsigned short port = client->getRemotePort();
        cout << "Client connected from IP: " << ipAddress << " Port: " << port << endl;
        clients.push_back(std::move(client));
    }
    
}

void Server::receiveMessages() {
    while (true) {
        for (auto& client : clients) {
            char buffer[1024];
            std::size_t received;
            if (client->receive(buffer, sizeof(buffer), received) == sf::Socket::Done) {
                // Process received data from the client (buffer contains the received message)
                cout << "Received message from client: " << buffer << endl;
            }
        }
    }
}

void Server::run() {
    handleConnections();
    receiveMessages();

}

void Server::stop() {
    running = false; // Set the running flag to false to stop the handleConnections and receiveMessages loops
    if (connectionsThread.joinable()) {
        connectionsThread.join(); // Join the handleConnections thread
    }
    if (receiveThread.joinable()) {
        receiveThread.join(); // Join the receiveMessages thread
    }
}