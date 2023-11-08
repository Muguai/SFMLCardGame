#pragma once
#include "GameObject.hpp"
#include <vector>

class GameObjectManager {
public:
    static GameObjectManager& getInstance();

    void addGameObject(GameObject* object);
    void updateAll(float deltaTime);
    ~GameObjectManager();

private:
    std::vector<GameObject*> gameObjects;

    GameObjectManager();
    GameObjectManager(const GameObjectManager&) = delete;
    GameObjectManager& operator=(const GameObjectManager&) = delete;
};
