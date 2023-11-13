#pragma once
#include <Header/Monster.hpp>
using namespace std;
class Board {
public:
	Board(sf::Vector2f boardPos, float delimiterSpace);
	void addPlayerMonster(Monster monster);
	void addOppponentMonster();
	bool isFull();
	void renderBoard(sf::RenderWindow& window);

private:
	void renderPlayerMonsters(sf::RenderWindow& window);
	int size;
	sf::Vector2f boardPos;
	float delimiterSpace;
	float monsterXOffset;
	int maxCapacity;
	float radius;
	float xMargin;
};