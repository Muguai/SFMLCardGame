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
    object->initialize();
}

void GameObjectManager::removeGameObject(GameObject* object) {
    auto it = std::find(gameObjects.begin(), gameObjects.end(), object);
    if (it != gameObjects.end()) {
        gameObjects.erase(it);
        delete object;
    }
}

void GameObjectManager::updateAll(float deltaTime, sf::RenderWindow& window) {

    for (const auto& object : gameObjects) {
        object->update(deltaTime, window);
    }
}

void GameObjectManager::updateAllOnTurn(sf::RenderWindow& window) {
    for (const auto& object : gameObjects) {
        object->updateOnTurn();
    }
}

GameObjectManager::~GameObjectManager() {
    for (auto object : gameObjects) {
        delete object;
    }
    gameObjects.clear();
}
