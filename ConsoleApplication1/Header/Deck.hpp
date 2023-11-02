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
	Deck();
	void addCard(Card card);
	Card dealCard(Hand& playerHand);
	void shuffleDeck();
	void printCards();
	int getSize();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f newPosition);
	void drawDeck(sf::RenderWindow& window);

};