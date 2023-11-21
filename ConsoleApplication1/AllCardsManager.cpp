#pragma once
#include "AllCardsManager.hpp"
#include <iostream>
#include <vector>
#include "Card.hpp"
using namespace std;

AllCardsManager::AllCardsManager() {}

AllCardsManager& AllCardsManager::getInstance() {
    static AllCardsManager instance;
    return instance;
}

Card AllCardsManager::getCard(string cardName) {
    auto it = cardsMap.find(cardName);

    if (it != cardsMap.end()) {
        return it->second;
    }
    else {
        std::cerr << "Card not found: " << cardName << std::endl;
        return Card();
    }
}

void AllCardsManager::addCard(Card card) {
    cardsMap[card.cardName] = card;
}


AllCardsManager::~AllCardsManager() {
}
