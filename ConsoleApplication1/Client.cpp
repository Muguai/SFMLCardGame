#include "Client.hpp"
#include <iostream>
using namespace std;

Client::Client() {

}

void Client::connectClient(const sf::IpAddress& serverIP, int port) {

    cout << "Trying to connect to server with ip adress " + serverIP.toString() + " and port " + std::to_string(port) << endl;
    if (socket.connect(serverIP, port) != sf::Socket::Done) {
        cout << "Couldnt connect to server" << endl;
    }
    else {
        cout << "Connected to server " + socket.getRemoteAddress().toString() << endl;
    }
}

void Client::run() {
    while (true) {
        // Handle user input and send messages to the server

        // Receive messages from the server and update game state
        char buffer[1024];
        std::size_t received;
        if (socket.receive(buffer, sizeof(buffer), received) == sf::Socket::Done) {
            cout << "Received message from server: " << buffer << endl;
        }
    }
}

void Client::messageToServer(string message) {
    std::vector<char> charMessage(message.begin(), message.end());
    charMessage.push_back('\0');

    if (socket.send(charMessage.data(), charMessage.size()) != sf::Socket::Done) {
        // Handle send error...
        std::cout << "Failed to send message to server" << std::endl;
    }
}

void Client::setPlayerNumber(int number) {
    playerNumber = number;
}

int Client::getPlayerNumber() {
    return playerNumber;
}

