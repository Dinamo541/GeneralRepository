#ifndef CARDDECKS_HPP
#define CARDDECKS_HPP

#include "Cards.hpp"
#include <iostream>

class CardDecks {
private:
    Cards cardDeck[52];

public:
    CardDecks();
    ~CardDecks();

    void initialize();
    void shuffle();
    void displayDeck();
    Cards shareCard();
};

#endif