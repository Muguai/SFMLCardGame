#pragma once
#include <vector>
#include "Card.hpp"
#include <GameObject.hpp>
#include <SFML/Graphics.hpp>


class Hand : public GameObject{
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
    std::vector<Card> getCards();
    void update(float deltaTime, sf::RenderWindow& window) override;
    void initialize() override;


private:
    std::vector<Card> cards;
    std::vector<Card> cardsRenderOrder;
    Card* draggingCard;
    bool hoverable;
    bool spawnFlipped;
};
