#include <Deck.hpp>
#include <Card.hpp>
#include <Shuffle.hpp>
#include <iostream>

using namespace std;
deque<Card> cardStack;
sf::Vector2f position;
sf::Texture cardTexture;
	
// Constructor:
Deck::Deck(){
	position.x = 0;
	position.y = 0;
	if (!cardTexture.loadFromFile("card.png")) {
		// Handle loading error
		cerr << "Failed to load card texture." << endl;
		cout << "cant find png!" << endl;
	}
}

// Simple getters:
int Deck::getSize() {
	return cardStack.size();
}

sf::Vector2f Deck::getPosition() {
	return position;
}

// Simple setters:
void Deck::setPosition(sf::Vector2f newPosition) {
	position.x = newPosition.x;
	position.y = newPosition.y;
}

// Logical Functions:
/* addCard()
*  A function that adds a card to the bottom of the deck.
*  Input: The card to be added.
*/

void Deck::addCard(Card card){
	cardStack.push_back(card);
}

/*	dealCard()
*	A function that deals the card from the top of the deck, popping and returning it.
*/

Card Deck::dealCard() {
	Card topCard = cardStack[0];
	topCard.setPosition(position);
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

/* printCards():
*  A function that iterates over the card-deque and prints invokes the toString for every card.
*  Basically printCards is a helper function used for testing every other function.
*/

void Deck::printCards(){
	for (int i = 0; i < cardStack.size(); i++) {
		cout << (i + 1);
		cout << " : ";
		cardStack[i].toString();
	}
}

// Graphical functions: 
void Deck::drawDeck(sf::RenderWindow& window){
	sf::Sprite cardSprite(cardTexture);
	cardSprite.setPosition(position.x, position.y);
	sf::Vector2f scalingVector;
	scalingVector.x = 0.5;
	scalingVector.y = 0.5;
	cardSprite.scale(scalingVector);
	window.draw(cardSprite);
}