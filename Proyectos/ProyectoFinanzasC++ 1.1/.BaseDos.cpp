#include <iostream>
#include <string>


class Incomes {
private:
    int id;
    int amount;
    std::string date;
    std::string reason;

public:
    Incomes() {
        id = 0;
        amount = 0;
        date = "";
        reason = "";
    }
    Incomes(int newId) {
        id = newId;
        amount = 0;
        date = "";
        reason = "";
    }
    ~Incomes() {}

    void setamount(int newAmount) {
        amount = newAmount;
    }
    void setDate(std::string newDate) {
        date = newDate; //Date formart "DD/MM/YYYY"
    }
    void setReason(std::string newReason) {
        reason = newReason;
    }

    int getId() {
        return id;
    }
    int getAmount() {
        return amount;
    }
    std::string getDate() {
        return date;
    }
    std::string getReason() {
        return reason;
    }

};

class Expenses {
private:
    int id;
    int amount;
    std::string date;
    std::string reason;

public:
    Expenses() {
        id = 0;
        amount = 0;
        date = "";
        reason = "";
    }
    Expenses(int newId) {
        id = newId;
        amount = 0;
        date = "";
        reason = "";
    }
    ~Expenses() {}

    void setamount(int newAmount) {
        amount = newAmount;
    }
    void setDate(std::string newDate) {
        date = newDate; //Date formart "DD/MM/YYYY"
    }
    void setReason(std::string newReason) {
        reason = newReason;
    }

    int getId() {
        return id;
    }
    int getAmount() {
        return amount;
    }
    std::string getDate() {
        return date;
    }
    std::string getReason() {
        return reason;
    }

};


class MainAccount {
private:
    static const int SIZE = 100;
    double balance;
    int moves;
    int totalIncomes;
    int totalExpenses;
    int lastIncome;
    int lastExpense;
    Incomes incomes[SIZE];
    Expenses expenses[SIZE];

public:
    MainAccount() {
        balance = 0.0;
        moves = 0;
        totalIncomes = 0;
        totalExpenses = 0;
        lastIncome = 0;
        lastExpense = 0;
        for (int i = 0; i < SIZE; i++) {
            expenses[i] = Expenses(i);
            incomes[i] = Incomes(i);
        }
    }
    ~MainAccount() {
        std::cout << "Destructor called for MainAccount" << std::endl;
    }

    void setBalance(double newBalance) {
        balance = newBalance;
    }
    void setMoves(int newMoves) {
        moves = newMoves;
    }
    void setTotalIncomes(int newIncomes) {
        totalIncomes = newIncomes;
    }
    void setTotalExpenses(int newExpenses) {
        totalExpenses = newExpenses;
    }
    void setLastIncome(int newLastIncome) {
        lastIncome = newLastIncome;
    }
    void setLastExpense(int newLastExpense) {
        lastExpense = newLastExpense;
    }

    int getSize() const {
        return SIZE;
    }
    double getBalance() {
        return balance;
    }
    int getMoves() {
        return moves;
    }
    int getTotalIncomes() {
        return totalIncomes;
    }
    int getTotalExpenses() {
        return totalExpenses;
    }
    int getLastIncome() {
        return lastIncome;
    }
    int getLastExpense() {
        return lastExpense;
    }

    void verifyLastIncomeAndExpense() {
        if (lastIncome > SIZE) {
            lastIncome = SIZE - 1;
        }
        if (lastExpense > SIZE) {
            lastExpense = SIZE - 1;
        }
    }
    void addIncome() {}
    void deleteoldestIncome() {
        for (int i = 0; i < lastIncome - 1; i++) {
            incomes[i] = incomes[i + 1];
        }
        lastIncome--;
        std::cout << "Oldest income deleted!" << std::endl;
    }
    void findIncomeByIndex(int index) {
        if (index == 0) {
            return;
        }
        index--;
        int amount = incomes[index].getAmount(); 
        std::string date = incomes[index].getDate();
        std::string reason = incomes[index].getReason();
        
        std::cout << "Income at index " << index 
            << ":\nAmount: " << amount
            << ".\nDate: " << date 
            << ".\nReason: " << reason
            << "\nPress ENTER to continue." << std::endl;
    }



};