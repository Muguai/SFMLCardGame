#include "Card.hpp"
#include <iostream>

Card::Card() {};

Card::Card(sf::Vector2f widthHeight, string name) {
    shape.setSize(widthHeight);
    shape.setFillColor(sf::Color::Blue);
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::White); 
    cardName = name;
    shape.setOrigin(widthHeight.x / 2.f, widthHeight.y / 2.f);
}

void Card::move(sf::Vector2f moveDir) {
    shape.move(moveDir);
}


void Card::setPosition(sf::Vector2f vector2) {
    shape.setPosition(vector2);
}

sf::Vector2f Card::getPosition() const {
    return shape.getPosition();
}


void Card::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Card::toString() const{
    std::cout << "Card Name: " + cardName + " X: " + std::to_string(getPosition().x) + " Y: " + std::to_string(getPosition().y) << std::endl;
}

bool Card::isHovered(const sf::RenderWindow& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::FloatRect cardBounds = shape.getGlobalBounds();
    return cardBounds.contains(static_cast<sf::Vector2f>(mousePosition));
}


float Card::getWidth() const {
    return shape.getSize().x;
}

float Card::getHeight() const {
    return shape.getSize().y;
}

sf::RectangleShape Card::getShape() {
    return shape;
}
