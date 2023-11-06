#pragma once
#include <SFML/Network.hpp>

class Client {
public:
    Client(const sf::IpAddress& serverIP, int port);
    void run();

private:
    sf::TcpSocket socket;
};
