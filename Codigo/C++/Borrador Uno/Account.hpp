#include <iostream>
#include <string>

class User {
private:
    std::string name = "";
    std::string email = "";
    std::string password = "";
public:
    User(std::string name, std::string email, std::string password) : name(name), email(email), password(password) {}

    // Getters and setters for the private members can be added here if needed
};

class Account {
private:
    std::string accountNumber = "";
    std::string accountHolderName = "";
    double balance = 0.0;
    double interestRate = 0.0;

public:
    Account() = default;
    Account(std::string accNum, std::string accHolder, double initialBalance, double rate);

    void setAccountNumber(std::string newAccountNumber) {
        accountNumber = newAccountNumber;
    }
    void setAccountHolderName(std::string accHolder) {
        accountHolderName = accHolder;
    }
    
    std::string getAccountNumber() {
    }

};