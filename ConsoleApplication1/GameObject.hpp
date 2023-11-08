#pragma once
class GameObjectManager; 
class GameObject {
public:
    virtual void update(float deltaTime) = 0;
    virtual ~GameObject() {} 
    virtual void initialize() {}

};

