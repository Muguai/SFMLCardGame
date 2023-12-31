#include <iostream>
#include <Header/Board.hpp>
#include <Header/Monster.hpp>
#include <optional>
#include <vector>

using namespace std;
Monster* playerMonsters;
Monster* opponentMonsters;

Board::Board() {}

/*	Board()
	The constructor for the board.
	The position of the board is taken in and a delimiter space between each monster.
	In the constructor every global value is set.
*/

Board::Board(Hand& playerHand, ManaHandler& playerMana, sf::Vector2f boardPos, float delimiterSpace){
	maxCapacity = 5;
	radius = 80.0f;
	playerMonsters   = new Monster[maxCapacity];
	opponentMonsters = new Monster[maxCapacity];
	this->playerHand = &playerHand;
	this->playerMana = &playerMana;
	this->boardPos = boardPos;
	this->delimiterSpace = delimiterSpace;
	this->monsterXOffset = radius * 2 + delimiterSpace;
	playerSize = 0;
	oppSize = 0;
	xMargin = 15;

	if (!boardTexture.loadFromFile("Images/Wood.jpg")) {
		cout << "Error loading card image!";
	}
}

/*	update()
	The update function in board does many taskes:
	1. Iterate over every player monster and count how many are clicked (and call their update).
	2. Unclick player monsters if there are multiple clicked ones.
	For example, if a player clicks his own monster 1 and then his own monster 2, both should be
	unclicked as we cannot attack ourselves.
	3. Iterate over every opponent monster instead and count their clicks + update.
	4. Call the fight() function if one opponent monster and one friendly monster is clicked.
	5. Unclick every monster on the board (In case enemy monsters were clicked first).
	6. Check if the player is trying to put out cards on the board.
	7. Render everything.
*/

void Board::update(float deltaTime, sf::RenderWindow& window) {
	// A). Handle player monsters already out on the board:
	// 1. Check which player monsters are clicked
	int clickedCounter = 0;
	for (int i = 0; i < maxCapacity; i++) {
		if (!playerMonsters[i].isNull()) {
			playerMonsters[i].update(deltaTime, window);
			if (playerMonsters[i].getClicked()) {
				clickedCounter ++;
			}
		}
	}

	// 2. Handle these player clicks:
	if (clickedCounter > 1) {
		for (int i = 0; i < maxCapacity; i++) {
			if (!playerMonsters[i].isNull()) {
				playerMonsters[i].unclick();
			}
		}
	}

	// 3. Handle opponent monsters being clicked:
	int oppClickedCounter = 0;
	for (int i = 0; i < maxCapacity; i++) {
		if (!opponentMonsters[i].isNull()) {
			opponentMonsters[i].update(deltaTime, window);
			if (opponentMonsters[i].getClicked()) {
				oppClickedCounter++;
			}
		}
	}

	// 4. If a player monster is clicked and an opponent monster, find index & let them fight:
	if (clickedCounter == 1 && oppClickedCounter == 1) {
		int playerIndex = 0;
		int oppIndex = 0;
		for (int i = 0; i < maxCapacity; i++) {
			if (!playerMonsters[i].isNull() && playerMonsters[i].getClicked()) {
				playerIndex = i;
			}
		}
		for (int i = 0; i < maxCapacity; i++) {
			if (!opponentMonsters[i].isNull() && opponentMonsters[i].getClicked()) {
				oppIndex = i;
			}
		}
	
		fight(playerIndex, oppIndex);
	}

	// 5. For each update/fight, make sure that all the opponents are unclicked (player untouched):
	for (int i = 0; i < maxCapacity; i++) {
		if (!opponentMonsters[i].isNull()) {
			opponentMonsters[i].unclick();
		}
	}

	// 6. Handle laying out cards to the board:
	if (isHovered(window) && !isFull(true)) {
		Card draggedCard = (*playerHand).getDraggedCard();
		draggedCard.toString();

		if (!draggedCard.isNull() && (*playerMana).tryPlaceMonster(draggedCard.getCost())) {
			int atk = draggedCard.attack;
			int hp = draggedCard.health;
			string name = draggedCard.cardName;
			Monster monster(atk, hp, name);
			addPlayerMonster(monster);
			(*playerHand).deleteCard();
		}
	}

	// 7. Render:
	renderBoard(window);
}

/*	fight()
	A function that simulates a fight from the playerMonsters and the OpponentMonsters.
	1. First a playerMonster and a opponentMonster is dealing damage to each other.
	2. Then they are unclicked. 
*/

void Board::fight(int playerIndex, int oppIndex) {
	// 1. They are unclicked
	playerMonsters[playerIndex].unclick();
	opponentMonsters[oppIndex].unclick();

	// 2. Two monsters attack each other:
	playerMonsters[playerIndex].takeDamage(opponentMonsters[oppIndex].getAttack());
	opponentMonsters[oppIndex].takeDamage(playerMonsters[playerIndex].getAttack());
	

}

void Board::initialize() {}

/*	addPlayerMonster()
*	A function that takes in a monster object and adds it to the array
*	of player owned monsters. The array permutation can be edited to
*	change the spawning order of adding monsters to the board.
*/

void Board::addPlayerMonster(Monster monster){
	playerSize++;
	int permutation[] = {2, 1, 3, 0, 4};
	for (int i = 0; i < maxCapacity; i++) {
		int index = permutation[i];
		if (playerMonsters[index].isNull()) {
			playerMonsters[index] = monster;
			break;
		}
	}
}


/*	addOpponentMonster()
	Does the same as addPlayerMonster() but for the opponent's
	monsters instead of the player's.
*/

void Board::addOppponentMonster(Monster monster){
	oppSize++;
	int permutation[] = { 2, 1, 3, 0, 4 };
	for (int i = 0; i < maxCapacity; i++) {
		int index = permutation[i];
		if (opponentMonsters[index].isNull()) {
			opponentMonsters[index] = monster;
			break;
		}
	}
}

/*	isFull()
	Checks if the size has reached max capacity.
	Input: The boolean value, pertaining to if you want to check the
	player or the opponent's size.
	Return: If it has, then true is returned, else false.
*/

bool Board::isFull(bool isPlayer){
	if (isPlayer) {
		return playerSize == maxCapacity;
	}
	else {
		return oppSize == maxCapacity;
	}
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

/*	renderOpponentMonster()
*	Does the same thing as renderPlayerMonsters() but for the opponent's monsters.
	The main difference is that the yOffset is passed in as a different value in renderBoard() below.
	The different yOffset makes it so the player's monsters are rendered on one side and the opponent's
	monsters on the other.
*/

void Board::renderOpponentMonsters(sf::RenderWindow& window, float monsterYOffset) {
	for (int i = 0; i < maxCapacity; i++) {
		if (!opponentMonsters[i].isNull()) {
			sf::Vector2f offsetVector(boardPos.x + i * monsterXOffset, boardPos.y + monsterYOffset);
			opponentMonsters[i].drawMonster(offsetVector, radius, window);

		}
	}
}

/*	isHovered()
	Make a check to see if the table is hovered over.
	If it is, then return true. This is used so that we know when to put a dragged card on the board.
*/

bool Board::isHovered(const sf::RenderWindow& window) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::FloatRect cardBounds = table.getGlobalBounds();
	return cardBounds.contains(static_cast<sf::Vector2f>(mousePosition));
}

/*	renderBoard()
	The main graphical function of the board class.
	renderBoard() performs calculations and renders everything that is on the board.
	This includes the two player's monsters as well as the actual board.
*/

void Board::renderBoard(sf::RenderWindow& window) {
	// 1. Calculating the total width of the table:
	float diameter = 2 * radius;
	float diameterSum = (maxCapacity * diameter);
	float twoEndMargin = 2 * xMargin;
	float delimeterSum = (maxCapacity - 1) * delimiterSpace;
	float tableWidth = diameterSum + twoEndMargin + delimeterSum;

	// 2. Calculating data for the height of the table:
	float yMargin = 20.0f;
	float centerDist = 40.0f;
	float tableHeight = 2 * diameter + centerDist + 2 * yMargin;

	// 3. Rendering the table
	sf::Vector2f tablePos(boardPos.x - xMargin, boardPos.y);
	table.setTexture(&boardTexture);
	table.setPosition(tablePos);
	table.setSize(sf::Vector2f(tableWidth, tableHeight));
	window.draw(table);

	// 4. Calculate offsets for monsters and render them on top of the table:
	float playerYOffset = (tableHeight-diameter) - yMargin;
	float opponentYOffset = yMargin;
	renderPlayerMonsters(window, playerYOffset);
	renderOpponentMonsters(window, opponentYOffset);
	
}