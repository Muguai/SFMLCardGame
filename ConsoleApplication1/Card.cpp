#include "Card.hpp"
#include <iostream>
#include <functional>
#include <string>
#include "GameObjectManager.hpp"

extern float deltaTime;
Card::Card() {
    null = true;
}
Card::Card(int a, int h, int c, sf::Vector2f widthHeight, string name, std::function<void()> myLambda) : lambda(myLambda), GameObject() {
    shape.setSize(widthHeight);
    shape.setFillColor(sf::Color::Blue);
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::White);

    backFace.setSize(widthHeight);
    backFace.setFillColor(sf::Color::Green);
    backFace.setOutlineColor(sf::Color::White);
    backFace.setOutlineThickness(2.f);

    frontFacing = true;
    null = false;
    cardName = name;
    shape.setOrigin(widthHeight.x / 2.f, widthHeight.y / 2.f);
    backFace.setOrigin(widthHeight.x / 2.f, widthHeight.y / 2.f);
    attack = a;
    health = h;
    cost = c;

    if (!font.loadFromFile("Fonts/COMIC.ttf")) {
        cout << "Error loading font!";
    }
    if (!cardTexture.loadFromFile("Images/" + name + ".png")) {
        cout << "Error loading card image!";
    }
}

bool Card::isNull() {
    return null;
}

void Card::update(float deltaTime, sf::RenderWindow& window) {
    
    
}

void Card::initialize() {
    //GameObjectManager::getInstance().addGameObject(this);
}
void Card::ExecuteLambda() {
    lambda();
}

void Card::useAbility() {}

void Card::move(sf::Vector2f moveDir) {
    shape.move(moveDir);
    backFace.move(moveDir);
}

void Card::flip() {
    frontFacing = !frontFacing;
}


void Card::setPosition(sf::Vector2f vector2) {
    shape.setPosition(vector2);
    backFace.setPosition(vector2);
}

sf::Vector2f Card::getPosition() const {
    if (frontFacing == true) {
        return shape.getPosition();
    }
    else {
        return backFace.getPosition();
    }
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
    
    // 2. Render center image, normalize its scale:
    sf::Sprite cardSprite(cardTexture);
    cardSprite.setScale(308 / cardSprite.getLocalBounds().width, 374 / cardSprite.getLocalBounds().height);
    int imgOffsetX =  -(shape.getSize().x / 2) + 20;
    int imgOffsetY = -(shape.getSize().y / 2) + 50;
    cardSprite.scale(sf::Vector2f(0.3, 0.3));
    cardSprite.setPosition(shape.getPosition().x + imgOffsetX, shape.getPosition().y + imgOffsetY);

    // 3. Render Attack and Health
    sf::Text statsText("ATK: " + to_string(attack) + "\nHP: " + to_string(health), font, 12);
    int statsOffsetX = -(shape.getSize().x / 2) + 20;
    int statsOffsetY = +(shape.getSize().y / 2) - 35;
    statsText.setPosition(shape.getPosition().x + statsOffsetX, shape.getPosition().y + statsOffsetY);

    // 4. Render Mana Cost:
    string paddedStr = to_string(cost);
    if (paddedStr.length() == 1) {
        paddedStr = " " + paddedStr;
    }

    sf::Text manaText(paddedStr, font, 12);
    int manaOffsetX = +(shape.getSize().x / 2) - 20;
    int manaOffsetY = -(shape.getSize().y / 2) + 5;
    manaText.setPosition(shape.getPosition().x + manaOffsetX, shape.getPosition().y + manaOffsetY);

    // 5. Render order:
    if (frontFacing == true) {
        window.draw(backFace);
        window.draw(shape);
        window.draw(nameText);
        window.draw(cardSprite);
        window.draw(statsText);
        window.draw(manaText);
    }
    else {
        window.draw(shape);
        window.draw(nameText);
        window.draw(cardSprite);
        window.draw(backFace);
    }
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
