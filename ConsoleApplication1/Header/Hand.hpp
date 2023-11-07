#pragma once
#include <vector>
#include "Card.hpp"


class Hand {
public:
    Hand(bool _hoverable, bool _spawnFlipped);
    void addCard(Card& card);
    void setCardPositions(const std::vector<sf::Vector2f>& positions);
    std::vector<sf::Vector2f> getCardPositions() const;
    void draw(sf::RenderWindow& window);
    void arrangeCardsInArc(float radiusX, float radiusY, float centerX, float centerY, sf::RenderWindow& window, float deltaTime);
    void printCardDetails() const;
    void handleCardHover(sf::RenderWindow& window);
    float easeInOut(float t);
    void flipAllCards();

private:
    std::vector<Card> cards;
    std::vector<Card> cardsRenderOrder;
    Card* draggingCard;
    bool hoverable;
    bool spawnFlipped;
};
