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

    if (!font.loadFromFile("Fonts/COMIC.ttf")) {
        cout << "Error loading font!";
    }
    if (!cardTexture.loadFromFile("Images/card2.png")) {
        cout << "Error loading card image!";
    }
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

/*  draw()
    A function that renders different components onto a card-body.
    The body as a whole is offsetted depending on the position of the card class.
*/

void Card::draw(sf::RenderWindow& window) {
    // 1. Render name of the card:
    sf::Text nameText(cardName, font, 18);
    int nameOffsetX = -(shape.getSize().x /2) + 20;
    int nameOffsetY = -(shape.getSize().y / 2) + 20;
    nameText.setPosition(shape.getPosition().x + nameOffsetX, shape.getPosition().y + nameOffsetY);
    
    // 2. Render center image:
    sf::Sprite cardSprite(cardTexture);
    int imgOffsetX =  -(shape.getSize().x / 2) + 20;
    int imgOffsetY = -(shape.getSize().y / 2) + 60;
    cardSprite.scale(sf::Vector2f(0.5, 0.5));
    cardSprite.setPosition(shape.getPosition().x + imgOffsetX, shape.getPosition().y + imgOffsetY);

    // 3. Render order:
    window.draw(shape);
    window.draw(nameText);
    window.draw(cardSprite);
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
