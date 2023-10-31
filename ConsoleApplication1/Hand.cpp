#include "Header/Hand.hpp"

void Hand::addCard(const Card& card) {
    cards.push_back(card);
}

void Hand::setCardPositions(const std::vector<sf::Vector2f>& positions) {
    if (positions.size() == cards.size()) {
        for (size_t i = 0; i < positions.size(); ++i) {
            cards[i].setPosition(positions[i]);
        }
    }
}

std::vector<sf::Vector2f> Hand::getCardPositions() const {
    std::vector<sf::Vector2f> positions;
    for (const auto& card : cards) {
        positions.push_back(card.getPosition());
    }
    return positions;
}

void Hand::arrangeCardsInArc(float radiusX, float radiusY, float centerX, float centerY) {
    int numCards = static_cast<int>(cards.size());
    float angleIncrement = 180.f / (numCards * 2);
    float currentAngle = 90.f - (angleIncrement * (numCards - 1) / 2);

    for (auto& card : cards) {
        float radians = currentAngle * (3.14159265359f / 180.f); 
        float xPos = centerX + radiusX * cos(radians);
        float yPos = centerY - radiusY * sin(radians); 
        card.setPosition(sf::Vector2f(xPos, yPos));
        currentAngle += angleIncrement;
    }

}

void Hand::move(float offsetX, float offsetY) {
    for (auto& card : cards) {
        card.move(offsetX, offsetY);
    }
}

void Hand::draw(sf::RenderWindow& window) {
    for (auto& card : cards) {
        card.draw(window);
    }
}

void Hand::printCardDetails() const {
    for (const auto& card : cards) {
        card.toString();
    }
}
