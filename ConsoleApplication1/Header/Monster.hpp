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
	void takeDamage(int dmg);
	void unclick();
	bool getClicked();
	void drawMonster(sf::Vector2f pos, float radius, sf::RenderWindow& window);
	bool isHovered(const sf::RenderWindow& window);
	void update(float deltaTime, sf::RenderWindow& window) override;
	void initialize() override;
	
private:
	void checkClicked(const sf::RenderWindow& window);
	void dying(float deltaTime, sf::RenderWindow& window);
	bool isDead;
	float deathStart;
	float deathTime;
	float deathPercentage;
	float deathTimer;

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