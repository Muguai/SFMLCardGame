#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "GameObject.hpp"
using namespace std;

class Monster : public GameObject {
public:
	Monster();
	Monster(int atk, int hp, string n, int s);
	bool isNull();
	int getAttack();
	int getHealth();
	float getRadius();
	void drawMonster(sf::Vector2f pos, float radius, sf::RenderWindow& window);
	void update(float deltaTime, sf::RenderWindow& window) override;
	void initialize() override;

private:
	int attack;
	int health;
	bool null;
	string name;
	int slot;
	sf::Texture monsterTexture;
	sf::Font font;
};