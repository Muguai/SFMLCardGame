#pragma once

#include <SFML/Network.hpp>
#include <vector>
#include <memory>

class Server {
public:
    Server();

    void handleConnections();
    void run();

private:
    sf::TcpListener listener;
    std::vector<std::unique_ptr<sf::TcpSocket>> clients;
};
