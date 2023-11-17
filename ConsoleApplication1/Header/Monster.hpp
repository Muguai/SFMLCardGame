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
	void unclick();
	bool getClicked();
	float getRadius();
	void drawMonster(sf::Vector2f pos, float radius, sf::RenderWindow& window);
	bool isHovered(const sf::RenderWindow& window);
	void update(float deltaTime, sf::RenderWindow& window) override;
	void initialize() override;
	
private:
	void checkClicked(const sf::RenderWindow& window);
	int attack;
	int health;
	bool null;
	bool clicked;
	bool clickLock;
	string name;
	int slot;
	sf::Texture monsterTexture;
	sf::Font font;
	sf::CircleShape outerCircle;
	sf::Color borderColor;
};