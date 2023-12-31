#include <Deck.hpp>
#include <Card.hpp>
#include <Shuffle.hpp>
#include <iostream>
#include <string>
#include <Resources.hpp>
#include <GameObjectManager.hpp>
#include <ManaHandler.hpp>

using namespace std;
deque<Card> cardStack;
sf::Vector2f position;
sf::Texture cardTexture;

Deck::Deck() {}
// Constructor:
Deck::Deck(int deckSize, bool _isOpponent, int faction){
	isOpponent = _isOpponent;

	// Load in resources:
	if (!cardTexture.loadFromFile("Images/card.png")) {
		cerr << "Failed to load card texture." << endl;
		cout << "cant find png!" << endl;
	}
	if (!font.loadFromFile("Fonts/COMIC.ttf")) {
		cout << "Error loading font!";
	}
	if (!soundBuffer.loadFromFile("Sound/whoosh.wav")) {
		cout << "Error loading sound effect!";
	}

	createDeck(deckSize, faction);
}

//	Simple getters:
int Deck::getSize() {
	return cardStack.size();
}

sf::Vector2f Deck::getPosition() {
	return position;
}

//	Simple setters:
void Deck::setPosition(sf::Vector2f newPosition) {
	position.x = newPosition.x;
	position.y = newPosition.y;
}

//	Logical Functions:

/*	returnCard()
*	A function that adds a card to the bottom of the deck.
*	Input: The card to be added.
*/

void Deck::returnCard(Card card){
	cardStack.push_back(card);
}

/*	createDeck()
	A function that creates a shuffled deck of size n.
	1. Read in the initial cards from the resources (The entire deck).
	2. Shuffle it.
	3. Trim it until it is of size n.
*/

void Deck::createDeck(int n, int faction) {
	if (faction == 1) {
		cardStack = getChaosSuperDeck();
	}
	else if (faction == 2){
		cardStack = getLifeSuperDeck();
	}
	shuffleDeck();
	while (cardStack.size() > n) {
		cardStack.pop_back();
	}

}


void Deck::update(float deltaTime, sf::RenderWindow& window) {
	sf::Vector2f newPos;
	if (!isOpponent) {
		newPos = sf::Vector2f(window.getSize().x / 2 + window.getSize().x / 3, window.getSize().y  - window.getSize().y / 5 ); 
	}
	else {
		newPos = sf::Vector2f(window.getSize().x / 2 - window.getSize().x / 3, window.getSize().y / 5 );
	}
	setPosition(newPos);
	renderDeck(window);
}

void Deck::initialize() {
}


/*	dealCard()
*	A function that deals the card from the top of the deck, popping and attaching
*	the card to the playerHand object.
*	Input: playerHand, the player object that is drawing the card on top of the stack.
*/

Card Deck::dealCard(Hand& playerHand) {
	sound.setBuffer(soundBuffer);
	sound.play();
	Card topCard = cardStack[0];

	topCard.setPosition(position);
	playerHand.addCard(topCard);

	cardStack.pop_front();
	return topCard;
}

/*	shuffleDeck()
	A function that randomly shuffles the deck with the Fisher Yates Algorithm.
	1. Init a permutation array (Fisher-Yates) and a temp card-vector
	2. Push the permutation into the temporary vector
	3. Deep Copy the content from the temp vector to the member one
*/

void Deck::shuffleDeck() {		
	int* permutation = permutedIndices(cardStack.size());
	vector<Card> tempCardStack;

	for (int i = 0; i < cardStack.size(); i++) {
		tempCardStack.push_back(cardStack[permutation[i]]);
	}

	for (int i = 0; i < cardStack.size(); i++) {
		cardStack[i] = tempCardStack[i];
	}
}

/*	(Test function)
*	printCards():
*	A function that iterates over the card-deque and prints invokes the toString for every card.
*	Basically printCards is a helper function used for testing every other function.
*/

void Deck::printCards(){
	for (int i = 0; i < cardStack.size(); i++) {
		cout << (i + 1);
		cout << " : ";
		cardStack[i].toString();
	}
}

//	Graphical functions:

/*
	renderDeck()
	A void function that renders the deck at the given position.
*/

void Deck::renderDeck(sf::RenderWindow& window){
	// 1. Create the card sprite:
	sf::Sprite cardSprite(cardTexture);
	cardSprite.setPosition(position.x, position.y);
	cardSprite.scale(sf::Vector2f(0.5, 0.5));
	
	// 2. Create the "how many cards left"-text, with an offsetted y:
	sf::Text cardsLeftText("Cards left: " + to_string(cardStack.size()), font, 18);
	cardsLeftText.setPosition(cardSprite.getPosition().x, cardSprite.getPosition().y -50);
	
	// 3. Append to the window
	window.draw(cardsLeftText);
	window.draw(cardSprite);
}
