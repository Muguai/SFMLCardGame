#pragma once
#include <Header/Monster.hpp>
using namespace std;
class Board {
public:
	Board(sf::Vector2f boardPos, float delimiterSpace);
	void addPlayerMonster(Monster monster);
	void addOppponentMonster();
	bool isFull();
	void renderPlayerMonsters(sf::RenderWindow& window);

private:
	int size;
	sf::Vector2f boardPos;
	float delimiterSpace;
	int maxCapacity;
	float radius;
};