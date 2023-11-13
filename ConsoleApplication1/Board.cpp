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
	In the constructor every global value is set.
*/

Board::Board(sf::Vector2f boardPos, float delimiterSpace){
	maxCapacity = 5;
	radius = 80.0f;
	playerMonsters   = new Monster[maxCapacity];
	opponentMonsters = new Monster[maxCapacity];
	this->boardPos = boardPos;
	this->delimiterSpace = delimiterSpace;
	this->monsterXOffset = radius * 2 + delimiterSpace;
	size = 0;
	xMargin = 15;
}

/*	addPlayerMonster()
*	A function that takes in a monster object and adds it to the array
*	of player owned monsters. The array permutation can be edited to
*	change the spawning order of adding monsters to the board.
*/

void Board::addPlayerMonster(Monster monster){
	size++;
	int permutation [] = {2, 1, 3, 0, 4};
	for (int i = 0; i < maxCapacity; i++) {
		int index = permutation[i];
		if (playerMonsters[index].isNull()) {
			playerMonsters[index] = monster;
			break;
		}
	}
}

void Board::addOppponentMonster(){}

/*	isFull()
	Checks if the size has reached max capacity.
	Return: If it has, then true is returned, else false.
*/

bool Board::isFull(){
	return size == maxCapacity;
}

/*	renderPlayerMonsters()
	Iterate over every monster in the player array and render it.
	Render with a delimiter that seperates monsters (delimiter is set in constructor).
*/

void Board::renderPlayerMonsters(sf::RenderWindow& window, float monsterYOffset) {
	for (int i = 0; i < maxCapacity; i++) {
		if (!playerMonsters[i].isNull()) {
			sf::Vector2f offsetVector(boardPos.x + i*monsterXOffset, boardPos.y + monsterYOffset);
			playerMonsters[i].drawMonster(offsetVector, radius, window);
		}
	}
}

void Board::renderBoard(sf::RenderWindow& window) {
	// Calculating the total width of the table:
	float diameter = 2 * radius;
	float diameterSum = (maxCapacity * diameter);
	float twoEndMargin = 2 * xMargin;
	float delimeterSum = (maxCapacity - 1) * delimiterSpace;
	float tableWidth = diameterSum + twoEndMargin + delimeterSum;

	// Calculating data for the height of the table and placement of monsters:
	float yMargin = 20.0f;
	float centerDist = 100.0f;
	float tableHeight = 2 * diameter + centerDist + 2 * yMargin;

	// Placing down the table
	sf::Vector2f tablePos(boardPos.x - xMargin, boardPos.y);
	sf::RectangleShape table;
	table.setPosition(tablePos);
	table.setSize(sf::Vector2f(tableWidth, tableHeight));
	table.setFillColor(sf::Color::Red);
	window.draw(table);

	float playerYOffset = (tableHeight-diameter) - yMargin;
	renderPlayerMonsters(window, playerYOffset);
}