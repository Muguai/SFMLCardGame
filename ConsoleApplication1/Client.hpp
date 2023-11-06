#pragma once
#include <SFML/Network.hpp>

class Client {
public:
    Client(const sf::IpAddress& serverIP);
    void run();

private:
    sf::TcpSocket socket;
};
