#ifndef CARDS_HPP
#define CARDS_HPP

#include <iostream>
#include <string>

class Cards {
private:
    int id;
    int idConst;
public:
    Cards();
    Cards(int id);

    ~Cards();

    char getSuit();
    char getRank();
    int getValue();
    int getSuitValue();
    
    void display();
    std::string getCard();
};

#endif