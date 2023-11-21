#pragma once
#include <Header/Monster.hpp>
#include "GameObject.hpp"
#include <Header/ManaHandler.hpp>
#include <Header/Hand.hpp>

using namespace std;
class Board : public GameObject{
public:
	Board();
	Board(Hand& PlayerHand, ManaHandler& playerMana, sf::Vector2f boardPos, float delimiterSpace);
	void addPlayerMonster(Monster monster);
	void addOppponentMonster(Monster monster);
	bool isFull(bool isPlayer);
	void renderBoard(sf::RenderWindow& window);
	bool isHovered(const sf::RenderWindow& window);
	void update(float deltaTime, sf::RenderWindow& window) override;
	void initialize() override;


private:
	void renderPlayerMonsters(sf::RenderWindow& window, float monsterYOffset);
	void renderOpponentMonsters(sf::RenderWindow& window, float monsterYOffset);
	void fight(int playerIndex, int oppIndex);

	Hand* playerHand;
	ManaHandler* playerMana;
	int playerSize;
	int oppSize;
	sf::Vector2f boardPos;
	float delimiterSpace;
	float monsterXOffset;
	int maxCapacity;
	float radius;
	float xMargin;
	sf::Texture boardTexture;
	sf::RectangleShape table;
};