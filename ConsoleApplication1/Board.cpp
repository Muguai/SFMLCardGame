#include <iostream>
#include <Header/Board.hpp>
#include <vector>
using namespace std;
vector<int> playerRow;
vector<int> opponentRow;
int maxCapacity = 5;

void Board::addPlayerMonster(){}
void Board::addOppponentMonster(){}

bool Board::isFull(){
	return playerRow.size() == maxCapacity;
}

