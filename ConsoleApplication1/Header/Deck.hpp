#pragma once
#include <SFML/Graphics.hpp>
#include <Header/Card.hpp>
#include <Header/Deck.hpp>
#include <deque>
using namespace std;

class Deck {
private:
	deque<Card> cardStack;
	void drawDeck();
	int x;
	int y;

public:
	Deck();
	void addCard(Card card);
	void shuffleDeck();
	void printCards();
	int getSize();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f newPosition);
	void drawDeck(sf::RenderWindow& window);

};