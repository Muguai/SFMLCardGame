#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Header/Card.hpp>
#include <Header/Deck.hpp>
#include <Header/Hand.hpp>
#include <deque>
using namespace std;

class Deck {
private:
	deque<Card> cardStack;
	sf::Vector2f position;
	sf::Font font;
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
	

public:
	Deck(int deckSize, int x, int y);
	void returnCard(Card card);
	void createDeck(int n);
	void shuffleDeck();
	void printCards();
	void setPosition(sf::Vector2f newPosition);
	void renderDeck(sf::RenderWindow& window);
	int getSize();
	sf::Vector2f getPosition();
	Card dealCard(Hand& playerHand);
};