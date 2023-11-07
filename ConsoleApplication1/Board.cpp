#include <iostream>
#include <Header/Board.hpp>
#include <Header/Monster.hpp>
#include <vector>
using namespace std;
vector<Monster> playerRow;
vector<Monster> opponentRow;
int maxCapacity = 5;

void Board::addPlayerMonster(){}
void Board::addOppponentMonster(){}
bool Board::isFull(){
	return playerRow.size() == maxCapacity;
}

