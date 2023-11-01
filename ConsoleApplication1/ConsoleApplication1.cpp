// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <Header/Card.hpp>
#include <Header/Hand.hpp>
#include <Header/Shuffle.hpp>
#include <Header/Deck.hpp>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    sf::RectangleShape shape(sf::Vector2f(120.f,50.f));
    shape.setFillColor(sf::Color::Green);

    sf::Clock clock;
    sf::Clock testSpawnTimer;

    float deltaTime;

    Hand playerHand;
    Deck playerDeck;
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

    // Adding three cards to the deck:
    cout << "Shuffle test:" << endl;
    playerDeck.setPosition(sf::Vector2f(100.0, 800.0));
    playerDeck.addCard(card1);
    playerDeck.addCard(card2);
    playerDeck.addCard(card3);
    playerDeck.shuffleDeck();

    while (window.isOpen())
    {   
        if (testSpawnTimer.getElapsedTime().asSeconds() > 4.f) {
            if (playerDeck.getSize() > 0) {
                playerHand.addCard(playerDeck.dealCard());
            }
            testSpawnTimer.restart();
        }

        sf::Time elapsed = clock.restart();
        deltaTime = elapsed.asSeconds();

        

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        playerDeck.drawDeck(window);
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
