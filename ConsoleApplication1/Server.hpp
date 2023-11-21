#include <SFML/Network.hpp>
#include <vector>
#include <memory>
#include <thread>
#include <atomic>
#include <string>
#include <mutex>
#include "Board.hpp"
#include "Deck.hpp"
using namespace std;


class Server {
public:
    Server();
    void startListening(int port);
    void run();
    void stop();
    void messageToClients(string message);
    void messageToClient(string message, size_t clientIndex);
    void setDecks(Deck player1Deck, Deck player2Deck);
    void setHands(Hand _player1Hand, Hand _player2Hand);
    void setBoard(Board _board);


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
    Board board;
    Deck player1Deck;
    Deck player2Deck;
    Hand player1Hand;
    Hand player2Hand;
};
