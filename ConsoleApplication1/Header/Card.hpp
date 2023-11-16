#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <GameObject.hpp>
#include <SFML/System.hpp>

using namespace std;

class Card : public GameObject {
public:
    int attack;
    int health;
    int cost;   
    string cardName;
    
    virtual void useAbility();
    Card(int a, int h, int c, sf::Vector2f widthHeight, string name, std::function<void()> myLambda);
    Card();
    void update(float deltaTime, sf::RenderWindow& window) override;
    void initialize() override;
    void move(sf::Vector2f moveDir);
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f vector2);
    sf::Vector2f getPosition() const;
    void toString() const;
    bool isHovered(const sf::RenderWindow& window);
    sf::RectangleShape getShape();
    float getWidth() const;
    float getHeight() const;
    int getCost();
    void flip();
    void setZ(float z) { this->z = z; }
    float getZ() const { return z; }
    void ExecuteLambda();
    bool isNull();
  
private:
    sf::RectangleShape shape;
    sf::RectangleShape backFace;
    sf::Font font;

    sf::Texture cardTexture;
    float z;
    bool frontFacing;
    bool null;
    std::function<void()> lambda;
};
