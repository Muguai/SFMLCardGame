#pragma once
#include "GameObjectManager.hpp"
#include <iostream>
#include <vector>
#include <Card.hpp>
using namespace std;

GameObjectManager::GameObjectManager() {}

GameObjectManager& GameObjectManager::getInstance() {
    static GameObjectManager instance;
    return instance;
}

// Change the parameter type to std::unique_ptr<GameObject>
void GameObjectManager::addGameObject(GameObject* object) {
    gameObjects.push_back(std::move(object));
}

void GameObjectManager::updateAll(float deltaTime, sf::RenderWindow& window) {

    for (const auto& object : gameObjects) {
        object->update(deltaTime, window);
    }
}

GameObjectManager::~GameObjectManager() {
    // No need to manually delete the objects, smart pointers will handle it
}
