#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <Card.hpp>
using namespace std;

class AllCardsManager {
public:
    AllCardsManager();

    static AllCardsManager& getInstance();

    void addCard(string cardName, Card card);

    Card getCard(string cardName);

    void addCard(Card card);

    ~AllCardsManager();

private:
    unordered_map<string, Card> cardsMap;
};
