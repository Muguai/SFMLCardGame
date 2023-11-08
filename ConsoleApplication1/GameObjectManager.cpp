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

void GameObjectManager::addGameObject(GameObject* object) {
    gameObjects.push_back(object);
}


void GameObjectManager::updateAll(float deltaTime) {
    cout << gameObjects.size() << endl;

    for (GameObject* object : gameObjects) {
        if (object != nullptr) {
            object->update(deltaTime);
        }
    }
}

GameObjectManager::~GameObjectManager() {
    for (GameObject* object : gameObjects) {
        delete object;
    }
}