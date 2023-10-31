// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Header/Card.hpp>
#include <Header/Hand.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    sf::RectangleShape shape(sf::Vector2f(120.f,50.f));
    shape.setFillColor(sf::Color::Green);

    Hand playerHand;


    Card card1(120.f, 200.f, "1");
    Card card2(120.f, 200.f, "2");
    Card card3(120.f, 200.f, "3");
    Card card4(120.f, 200.f, "4");
    Card card5(120.f, 200.f, "5");
    Card card6(120.f, 200.f, "6");
    playerHand.addCard(card1);
    playerHand.addCard(card2);
    playerHand.addCard(card3);
    playerHand.addCard(card4);
    playerHand.addCard(card5);
    playerHand.addCard(card6);





    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }



        window.clear();

        if (event.type == sf::Event::Resized)
        {
            sf::FloatRect view(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(view));
        }
        //playerHand.printCardDetails();
        float centerX = window.getSize().x / 2.f; // Center X-coordinate
        float centerY = window.getSize().y - 300.f; // Bottom Y-coordinate

        playerHand.arrangeCardsInArc(400.f, 150.f, centerX, centerY); // Set radiusX, radiusY, center coordinates, and cardGap        
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
