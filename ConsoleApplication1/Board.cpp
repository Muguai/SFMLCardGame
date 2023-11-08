#include <iostream>
#include <Header/Board.hpp>
#include <Header/Monster.hpp>
#include <optional>
#include <vector>

using namespace std;
Monster* playerMonsters;
Monster* opponentMonsters;

Board::Board(sf::Vector2f boardPos, float delimiterSpace){
	maxCapacity = 5;
	playerMonsters   = new Monster[maxCapacity];
	opponentMonsters = new Monster[maxCapacity];
	
	radius = 80.0f;
	size = 0;
	this->boardPos = boardPos;
	this->delimiterSpace = radius * 2 + delimiterSpace;
}

void Board::addPlayerMonster(Monster monster){
	size++;
	for (int i = 0; i < maxCapacity; i++) {
		if (playerMonsters[i].isNull()) {
			playerMonsters[i] = monster;
			break;
		}
	}
}

void Board::addOppponentMonster(){}
bool Board::isFull(){
	return size == maxCapacity;
}

void Board::renderPlayerMonsters(sf::RenderWindow& window) {
	for (int i = 0; i < size; i++) {
		if (!playerMonsters[i].isNull()) {
			sf::Vector2f offsetVector(boardPos.x + i*delimiterSpace, boardPos.y);
			playerMonsters[i].drawMonster(offsetVector, radius, window);
		}
	}
}

