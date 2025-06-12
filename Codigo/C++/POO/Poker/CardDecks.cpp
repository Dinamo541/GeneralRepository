#include "CardDecks.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

CardDecks::CardDecks() {
    initialize();
    shuffle();
    shuffle();
}
CardDecks::~CardDecks() {}

void CardDecks::initialize() {
    for (int i = 0; i < 52; i++) {
        cardDeck[i] = Cards(i);
    }
}
void CardDecks::shuffle() {
    std::srand(std::time(0));

    for (int i = 51; i > 0; --i) {
        int j = std::rand() % (i + 1);
        Cards temp = cardDeck[i];
        cardDeck[i] = cardDeck[j];
        cardDeck[j] = temp;
    }
}
void CardDecks::displayDeck() {
    for (int i = 0; i < 52; i++) {
        cardDeck[i].display();
        std::cout << std::endl;
    }
}
Cards CardDecks::shareCard() {
    Cards card = cardDeck[0];
    for (int i = 0; i < 51; i++) {
        cardDeck[i] = cardDeck[i + 1];
    }
    cardDeck[51] = Cards();
    return card;
}