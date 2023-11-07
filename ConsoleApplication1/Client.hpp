#pragma once
#include <SFML/Network.hpp>

class Client {
public:
    Client();
    void connectClient(const sf::IpAddress& serverIP, int port);
    void run();
    void messageToServer(char message[]);


private:
    sf::TcpSocket socket;
};
