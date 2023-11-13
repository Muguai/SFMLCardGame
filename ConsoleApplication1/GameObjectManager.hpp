#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "GameObject.hpp"
#include <SFML/Graphics.hpp>

class GameObjectManager {
public:
    GameObjectManager();

    static GameObjectManager& getInstance();

    // Change the parameter type to std::unique_ptr<GameObject>
    void addGameObject(GameObject* object);

    void updateAll(float deltaTime, sf::RenderWindow& window);

    ~GameObjectManager();

private:
    std::vector<GameObject*> gameObjects;  // Adjust the vector type
};
