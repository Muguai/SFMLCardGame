#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
using namespace std;

class Card {
public:
    int attack;
    int health;
    virtual void useAbility();
    Card();
    Card(int a, int h, sf::Vector2f widthHeight, string name, std::function<void()> myLambda);

    void move(sf::Vector2f moveDir);
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f vector2);
    sf::Vector2f getPosition() const;
    void toString() const;
    bool isHovered(const sf::RenderWindow& window);
    sf::RectangleShape getShape();
    float getWidth() const;
    float getHeight() const;
    void flip();
    void setZ(float z) { this->z = z; }
    float getZ() const { return z; }
    void ExecuteLambda();


private:
    sf::RectangleShape shape;
    sf::RectangleShape backFace;
    sf::Font font;
    string cardName;
    sf::Texture cardTexture;
    float z;
    bool frontFacing;
    std::function<void()> lambda;
};
