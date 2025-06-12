#include "PokerBoards.hpp"
#include <iostream>
#include <string>

PokerBoards::PokerBoards(int players) {
    currentPlayers = players;
    for (int i = 0; i < 10; i++) {
        handLevel[i] = 10;
        for (int j = 0; j < 2; j++) {
            playersCards[i][j] = Cards();
        }
        for (int j = 0; j < 5; j++) {
            playerHands[i][j] = Cards();
        }
        for (int j = 0; j < 7; j++) {
            playerHands[i][j] = Cards();
        }
    }
    
}
PokerBoards::~PokerBoards() {}

int PokerBoards::getCurrentPlayers() {
    return currentPlayers;
}
std::string PokerBoards::getFlop() {
    std::string flopString = "  Flop: ";
    for (int i = 0; i < 3; i++) {
        flopString += flop[i].getCard();
        flopString += " ";
    }
    return flopString;
}
std::string PokerBoards::getTurn() {
    std::string turnString = "  Turn: ";
    for (int i = 0; i < 3; i++) {
        turnString += flop[i].getCard();
        turnString += " ";
    }
    turnString += turn.getCard();
    return turnString;
}
std::string PokerBoards::getRiver() {
    std::string riverString = "  River: ";
    for (int i = 0; i < 3; i++) {
        riverString += flop[i].getCard();
        riverString += " ";
    }
    riverString += turn.getCard();
    riverString += " ";
    riverString += river.getCard();
    return riverString;
}

void PokerBoards::dealCards(CardDecks deck) {
    for (int i = 0; i < 3; i++) {
        flop[i] = deck.shareCard();
        pot[i] = flop[i];
    }
    turn = deck.shareCard();
    river = deck.shareCard();
    pot[3] = turn;
    pot[4] = river;
    for (int i = 0; i < currentPlayers; i++) {
        playersCards[i][0] = deck.shareCard();
        playersCards[i][1] = deck.shareCard();
        for (int j = 0; j < 5; j++) {
            playerHands[i][j] = pot[j];
        }
        playerHands[i][5] = playersCards[i][0];
        playerHands[i][6] = playersCards[i][1];
    }
    
}
void PokerBoards::displayPlayersCards() {
    for (int i = 0; i < currentPlayers; i++) {
        playersCards[i][0].display();
        playersCards[i][1].display();
    }
}
void PokerBoards::showPlayerCards(int playerIndex) {
    if (playerIndex < 0 || playerIndex >= currentPlayers) {
        std::cout << "Invalid player index." << std::endl;
        return;
    }
    playersCards[playerIndex][0].display();
    std::cout << " ";
    playersCards[playerIndex][1].display();
}
void PokerBoards::displayFlop() {
    std::cout << " ";
    for (int i = 0; i < 3; i++) {
        flop[i].display();
        std::cout << " ";
    }
}
void PokerBoards::displayTurn() {
    turn.display();
}
void PokerBoards::displayRiver() {
    river.display();
}
void PokerBoards::displayPot() {
    for (int i = 0; i < 5; i++) {
        pot[i].display();
        std::cout << " ";
    }
}
void PokerBoards::choosePlayerIndex(std::string pot) {
    while (true) {
        std::cout << "want to see a player hand? (1 to " << getCurrentPlayers() << ", 0 to continue): ";
        std::cin.clear();
        std::cin >> choice;
        while (std::cin.fail() || getCurrentPlayers() < choice || choice < 0) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a valid index (1 - " << getCurrentPlayers() << "): ";
            std::cin >> choice;
        }
        if (choice == 0) {
            break;
        } else {
            system("cls");
            std::cout << pot << std::endl;
            std::cout << "\nPlayer " << choice << " cards:  ";
            showPlayerCards(choice - 1);
            std::cout << "\n";
        }
    }
}
int PokerBoards::findWiner() {
    for (int i = 0; i < currentPlayers; i++) {
        sorterCardsHighestToLowest(i);
        setHandLevel(i);
    }
    int bestHand = handLevel[0];
    int winnerIndex = 0;
    for (int i = 1; i < currentPlayers; i++) {
        if (handLevel[i] < bestHand) {
            bestHand = handLevel[i];
            winnerIndex = i;
        }
    }
    for (int i = 0; i < currentPlayers; i++) {
        if (handLevel[winnerIndex] == handLevel[i] && winnerIndex != i) {
            winnerIndex = tieBreaker(winnerIndex, i);
        }
    }
    winnerIndex++;
    return bestHand * 100 + winnerIndex;
}
int PokerBoards::tieBreaker(int winnerIndex, int playerTie) {
    if (playersCards[winnerIndex][0].getValue() < playersCards[playerTie][0].getValue()) {
        winnerIndex = playerTie;
    } else if (playersCards[winnerIndex][1].getValue() < playersCards[playerTie][1].getValue()) {
        winnerIndex = playerTie;
    }
    return winnerIndex;
}
int PokerBoards::findHighestCard(int index, int highestCard, bool tied[10]) {
    for (int j = index + 1; j < currentPlayers; j++) {
        if (tied[index] == tied[j] && highestCard < playersCards[j][0].getValue()) {
            return j;
        }
    }
    return index;
}
void PokerBoards::setHandLevel(int playerIndex) {
    sorterCardsHighestToLowest(playerIndex);
    bool two, three, four;

    if (findStraightFlush(playerIndex) && playerHands[playerIndex][0].getValue() == 12) {
        handLevel[playerIndex] = 1;
        return;
    }
    if (findStraightFlush(playerIndex)) {
        handLevel[playerIndex] = 2;
        return;
    }
    for (int i = 0; i < 4; i++) {
        two = playerHands[playerIndex][i].getValue() == playerHands[playerIndex][i+1].getValue();
        three = playerHands[playerIndex][i].getValue() == playerHands[playerIndex][i+2].getValue();
        four = playerHands[playerIndex][i].getValue() == playerHands[playerIndex][i+3].getValue();
        if (two && three && four) {
            handLevel[playerIndex] = 3;
            return;
        }
    }
    for (int i = 0; i < 5; i++) {
        two = playerHands[playerIndex][i].getValue() == playerHands[playerIndex][i+1].getValue();
        three = playerHands[playerIndex][i].getValue() == playerHands[playerIndex][i+2].getValue();
        if (two && three) {
            if (findADifferentPair(playerIndex, i)) {
                handLevel[playerIndex] = 4;
                return;
            }
        }
    }
    bool five;
    for (int i = 0; i < 3; i++) {
        two = playerHands[playerIndex][i].getSuitValue() == playerHands[playerIndex][i+1].getSuitValue();
        three = playerHands[playerIndex][i].getSuitValue() == playerHands[playerIndex][i+2].getSuitValue();
        four = playerHands[playerIndex][i].getSuitValue() == playerHands[playerIndex][i+3].getSuitValue();
        five = playerHands[playerIndex][i].getSuitValue() == playerHands[playerIndex][i+4].getSuitValue();
        if (two && three && four && five) {
            handLevel[playerIndex] = 5;
            return;
        }
    }
    bool straight;
    for (int i = 0; i < 3; i++) {
        straight = true;
        for (int j = i; j < 5; j++) {
            if (playerHands[playerIndex][i+j].getValue() != playerHands[playerIndex][i+j+1].getValue() + 1) {
                straight = false;
                break;
            }
        }
        if (straight) {
            handLevel[playerIndex] = 6;
            return;
        }
    }
    for (int i = 0; i <= 4; i++) {
        two = playerHands[playerIndex][i].getValue() == playerHands[playerIndex][i+1].getValue();
        three = playerHands[playerIndex][i].getValue() == playerHands[playerIndex][i+2].getValue();
        if (two && three) {
            handLevel[playerIndex] = 7;
            return;
        }
    }
    int pairs = 0;
    for (int i = 0; i < 6; i++) {
        if (playerHands[playerIndex][i].getValue() == playerHands[playerIndex][i+1].getValue()) {
            pairs++;
            i++;
        }
    }
    if (pairs > 1) {
        handLevel[playerIndex] = 8;
        return;
    } else if (pairs == 1) {
        handLevel[playerIndex] = 9;
        return;
    }
    handLevel[playerIndex] = 10;
}
bool PokerBoards::findStraightFlush(int playerIndex) {
    bool straightFlush;
    int suit, value;
    for (int i = 0; i <= 2; i++) {
        straightFlush = true;
        suit = playerHands[playerIndex][i].getSuitValue();
        value = playerHands[playerIndex][i].getValue();
        for (int j = 1; j < 5; j++) {
            if (playerHands[playerIndex][i + j].getSuitValue() != suit ||
                playerHands[playerIndex][i + j].getValue() != value - j) {
                straightFlush = false;
                j += 6;
            }
        }
        if (straightFlush) {
            return true;
        }
    }
    return false;
}
bool PokerBoards::findADifferentPair(int playerIndex, int index) {
    bool pair;
    for (int j = 0; j < 5; j++) {
        pair = playerHands[playerIndex][j].getValue() == playerHands[playerIndex][j+1].getValue();
        if (j != index && j != index+1 && j != index+2 && pair) {
            return true;
        }
    }
    return false;
}
void PokerBoards::sorterCardsHighestToLowest(int playerIndex) {
    for (int i = 0; i < 6; ++i) {
        swapCards(playerIndex, i);
    }
}
void PokerBoards::swapCards(int playerIndex, int index) {
    for (int j = 0; j < 7 - index - 1; ++j) {
        if (playerHands[playerIndex][j].getValue() < playerHands[playerIndex][j + 1].getValue()) {
            Cards temp = playerHands[playerIndex][j];
            playerHands[playerIndex][j] = playerHands[playerIndex][j + 1];
            playerHands[playerIndex][j + 1] = temp;
        }
    }
    
}
void PokerBoards::burbelSorterSuit(int playerIndex) {
    for (int j = 0; j < 7 - 1; j++) {
        swapArrayBySuit(playerIndex, j);
    }
}
void PokerBoards::swapArrayBySuit(int player, int index) {
    for (int j = 0; j < 7 - index - 1; j++) {
        if (playerHands[player][j].getSuitValue() > playerHands[player][j + 1].getSuitValue()) {
            Cards swap = playerHands[player][j];
            playerHands[player][j] = playerHands[player][j + 1];
            playerHands[player][j + 1] = swap;
        }
    }
}
void PokerBoards::SortPlayerCards(int playerIndex) {
    if (playersCards[playerIndex][0].getValue() < playersCards[playerIndex][1].getValue()) {
        Cards swap = playerHands[playerIndex][0];
        playerHands[playerIndex][0] = playerHands[playerIndex][1];
        playerHands[playerIndex][1] = swap;
    }
}