#pragma once
#include <vector>
#include "Card.hpp"

class Hand {
public:
    void addCard(const Card& card);
    void setCardPositions(const std::vector<sf::Vector2f>& positions);
    std::vector<sf::Vector2f> getCardPositions() const;
    void move(float offsetX, float offsetY);
    void draw(sf::RenderWindow& window);
    void arrangeCardsInArc(float radiusX, float radiusY, float centerX, float centerY);
    void printCardDetails() const;


private:
    std::vector<Card> cards;
};
