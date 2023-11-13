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

    void addGameObject(GameObject* object);
    void removeGameObject(GameObject* object);

    void updateAll(float deltaTime, sf::RenderWindow& window);

    ~GameObjectManager();

private:
    std::vector<GameObject*> gameObjects; 
};
