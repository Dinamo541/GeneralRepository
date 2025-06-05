#include <iostream>
#include <string>
#include <sstream>

class MainAccount {
private:
    static const int SIZE = 100;
    double balance;
    int moves;
    int incomes;
    int lastIncome;
    int expenses;
    int lastExpense;
    std::string incomesReasonAndAmount[SIZE];
    std::string incomesDates[SIZE];
    std::string expensesReasonAndAmount[SIZE];
    std::string expensesDate[SIZE];

public:
    MainAccount();
    MainAccount(double newBalance, int newMoves, int newIncomes, int newLastIncome, int newExpenses, int newLastExpense);  
    ~MainAccount();

    void setBalance(double newBalance);
    void setMoves(int newMoves);
    void setIncomes(int newIncomes);
    void setLastIncome(int newLastIncome);
    void setExpenses(int newExpenses);
    void setLastExpense(int newLastExpense);
    
    int getSize() const;
    double getBalance();
    int getMoves();
    int getIncomes();
    int getLastIncome();
    int getExpenses();
    int getLastExpense();
    
    void addIncome();
    void findIncomeByIndex();
    void findIncomeByDate();
    void showAllIncomeByDate(std::string date, std::string reasonAndAmount);
    void findIncomeByReason();
    void showAllIncomeByReason(std::string reason, std::string amount, int limitToStart);

    void addExpense();
    void findExpenseByIndex();
    void findExpenseByDate();
    void showAllExpenseByDate(std::string date, std::string reasonAndAmount);
    void findExpenseByReason();
    void showAllExpenseByReason(std::string reason, std::string amount, int limitToStart);

    std::string display();
};