#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Cards {
private:
    int id;
    char suits[4] = {'d', 'c', 's', 'h'};
    char ranks[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
public:
    Cards() : id(0) {}
    Cards(int id) : id(id) {}

    ~Cards() {}

    char getSuit() {
        return suits[id / 13];
    }
    char getRank() {
        return ranks[id % 13];
    }
    int getValue() {
        return id % 13;
    }
    int getSuitValue() {
        return id / 13;
    }
    void display() {
        std::cout << getRank() << getSuit();
    }
    std::string getCard() {
        std::string ranksS[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"}; 
        std::string suitsS[4] = {"d", "c", "s", "h"};
        return ranksS[id % 13] + suitsS[id / 13];
    }
};

class CardDecks {
private:
    Cards cardDeck[52];

public:
    CardDecks() {
        initialize();
        shuffle();
        shuffle();
    }
    ~CardDecks() {}

    void initialize() {
        for (int i = 0; i < 52; i++) {
            cardDeck[i] = Cards(i);
        }
    }
    void shuffle() {
        for (int i = 51; i > 0; --i) {
            int j = std::rand() % (i + 1);
            Cards temp = cardDeck[i];
            cardDeck[i] = cardDeck[j];
            cardDeck[j] = temp;
        }
    }
    void displayDeck() {
        for (int i = 0; i < 52; i++) {
            cardDeck[i].display();
            std::cout << std::endl;
        }
    }
    Cards shareCard() {
        Cards card = cardDeck[0];
        for (int i = 0; i < 51; i++) {
            cardDeck[i] = cardDeck[i + 1];
        }
        cardDeck[51] = Cards();
        return card;
    }
};

class PokerBoards {
protected:
    Cards playersCards[10][2];
    Cards playerHands[10][7];
    Cards flop[3];
    Cards turn;
    Cards river;
    Cards pot[5];
    int handLevel[10];
    int currentPlayers;
    int choice;
    int bestHand;
    int winner;
    bool playersPlaying[10];

public:
    PokerBoards() {
        currentPlayers = 10;
        bestHand = 0;
        winner = 0;
        for (int i = 0; i < 10; i++) {
            handLevel[i] = 10;
            playersPlaying[i] = true;
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
    PokerBoards(int players) {
        currentPlayers = players;
        bestHand = 0;
        winner = 0;
        for (int i = 0; i < 10; i++) {
            handLevel[i] = 10;
            playersPlaying[i] = true;
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
    ~PokerBoards() {}

    int getCurrentPlayers() {
        return currentPlayers;
    }
    std::string getFlop() {
        std::string flopString = "  Flop: ";
        for (int i = 0; i < 3; i++) {
            flopString += flop[i].getCard();
            flopString += " ";
        }
        return flopString;
    }
    std::string getTurn() {
        std::string turnString = "  Turn: ";
        for (int i = 0; i < 3; i++) {
            turnString += flop[i].getCard();
            turnString += " ";
        }
        turnString += turn.getCard();
        return turnString;
    }
    std::string getRiver() {
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

    void dealCards(CardDecks deck) {
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
    void displayPlayersCards() {
        for (int i = 0; i < currentPlayers; i++) {
            playersCards[i][0].display();
            playersCards[i][1].display();
        }
    }
    void showPlayerCards(int playerIndex) {
        if (!playersPlaying[playerIndex]) {
            std::cout << "FOLD ";
        }
        playersCards[playerIndex][0].display();
        std::cout << " ";
        playersCards[playerIndex][1].display();
    }
    void displayFlop() {
        std::cout << " ";
        for (int i = 0; i < 3; i++) {
            flop[i].display();
            std::cout << " ";
        }
    }
    void foldAPlayer(int playerIndex) {
        if (!playersPlaying[playerIndex]) {
            std::cout << "This player has already folded.\n";
        } else {
            playersPlaying[playerIndex] = false;
            std::cout << "Player number " << playerIndex + 1 << " FOLD.\n";
        }
    }
    void displayTurn() {
        turn.display();
    }
    void displayRiver() {
        river.display();
    }
    void displayPot() {
        for (int i = 0; i < 5; i++) {
            pot[i].display();
            std::cout << " ";
        }
    }
    void findWiner() {
        for (int i = 0; i < currentPlayers; i++) {
            sorterCardsHighestToLowest(i);
            setHandLevel(i);
            SortPlayerCards(i);
        }
        for (int i = 0; i < currentPlayers; i++) {
            if (playersPlaying[i]) {
                bestHand = handLevel[i];
                winner = i;
                break;
            }
        }
        for (int i = 0; i < currentPlayers; i++) {
            if (playersPlaying[i] && handLevel[i] < bestHand && winner != i) {
                bestHand = handLevel[i];
                winner = i;
            }
        }
        for (int i = 0; i < currentPlayers; i++) {
            if (handLevel[winner] == handLevel[i] && winner != i && playersPlaying[i]) {
                tieBreaker(i);
            }
        }
    }
    void tieBreaker(int playerTie) {
        if (playersCards[winner][0].getValue() < playersCards[playerTie][0].getValue()) {
            winner = playerTie;
        } else if (playersCards[winner][1].getValue() < playersCards[playerTie][1].getValue()) {
            winner = playerTie;
        }
    }
    int findHighestCard(int index, int highestCard, bool tied[10]) {
        for (int j = index + 1; j < currentPlayers; j++) {
            if (tied[index] == tied[j] && highestCard < playersCards[j][0].getValue()) {
                return j;
            }
        }
        return index;
    }
    void setHandLevel(int playerIndex) {
        sorterCardsHighestToLowest(playerIndex);
        int counter;
        bool two, three, four, diferent;

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
            if (two && three && findADifferentPair(playerIndex, i)) {
                handLevel[playerIndex] = 4;
                return;
            }
        }
        for (int i = 0; i < 3; i++) {
            counter = 0;
            for (int j = i + 1; j < 7 && counter < 4; j++){
                diferent = playerHands[playerIndex][i].getValue() != playerHands[playerIndex][j].getValue();
                if (diferent && playerHands[playerIndex][i].getSuitValue() == playerHands[playerIndex][j].getSuitValue()) {
                    counter++;
                }
            }
            if (counter == 4) {
                handLevel[playerIndex] = 5;
                return;
            }
        }
        for (int i = 0; i < 3; i++) {
            counter = 1;
            for (int j = i; j < 6; j++) {
                int current = playerHands[playerIndex][j].getValue();
                int next = playerHands[playerIndex][j + 1].getValue();
                if (counter == 5) {
                    handLevel[playerIndex] = 6;
                    return;
                } else if (current == next) {
                    continue;
                } else if (current == next + 1) {
                    counter++;
                } else {
                    break;
                }
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
    bool findStraightFlush(int playerIndex) {
        int suit, value, counter, lastValue, currentSuit, currentValue;
        for (int i = 0; i <= 2; i++) {
            suit = playerHands[playerIndex][i].getSuitValue();
            value = playerHands[playerIndex][i].getValue();
            counter = 1;
            lastValue = value;
            for (int j = i + 1; j < 7; j++) {
                currentSuit = playerHands[playerIndex][j].getSuitValue();
                currentValue = playerHands[playerIndex][j].getValue();
                if (currentSuit != suit)
                    continue;
                if (currentValue == lastValue)
                    continue;
                if (currentValue == lastValue - 1) {
                    counter++;
                    lastValue = currentValue;
                    if (counter == 5)
                        return true;
                } else {
                    break;
                }
            }
        }
        return false;
    }
    bool findADifferentPair(int playerIndex, int index) {
        bool pair, diferent;
        for (int j = 0; j < 5; j++) {
            pair = playerHands[playerIndex][j].getValue() == playerHands[playerIndex][j+1].getValue();
            diferent = playerHands[playerIndex][j].getValue() != playerHands[playerIndex][index].getValue();
            if (diferent && pair) {
                return true;
            }
        }
        return false;
    }
    void sorterCardsHighestToLowest(int playerIndex) {
        for (int i = 0; i < 6; ++i) {
            swapCards(playerIndex, i);
        }
    }
    void swapCards(int playerIndex, int index) {
        for (int j = 0; j < 7 - index - 1; ++j) {
            if (playerHands[playerIndex][j].getValue() < playerHands[playerIndex][j + 1].getValue()) {
                Cards temp = playerHands[playerIndex][j];
                playerHands[playerIndex][j] = playerHands[playerIndex][j + 1];
                playerHands[playerIndex][j + 1] = temp;
            }
        }
        
    }
    void burbelSorterSuit(int playerIndex) {
        for (int j = 0; j < 7 - 1; j++) {
            swapArrayBySuit(playerIndex, j);
        }
    }
    void swapArrayBySuit(int player, int index) {
        for (int j = 0; j < 7 - index - 1; j++) {
            if (playerHands[player][j].getSuitValue() > playerHands[player][j + 1].getSuitValue()) {
                Cards swap = playerHands[player][j];
                playerHands[player][j] = playerHands[player][j + 1];
                playerHands[player][j + 1] = swap;
            }
        }
    }
    void SortPlayerCards(int playerIndex) {
        if (playersCards[playerIndex][0].getValue() < playersCards[playerIndex][1].getValue()) {
            Cards swap = playersCards[playerIndex][0];
            playersCards[playerIndex][0] = playersCards[playerIndex][1];
            playersCards[playerIndex][1] = swap;
        }
    }
    bool checkIfAnyoneIsStillPlaying() {
        for (int i = 0; i < currentPlayers; i++) {
            if (playersPlaying[i]) {
                return true;
            }
        }
        return false;
    }
    void showTheWinner() {
        if (checkIfAnyoneIsStillPlaying()) {
            findWiner();
            std::cout << "Player " << winner + 1 << " is the winner with a hand of: ";
            showWinnerHand();
        } else {
            std::cout << "All the players are out, no one wins.";
        }
    }
    void choosePlayerIndex(std::string pot) {
        while (true) {
            std::cin.clear();
            std::cout << pot << "\n\n";
            std::cout << "Want to see a player hand? (1 to " << currentPlayers << ", 0 to continue): ";
            std::cin >> choice;
            while (std::cin.fail() || currentPlayers < choice || choice < 0) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input. Please enter a valid index (1 to " << currentPlayers << ", 0 to continue): ";
                std::cin >> choice;
            }
            if (choice == 0) {
                return;
            } else {
                system("cls");
                std::string move;
                std::cout << std::endl << pot << std::endl;
                std::cout << "\nPlayer " << choice << " cards:  ";
                showPlayerCards(choice - 1);
                std::cout << "\nEnter 'F' to FOLD or anything to get back: ";
                std::cin >> move;
                system("cls");
                if (move == "F" || move == "f") {
                    foldAPlayer(choice - 1);
                }
            }
        }
    }
    void showWinnerHand() {
        switch (bestHand) {
            case 1:
                std::cout << "Royal Flush";
                break;
            case 2:
                std::cout << "Straight Flush";
                break;
            case 3:
                std::cout << "Four of a Kind";
                break;
            case 4:
                std::cout << "Full House";
                break;
            case 5:
                std::cout << "Flush";
                break;
            case 6:
                std::cout << "Straight";
                break;
            case 7:
                std::cout << "Three of a Kind";
                break;
            case 8:
                std::cout << "Two Pairs";
                break;
            case 9:
                std::cout << "Pair";
                break;
            case 10:
                std::cout << "High Card";
                break;
            default:
                std::cout << "Unknown";
                break;
        }
    }
    void displayBoard() {
        std::cout << "  Flop: ";
        for (int i = 0; i < 3; i++) {
            flop[i].display();
            std::cout << " ";
        }
        std::cout << "\n  Turn: ";
        turn.display();
        std::cout << "\n  River: ";
        river.display();
        std::cout << "\n  Pot: ";
        for (int i = 0; i < 5; i++) {
            pot[i].display();
            std::cout << " ";
        }
        std::cout << std::endl;
    }

};

class PokerGame : PokerBoards {
private:
    int betPot;
    int currentBet;
    int chipsPerPlayer[10];
    int playersBet[10];
    bool isBetPay;

public:
    PokerGame() {
        betPot = 0;
        currentBet = 0;
        isBetPay = false;
        for (int i = 0; i < 10; i++) {
            chipsPerPlayer[i] = 0;
            playersBet[i] = 0;
        }
    }
    ~PokerGame() {}

    int getBetPot() {
        return betPot;
    }
    int getCurrentBet() {
        return currentBet;
    }
    bool getIsBetPay() {
        return isBetPay;
    }
    void setBetPot(int newPot) {
        betPot = newPot;
    }
    void setCurrentBet(int newCurrentBet) {
        currentBet = newCurrentBet;
    }
    void setisBetPay(bool newIsBetPay) {
        isBetPay = newIsBetPay;
    }

    void make() {
        
    }
    void choosePlayerIndex(std::string pot) {
        while (true) {
            std::cin.clear();
            std::cout << pot << "\n\n";
            std::cout << "The current bet is: " << currentBet << "\n";
            std::cout << "Want to see a player hand? (1 to " << currentPlayers << ", 0 to continue): ";
            std::cin >> choice;
            while (std::cin.fail() || currentPlayers < choice || choice < 0) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input. Please enter a valid index (1 to " << currentPlayers << ", 0 to continue): ";
                std::cin >> choice;
            }
            if (choice == 0 && isBetPay) {
                return;
            } else {
                system("cls");
                std::string move;
                std::cout << std::endl << pot << std::endl;
                std::cout << "\nPlayer " << choice << " cards:  ";
                showPlayerCards(choice - 1);
                std::cout << "\nEnter 'F' to FOLD or anything to get back: ";
                std::cin >> move;
                system("cls");
                if (move == "F" || move == "f") {
                    foldAPlayer(choice - 1);
                }
            }
        }
    }

};

int main() {
    srand(time(NULL));
    std::cout << "Welcome to the Poker Game!" << std::endl;
    std::cout << "Press ENTER to start." << std::endl;
    std::cin.get();
    system("cls");
    int players = 0;
    char option = ' ';
    PokerGame gameControl;
    while (players < 2 || players > 10) {
        std::cout << "Enter the number of players (2-10, 0 to exit, 1 to see Hand Ranking): ";
        std::cin >> players;
        if (players == 0) {
            std::cout << "Exiting the game." << std::endl;
            return 0;
        } else if (players == 1) {
            system("cls");
            std::cout << "------------------------ Poker Hand Rankings ------------------------\n";
            std::cout << "     1. Royal Flush\n";
            std::cout << "     2. Straight Flush\n";
            std::cout << "     3. Four of a Kind\n";
            std::cout << "     4. Full House\n";
            std::cout << "     5. Flush\n";
            std::cout << "     6. Straight\n";
            std::cout << "     7. Three of a Kind\n";
            std::cout << "     8. Two Pair\n";
            std::cout << "     9. Pair\n";
            std::cout << "    10. High Card\n";
            std::cout << "    11. If two players have the same hand, they win by high card.\n";
            std::cout << "---------------------------------------------------------------------\n\n";
        } else if (std::cin.fail() || players < 2 || players > 10) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number between 2 and 10 (0 to exit)." << std::endl;
        }
    }
    system("cls");
    std::cout << "Starting the game with " << players << " players.\n" << std::endl;
    while (true) {
        CardDecks deck;
        PokerBoards board(players);
        board.dealCards(deck);
        board.choosePlayerIndex(board.getFlop());
        system("cls");
        std::cin.clear();
        std::cout << std::endl;
        board.choosePlayerIndex(board.getTurn());
        system("cls");
        std::cout << std::endl;
        board.choosePlayerIndex(board.getRiver());
        system("cls");
        board.displayBoard();
        std::cout << std::endl;
        for (int i = 0; i < players; i++) {
            std::cout << "\nJugador numero " << i + 1 << ": ";
            board.showPlayerCards(i);
            std::cout << std::endl;
        }
        std::cout << std::endl;
        board.showTheWinner();
        std::cout << "\nWant to try again? Enter 'Y' to play again: \n";
        std::cin >> option;
        if (!(option == 'y' || option == 'Y')) {
            std::cout << "Thanks for playing." << std::endl;
            return 0;
        }
        system("cls");
    }
}