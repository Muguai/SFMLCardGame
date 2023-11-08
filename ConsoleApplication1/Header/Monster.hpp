#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
using namespace std;

class Monster {
public:
	Monster(int atk, int hp, string n, int s);
	int getAttack();
	int getHealth();
	void drawMonster(sf::Vector2f pos, float radius, sf::RenderWindow& window);

private:
	int attack;
	int health;
	string name;
	int slot;
	sf::Texture monsterTexture;
	sf::Font font;
};