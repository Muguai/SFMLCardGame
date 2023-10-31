#pragma once
#include <SFML/Graphics.hpp>
using namespace std;

class Card {
public:
    Card();
    Card(float width, float height, string name); // Constructor
    void move(float offsetX, float offsetY);
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f vector2);
    sf::Vector2f getPosition() const;
    void toString() const;


private:
    sf::RectangleShape shape;
    string cardName;
};
