#include <SFML/Network.hpp>
#include <vector>
#include <memory>
#include <thread>
#include <atomic>

class Server {
public:
    Server();
    void startListening(int port);
    void run();
    void stop();
    void messageToClient(char message[]);


private:
    void handleConnections();
    void receiveMessages();

private:
    sf::TcpListener listener;
    std::vector<std::unique_ptr<sf::TcpSocket>> clients;
    std::thread connectionsThread;
    std::thread receiveThread;
    std::atomic<bool> running; 
};
