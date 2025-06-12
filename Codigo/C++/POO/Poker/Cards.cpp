#include "Cards.hpp"
#include <iostream>
#include <string>

Cards::Cards() : id(0) {}
Cards::Cards(int id) : id(id) {}

Cards::~Cards() {}

char Cards::getSuit() {
    char suits[4] = {'d', 'c', 's', 'h'};
    return suits[id / 13];
}
char Cards::getRank() {
    char ranks[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    return ranks[id % 13];
}
int Cards::getValue() {
    return id % 13;
}
int Cards::getSuitValue() {
    return id / 13;
}
void Cards::display() {
    std::cout << getRank() << getSuit();
}
std::string Cards::getCard() {
    std::string suits[4] = {"d", "c", "s", "h"};
    std::string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"}; 
    return ranks[id % 13] + suits[id / 13];
}