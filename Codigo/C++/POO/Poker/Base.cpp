#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Card {
private:
    int id;

public:
    Card() : id(0) {}
    Card(int id) : id(id) {}

    ~Card() {}

    char getSuit() {
        char suits[4] = {'d', 'c', 's', 'h'};
        return suits[id / 13];
    }
    char getRank() {
        char ranks[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
        return ranks[id % 13];
    }
    int getValue() {
        return id % 13;
    }
    void display() {
        std::cout << getRank() << getSuit();
    }
};

class CardDeck {
private:
    Card cardDeck[52];

public:
    CardDeck() {
        initialize();
        shuffle();
    }
    ~CardDeck() {}
    void initialize() {
        for (int i = 0; i < 52; i++) {
            cardDeck[i] = Card(i);
        }
    }
    void shuffle() {
        std::srand(std::time(0));

        for (int i = 51; i > 0; --i) {
            int j = std::rand() % (i + 1);
            Card temp = cardDeck[i];
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
    Card shareCard() {
        Card card = cardDeck[0];
        for (int i = 0; i < 51; i++) {
            cardDeck[i] = cardDeck[i + 1];
        }
        cardDeck[51] = Card();
        return card;
    }
};

class PokerBoard {
private:
    Card playerCards[10][2];
    Card bestHands[10][5];
    int currentPlayers;
    int choice;
    Card flop[3];
    Card turn;
    Card river;
    Card pot[5];

public:
    PokerBoard(int players) {
        currentPlayers = players;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 2; j++) {
                playerCards[i][j] = Card();
            }
            for (int j = 0; j < 5; j++) {
                bestHands[i][j] = Card();
            }
        }
    }
    ~PokerBoard() {}

    int getCurrentPlayers() {
        return currentPlayers;
    }

    void dealCards(CardDeck deck) {
        for (int i = 0; i < currentPlayers; i++) {
            playerCards[i][0] = deck.shareCard();
            playerCards[i][1] = deck.shareCard();
        }
        for (int i = 0; i < 3; i++) {
            flop[i] = deck.shareCard();
            pot[i] = flop[i];
        }
    }
    void dealTurn(CardDeck deck) {
        turn = deck.shareCard();
        pot[3] = turn;
    }
    void dealRiver(CardDeck deck) {
        river = deck.shareCard();
        pot[4] = river;
    }
    void displayPlayersCards() {
        for (int i = 0; i < currentPlayers; i++) {
            playerCards[i][0].display();
            playerCards[i][1].display();
        }
    }
    void showPlayerCards(int playerIndex) {
        if (playerIndex < 0 || playerIndex >= currentPlayers) {
            std::cout << "Invalid player index." << std::endl;
            return;
        }
        playerCards[playerIndex][0].display();
        std::cout << " ";
        playerCards[playerIndex][1].display();
    }
    void displayFlop() {
        std::cout << " ";
        for (int i = 0; i < 3; i++) {
            flop[i].display();
            std::cout << " ";
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
    void choosePlayerIndex() {
        while (true) {
            std::cout << "Want to see a player hand? (1 to " << getCurrentPlayers() << ", 0 to continue): ";
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
                std::cout << "Cards:  ";
                showPlayerCards(choice - 1);
                std::cout << "\n";
            }
        }
    }
    void findBestHand() {
        
        std::cout << "Finding best hand... (not implemented yet)" << std::endl;
    }

};



int main() {
    std::cout << "Welcome to the Poker Game!" << std::endl;
    std::cout << "Press ENTER to start." << std::endl;
    std::cin.get();
    int players = 0;
    while (players < 2 || players > 10) {
        std::cout << "Enter the number of players (2-10, 0 to exit): ";
        std::cin >> players;
        if (std::cin.fail() || players < 2 || players > 10) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number between 2 and 10 (0 to exit)." << std::endl;
        } else if (players == 0) {
            std::cout << "Exiting the game." << std::endl;
            return 0;
        }
    }
    std::cout << "Starting the game with " << players << " players." << std::endl;
    CardDeck deck;
    PokerBoard board(players);
    deck.displayDeck();
    board.dealCards(deck);
    std::cout << "Flop: ";
    board.displayFlop();
    std::cout << "\n\n" << board.getCurrentPlayers() << " are playing.\nENTER to continue.";
    std::cin.get();
    board.choosePlayerIndex();
    board.dealTurn(deck);
    std::cout << std::endl;
    std::cout << "Turn: ";
    board.displayFlop();
    board.displayTurn();
    std::cout << "\n\nPress ENTER to continue." << std::endl;
    std::cin.get();
    board.choosePlayerIndex();
    board.dealRiver(deck);
    std::cout << std::endl;
    std::cout << "River: ";
    board.displayPot();
    board.displayRiver();
    std::cout << "\n\nPress ENTER to continue." << std::endl;
    std::cin.get();

    return 0;
}
