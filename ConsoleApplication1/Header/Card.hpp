#pragma once
#include <SFML/Graphics.hpp>
using namespace std;

class Card {
public:
    Card(sf::Vector2f widthHeight, string name); // Constructor
    void move(float offsetX, float offsetY);
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f vector2);
    sf::Vector2f getPosition() const;
    void toString() const;
    bool isHovered(const sf::RenderWindow& window);
    sf::RectangleShape getShape();
    float getWidth() const;
    float getHeight() const;
    void setZ(float z) { this->z = z; }
    float getZ() const { return z; }


private:
    sf::RectangleShape shape;
    string cardName;
    float z;
};
