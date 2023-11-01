#include "Header/Hand.hpp"
#include <iostream>
#include "VectorHelper.hpp"

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

void Hand::arrangeCardsInArc(float radiusX, float radiusY, float centerX, float centerY, sf::RenderWindow& window, float deltaTIme) {
    int numCards = static_cast<int>(cards.size());
    float angleIncrement = 180.f / (numCards * 2);
    float currentAngle = 90.f - (angleIncrement * (numCards - 1) / 2);
    bool onlyOneHovered = false;
    bool onlyOneDragging = false;
    float z = 0.0f;
    for (auto& card : cards) {
        float radians = currentAngle * (3.14159265359f / 180.f); 
        float xPos = centerX + radiusX * cos(radians);
        float yPos = centerY - radiusY * sin(radians); 
        sf::Vector2f targetPosition = sf::Vector2f(xPos, yPos);
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        bool isHovered = mousePos.x >= xPos - card.getWidth() / 2 && mousePos.x <= xPos + card.getWidth() / 2 &&
            mousePos.y >= yPos - card.getHeight() / 2 && mousePos.y <= yPos + card.getHeight() / 2;
        z += 1;
        card.setZ(z);

        if (VectorHelper::distanceTo(card.getPosition(), targetPosition) > 10.f) {
            sf::Vector2f direction = targetPosition - card.getPosition();     
            direction = VectorHelper::normalize(direction);

            float speed = 1000.f;
            cout << "Move " + std::to_string(VectorHelper::distanceTo(card.getPosition(), targetPosition)) + " With Vector " + std::to_string((direction * speed * deltaTIme).x) + " " + std::to_string((direction * speed * deltaTIme).y);
            card.move(direction * speed * deltaTIme);
        }

        /*
        if (isHovered && !onlyOneHovered && !onlyOneDragging) {
            onlyOneHovered = true;
            card.setZ(numCards);
            targetPosition.y -= 100; 
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && card.isHovered(window) && !onlyOneDragging) {
            cout << "Hovered";
            onlyOneDragging = true;
            card.setZ(numCards);
            targetPosition = static_cast<sf::Vector2f>(mousePos);
        }
        */

        currentAngle += angleIncrement;
    }

    std::sort(cards.begin(), cards.end(), [](const Card& a, const Card& b) {
        return a.getZ() < b.getZ();
    });

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


void Hand::handleCardHover(sf::RenderWindow& window) {
    for (auto& card : cards) {
        if (card.isHovered(window)) {
            card.getShape().setFillColor(sf::Color::Yellow);
        }
        else {
            card.getShape().setFillColor(sf::Color::Blue);
        }
    }

}

