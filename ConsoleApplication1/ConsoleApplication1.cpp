// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Network.hpp>
#include <Header/Card.hpp>
#include <Header/Hand.hpp>
#include <Header/Shuffle.hpp>
#include <Header/Deck.hpp>
#include <Header/Monster.hpp>
#include <Header/Board.hpp>
#include <thread> 
#include <Server.hpp>
#include <Client.hpp>
#include <string>

using namespace std;
float deltaTime;


enum class NetworkMode {
    Server,
    Client
};


int main()
{   
    // Select a faction to play:
    int faction = 0;
    while (faction == 0) {
        cout << "What faction do you want to play?" << endl;
        cout << "1. Chaos" << endl;
        cout << "2. Life (Currently no such faction)" << endl;
        cin >> faction;
        if (faction < 0 || faction > 2) {
            cout << "Bad faction choice, try again!" << endl;
            faction = 0;
        }
    }

    NetworkMode mode = NetworkMode::Server;
    Server server;
    Client client;

    char who;
    std::cout << "Do you want to be a server (s) or a client (c)?" << endl;
    std::cin >> who;

    std::thread serverThread;
    std::thread serverHandleMessagesThread;
    std::thread clientThread;

    if (std::tolower(who) == 's') {
        mode = NetworkMode::Server;
    }
    else if (std::tolower(who) == 'c') {
        mode = NetworkMode::Client;
    }
    else {
        std::cout << "No such command" << endl;
        return 0;
    }


    if (mode == NetworkMode::Server) {

        string port;
        std::cout << "Choose a port for your server" << endl;
        std::cin >> port;

        if (port == "s") {
            port = "5000";
        }


        int portInt = std::stoi(port);
        server.startListening(portInt);

        serverThread = std::thread([&]() {
            server.run();
            });

        client.connectClient(sf::IpAddress::getLocalAddress(), portInt);

        client.setPlayerNumber(1);

        clientThread = std::thread([&]() {
            client.run();
            });

    }else if (mode == NetworkMode::Client) {

        string ip;
        std::cout << "Whats the servers ip adress?" << endl;
        std::cin >> ip;

        if (ip == "c") {
            ip = "127.0.0.1";
        }

        string port;
        std::cout << "Whats the servers port?" << endl;
        std::cin >> port;


        if (port == "c") {
            port = "5000";
        }

        int portInt = std::stoi(port);

        client.connectClient(ip, portInt);

        client.setPlayerNumber(2);

        clientThread = std::thread([&]() {
            client.run();
            });
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);


    sf::Clock clock;
    sf::Clock testSpawnTimer;

    Hand playerHand;
    sf::Vector2f cardSize = sf::Vector2f(150.f, 200.f);

    // Init the deck as: Deck size = 10, x = 100.0 and y = 700.0, faction = <selected int>:
    Deck playerDeck(10, 100.0f, 700.0f, faction);
    playerDeck.shuffleDeck();

    // Testing playerboard:
    Monster testMonster(10, 10, "Dragon", 4);
    Board playerBoard(sf::Vector2f(450, 500), 40.0f);

    while (window.isOpen())
    {   
        if (testSpawnTimer.getElapsedTime().asSeconds() > 1.f) {
            if (playerDeck.getSize() > 0) {
                playerDeck.dealCard(playerHand);
                
                if (!playerBoard.isFull()) {
                    playerBoard.addPlayerMonster(testMonster);
                }
            }
            testSpawnTimer.restart();
        }

        sf::Time elapsed = clock.restart();
        deltaTime = elapsed.asSeconds();

         //client.messageToServer("Hello, Server!");
         server.messageToClients("Hello Clients");
        

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        playerDeck.renderDeck(window);
        if (event.type == sf::Event::Resized)
        {
            sf::FloatRect view(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(view));
        }
        
        //playerHand.printCardDetails();
        float centerX = window.getSize().x / 2.f; 
        float centerY = window.getSize().y - 100.f; 

        playerHand.arrangeCardsInArc(400.f, 150.f, centerX, centerY, window, deltaTime); 
        playerHand.handleCardHover(window);
        playerHand.draw(window);
        
        //testMonster.drawMonster(sf::Vector2f(0.0, 0.0), 80.0f, window);
        playerBoard.renderPlayerMonsters(window);
        
        window.display();
    }
    if (mode == NetworkMode::Server) {
        server.stop();
        if (serverThread.joinable()) {
            serverThread.join();
        }
       
    }
    else if (mode == NetworkMode::Client) {
        if (clientThread.joinable()) {
            clientThread.join();
        }
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
