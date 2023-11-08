#include <iostream>
#include <Header/Board.hpp>
#include <Header/Monster.hpp>
#include <optional>
#include <vector>

using namespace std;
Monster* playerMonsters;
Monster* opponentMonsters;

/*	Board()
	The constructor for the board.
	The position of the board is taken in and a delimiter space between each monster.
*/

Board::Board(sf::Vector2f boardPos, float delimiterSpace){
	maxCapacity = 5;
	radius = 80.0f;

	playerMonsters   = new Monster[maxCapacity];
	opponentMonsters = new Monster[maxCapacity];
	this->boardPos = boardPos;
	this->delimiterSpace = radius * 2 + delimiterSpace;
	
	size = 0;
}

/*	addPlayerMonster
*	A function that takes in a monster object and adds it to the array
*	of player owned monsters.
*/

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

/*	renderPlayerMonsters()
	Iterate over every monster in the player array and render it.
	Render with a delimiter that seperates monsters (delimiter is set in constructor).
*/

void Board::renderPlayerMonsters(sf::RenderWindow& window) {
	for (int i = 0; i < size; i++) {
		if (!playerMonsters[i].isNull()) {
			sf::Vector2f offsetVector(boardPos.x + i*delimiterSpace, boardPos.y);
			playerMonsters[i].drawMonster(offsetVector, radius, window);
		}
	}
}

