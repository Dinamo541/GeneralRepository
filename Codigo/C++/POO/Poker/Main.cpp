#include "Cards.hpp"
#include "CardDecks.hpp"
#include "PokerBoards.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

int main() {
    std::cout << "Welcome to the Poker Game!" << std::endl;
    std::cout << "Press ENTER to start." << std::endl;
    std::cin.get();
    system("cls");
    int players = 0, result, bestHand, winner;
    char option = ' ';
    while (true){
        while (players < 2 || players > 10) {
            std::cout << "Enter the number of players (2-10, 0 to exit, 1 to see Hand Ranking): ";
            std::cin >> players;
            if (players == 0) {
                std::cout << "Exiting the game." << std::endl;
                return 0;
            } else if (players == 1) {
                system("cls");
                std::cout << "\n------------------------ Poker Hand Rankings ------------------------\n";
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
                std::cout << "---------------------------------------------------------------------\n";
            } else if (std::cin.fail() || players < 2 || players > 10) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input. Please enter a number between 2 and 10 (0 to exit, 1 to see Hand Ranking)." << std::endl;
            }
        }
        system("cls");
        std::cout << "Starting the game with " << players << " players.\n" << std::endl;
        CardDecks deck;
        PokerBoards board(players);
        board.dealCards(deck);
        std::cout << board.getFlop();
        std::cout << "\n\n" << board.getCurrentPlayers() << " are playing, ";
        board.choosePlayerIndex(board.getFlop());
        system("cls");
        std::cin.clear();
        std::cout << std::endl;
        std::cout << board.getTurn();
        std::cout << "\n\n" << board.getCurrentPlayers() << " are playing, ";
        board.choosePlayerIndex(board.getTurn());
        system("cls");
        std::cout << "\n  River: ";
        board.displayPot();
        std::cout << "\n\n" << board.getCurrentPlayers() << " are playing, ";
        board.choosePlayerIndex(board.getRiver());
        result = board.findWiner();
        system("cls");
        std::cout << "\n  Pot: ";
        board.displayPot();
        std::cout << std::endl;
        for (int i = 0; i < players; i++) {
            std::cout << "\nJugador numero " << i + 1 << ": ";
            board.showPlayerCards(i);
            std::cout << std::endl;
        }
        std::cout << std::endl;
        bestHand = result / 100;
        winner = result % 100;
        std::cout << "Player " << winner << " is the winner with a hand of: ";
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
                std::cout << "Two Pair";
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
        std::cout << "\nWant to try again? Enter 'Y' to play again: \n";
        std::cin >> option;
        if (!(option == 'y' || option == 'Y')) {
            std::cout << "Thanks for playing." << std::endl;
            return 0;
        }
        system("cls");
        players = 0;
    }
}