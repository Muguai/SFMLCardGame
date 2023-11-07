#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
using namespace std;

class Monster {
public:
	Monster() {};
	int getAttack();
	int getHealth();
	int getCost();

private:
	int attack;
	int health;
	int cost;
};