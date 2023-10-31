#include "Card.hpp"
#include <iostream>

Card::Card() {}
Card::Card(float width, float height, string name) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::Blue);
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::White); 
    cardName = name;
}

void Card::move(float offsetX, float offsetY) {
    shape.move(offsetX, offsetY);
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