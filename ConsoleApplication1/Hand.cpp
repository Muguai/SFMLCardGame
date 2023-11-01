#include "Header/Hand.hpp"
#include <iostream>
#include "VectorHelper.hpp"

void Hand::addCard(const Card& card) {
    cards.push_back(card);
    cardsRenderOrder = cards;
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
    float angleIncrement = 120.f / numCards;
    float currentAngle = 90.f - (angleIncrement * (numCards - 1) / 2);
    bool onlyOneHovered = false;
    float z = 0.0f;

    for (auto& card : cards) {
        float radians = currentAngle * (3.14159265359f / 180.f); 
        float xPos = centerX + radiusX * cos(radians);
        float yPos = centerY - radiusY * sin(radians); 
        sf::Vector2f targetPosition = sf::Vector2f(xPos, yPos);
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        z += 1;
        card.setZ(z);

        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && draggingCard) {
            draggingCard = nullptr;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && card.isHovered(window) && !draggingCard) {
            draggingCard = &card;
        }

        if (draggingCard == &card) {
            card.setZ(numCards + 1);
            targetPosition = static_cast<sf::Vector2f>(mousePos);
            card.setPosition(targetPosition);
            currentAngle += angleIncrement;
            continue;
        }


        bool isHovered = mousePos.x >= xPos - card.getWidth() / 3 && mousePos.x <= xPos + card.getWidth() / 3 &&
            mousePos.y >= yPos - card.getHeight() / 2 && mousePos.y <= yPos + card.getHeight() / 2;

        if (isHovered && !onlyOneHovered && !draggingCard) {
            targetPosition.y -= 100;
            card.setZ(numCards + 1);
            onlyOneHovered = true;
        }

        float distance = VectorHelper::distanceTo(card.getPosition(), targetPosition);
        if (distance > 5.f) {
            sf::Vector2f direction = targetPosition - card.getPosition();     
            direction = VectorHelper::normalize(direction);
            float minSpeed = 500.f; 
            float maxSpeed = 2000.f;  

            float speedFactor = 5.f;
            float speed = std::max(minSpeed, std::min(distance * speedFactor, maxSpeed));
            if (speed > minSpeed) {
            cout << "Speed " + std::to_string(speed) << endl;
            }
            card.move(direction * speed * deltaTIme);
        }

        currentAngle += angleIncrement;
    }

    cardsRenderOrder = cards;
    std::sort(cardsRenderOrder.begin(), cardsRenderOrder.end(), [](const Card& a, const Card& b) {
        return a.getZ() < b.getZ();
    });

}


void Hand::draw(sf::RenderWindow& window) {
    for (auto& card : cardsRenderOrder) {
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

