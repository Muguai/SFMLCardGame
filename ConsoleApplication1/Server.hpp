#include <SFML/Network.hpp>
#include <vector>
#include <memory>
#include <thread>
#include <atomic>
#include <string>
#include <mutex>

using namespace std;


class Server {
public:
    Server();
    void startListening(int port);
    void run();
    void stop();
    void messageToClients(string message);
    void messageToClient(string message, size_t clientIndex);


private:
    void handleConnections();
    void receiveMessages();

private:
    sf::TcpListener listener;
    std::vector<std::unique_ptr<sf::TcpSocket>> clients;
    std::mutex clientsMutex;
    std::thread connectionsThread;
    std::thread receiveThread;
    std::atomic<bool> running; 
};
