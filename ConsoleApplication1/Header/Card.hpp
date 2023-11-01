#pragma once
#include <SFML/Graphics.hpp>
using namespace std;

class Card {
public:
    Card();
    Card(sf::Vector2f widthHeight, string name); 
    void move(sf::Vector2f moveDir);
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
    sf::Font font;
    string cardName;
    sf::Texture cardTexture;
    float z;
};
