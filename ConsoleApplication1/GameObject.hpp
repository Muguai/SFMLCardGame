#pragma once
#include <SFML/Graphics.hpp>

class GameObjectManager; 
class GameObject {
public:
    virtual void update(float deltaTime, sf::RenderWindow& window) = 0;
    virtual ~GameObject() {} 
    virtual void initialize() {}

};

