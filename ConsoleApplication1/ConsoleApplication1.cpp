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
        std::cout << "Choose a port to render to" << endl;
        std::cin >> port;

        if (port == "s") {
            port = "5000";
        }


        int portInt = std::stoi(port);
        server.startListening(portInt);

        serverThread = std::thread([&]() {
            server.run();
            });

    }
    else if (mode == NetworkMode::Client) {

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

    //Player Hand dummy cards
    Card card1(cardSize, "1");
    Card card2(cardSize, "2");
    Card card3(cardSize, "3");
    Card card4(cardSize, "4");
    Card card5(cardSize, "5");
    Card card6(cardSize, "6");
    playerHand.addCard(card1);
    playerHand.addCard(card2);
    playerHand.addCard(card3);
    playerHand.addCard(card4);
    playerHand.addCard(card5);
    playerHand.addCard(card6);

    Deck playerDeck(10, 100.0f, 700.0f);
    playerDeck.shuffleDeck();

    

    while (window.isOpen())
    {   
        if (testSpawnTimer.getElapsedTime().asSeconds() > 4.f) {
            if (playerDeck.getSize() > 0) {
                playerDeck.dealCard(playerHand);
            }
            testSpawnTimer.restart();
        }

        sf::Time elapsed = clock.restart();
        deltaTime = elapsed.asSeconds();

        if (mode == NetworkMode::Server) {
            char message[] = "Hello, Client!";

            server.messageToClient(message);
        }

        if (mode == NetworkMode::Client) {
            char message[] = "Hello, Server!";
            client.messageToServer(message);
        }
        

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
        window.display();
    }
    if (mode == NetworkMode::Server) {
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
