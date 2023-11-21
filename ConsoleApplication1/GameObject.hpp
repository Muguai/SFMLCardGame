#pragma once
#include <SFML/Graphics.hpp>

class GameObjectManager; 
class GameObject {
public:

    /*	update()
    	Calls once every frame
    */
    virtual void update(float deltaTime, sf::RenderWindow& window) = 0;
    virtual ~GameObject() {} 
    /*	initialize()
    	Calls once when added to GameObjectManager
    */
    virtual void initialize() {}

    /*  updateOnTurn()
        Performs task at the start of a new turn.
    */
    virtual void updateOnTurn(){}
};


/*
HPP

void update(float deltaTime, sf::RenderWindow& window) override;
void initialize() override;

CPP

void Object::update(float deltaTime, sf::RenderWindow& window) {
}

void Object::initialize() {
}

*/