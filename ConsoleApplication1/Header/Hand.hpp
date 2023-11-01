#pragma once
#include <vector>
#include "Card.hpp"


class Hand {
public:
    void addCard(const Card& card);
    void setCardPositions(const std::vector<sf::Vector2f>& positions);
    std::vector<sf::Vector2f> getCardPositions() const;
    void draw(sf::RenderWindow& window);
    void arrangeCardsInArc(float radiusX, float radiusY, float centerX, float centerY, sf::RenderWindow& window, float deltaTime);
    void printCardDetails() const;
    void handleCardHover(sf::RenderWindow& window);
    float easeInOut(float t);

private:
    std::vector<Card> cards;
    std::vector<Card> cardsRenderOrder;
    Card* draggingCard;
};
