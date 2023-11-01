#pragma once
#include <SFML/Graphics.hpp>
#include <Header/Card.hpp>
#include <Header/Deck.hpp>
#include <deque>
using namespace std;

class Deck {
private:
	deque<Card> cardStack;

public:
	Deck();
	void addCard(Card card);
	void shuffleDeck();
	void printCards();
	int getSize();
};