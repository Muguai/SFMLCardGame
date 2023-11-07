#pragma once
#include <SFML/Network.hpp>
#include <string>
using namespace std;

class Client {
public:
    Client();
    void connectClient(const sf::IpAddress& serverIP, int port);
    void run();
    void messageToServer(string message);
    void setPlayerNumber(int number);
    int getPlayerNumber();


private:
    sf::TcpSocket socket;
    int playerNumber;
};
