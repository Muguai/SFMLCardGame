#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Header/Card.hpp>
#include <Header/Deck.hpp>
#include <Header/Hand.hpp>
#include <deque>
using namespace std;

class Deck : public GameObject {
private:
	deque<Card> cardStack;
	sf::Vector2f position;
	sf::Font font;
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
	bool isOpponent;
	

public:
	Deck(int deckSize, bool isOpponent, int faction);
	void returnCard(Card card);
	void createDeck(int n, int faction);
	void shuffleDeck();
	void printCards();
	void setPosition(sf::Vector2f newPosition);
	void renderDeck(sf::RenderWindow& window);
	int getSize();
	sf::Vector2f getPosition();
	Card dealCard(Hand& playerHand);
	void update(float deltaTime, sf::RenderWindow& window) override;
	void initialize() override;
};