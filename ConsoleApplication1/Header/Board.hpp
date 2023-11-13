#pragma once
#include <Header/Monster.hpp>
using namespace std;
class Board {
public:
	Board(sf::Vector2f boardPos, float delimiterSpace);
	void addPlayerMonster(Monster monster);
	void addOppponentMonster(Monster monster);
	bool isFull(bool isPlayer);
	void renderBoard(sf::RenderWindow& window);

private:
	void renderPlayerMonsters(sf::RenderWindow& window, float monsterYOffset);
	void renderOpponentMonsters(sf::RenderWindow& window, float monsterYOffset);

	int playerSize;
	int oppSize;
	sf::Vector2f boardPos;
	float delimiterSpace;
	float monsterXOffset;
	int maxCapacity;
	float radius;
	float xMargin;
	sf::Texture boardTexture;
};