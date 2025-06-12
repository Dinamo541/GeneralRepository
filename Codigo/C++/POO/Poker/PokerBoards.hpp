#ifndef POKERBOARDS_HPP
#define POKERBOARDS_HPP

#include "CardDecks.hpp"
#include <iostream>
#include <string>

class PokerBoards {
private:
    Cards playersCards[10][2];
    Cards playerHands[10][7];
    Cards flop[3];
    Cards turn;
    Cards river;
    Cards pot[5];
    int handLevel[10];
    int currentPlayers;
    int choice;

public:
    PokerBoards(int players);
    ~PokerBoards() {}

    int getCurrentPlayers();
    std::string getFlop();
    std::string getTurn();
    std::string getRiver();

    int findWiner();
    int tieBreaker(int winnerIndex, int playerTie);
    int findHighestCard(int index, int highestCard, bool tied[10]);
    void dealCards(CardDecks deck);
    void displayPlayersCards();
    void showPlayerCards(int playerIndex);
    void displayFlop();
    void displayTurn();
    void displayRiver();
    void displayPot();
    void choosePlayerIndex(std::string pot);
    void setHandLevel(int playerIndex);
    void sorterCardsHighestToLowest(int playerIndex);
    void swapCards(int playerIndex, int index);
    void burbelSorterSuit(int playerIndex);
    void swapArrayBySuit(int player, int index);
    void SortPlayerCards(int playerIndex);
    bool findStraightFlush(int playerIndex);
    bool findADifferentPair(int playerIndex, int index);
};

#endif