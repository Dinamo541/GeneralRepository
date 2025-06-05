#include "Account.hpp"
#include <iostream>
#include <string>
#include <sstream>

MainAccount::MainAccount() {
    balance = 0.0;
    moves = 0;
    incomes = 0;
    expenses = 0;
    for (int i = 0; i < SIZE; i++) {
        incomesReasonAndAmount[i] = "";
        incomesDates[i] = "";
        expensesReasonAndAmount[i] = "";
        expensesDate[i] = "";
    }
}
MainAccount::MainAccount(double newBalance, int newMoves, int newIncomes, int newLastIncome, int newExpenses, int newLastExpense) {
    balance = newBalance;
    moves = newMoves;
    incomes = newIncomes;
    lastIncome = newLastIncome;
    expenses = newExpenses;
    lastExpense = newLastExpense;
    for (int i = 0; i < SIZE; i++) {
        incomesReasonAndAmount[i] = "";
        incomesDates[i] = "";
        expensesReasonAndAmount[i] = "";
        expensesDate[i] = "";
    }
}   
MainAccount::~MainAccount() {
    std::cout << "Destructor called for MainAccount" << std::endl;
}

void MainAccount::setBalance(double newBalance) {
    balance = newBalance;
}
void MainAccount::setMoves(int newMoves) {
    moves = newMoves;
}
void MainAccount::setIncomes(int newIncomes) {
    incomes = newIncomes;
}
void MainAccount::setLastIncome(int newLastIncome) {
    lastIncome = newLastIncome;
}
void MainAccount::setExpenses(int newExpenses) {
    expenses = newExpenses;
}
void MainAccount::setLastExpense(int newLastExpense) {
    lastExpense = newLastExpense;
}

int MainAccount::getSize() const {
    return SIZE;
}
double MainAccount::getBalance() {
    return balance;
}
int MainAccount::getMoves() {
    return moves;
}
int MainAccount::getIncomes() {
    return incomes;
}
int MainAccount::getLastIncome() {
    return lastIncome;
}
int MainAccount::getExpenses() {
    return expenses;
}
int MainAccount::getLastExpense() {
    return lastExpense;
}

void MainAccount::addIncome() {
    if (lastIncome >= SIZE) {
        char choice;
        std::cout << "Caution, the transaction limit is 100, if you make one more you will exceed it and the oldest transaction will be deleted." << std::endl;
        std::cout << "If you want to continue, please enter 'Y' or 'N': " << std::endl;
        std::cin >> choice;
        if (choice != 'Y' && choice != 'y') {
            std::cout << "Transaction cancelled." << std::endl;
            return;
        }
    }
    double amount;
    std::string reason;
    std::cout << "Enter income amount: " << std::endl;
    std::cin >> amount;
    while (std::cin.fail() || amount < 0) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        if (amount < 0) {
            std::cout << "Invalid amount. Income must be positive." << std::endl;
        } else {
            std::cout << "Invalid input. Please enter a valid number: " << std::endl;
        }
        std::cin >> amount;
    }
    std::cout << "Enter income reason: " << std::endl;
    std::cin >> reason;  //Formart "RR/HM"
    incomesReasonAndAmount[lastIncome] = reason + "/" + std::to_string(amount);
    std::cout << "Enter income date (DD/MM/YYYY): " << std::endl;
    std::cin >> incomesDates[lastIncome];
    balance += amount;
    moves++;
    incomes++;
    if (lastIncome > SIZE - 1) {
        lastIncome++;
    }
    std::cout << "Income added: " << amount << "\n";
}
void MainAccount::findIncomeByIndex() {
    int index = 0;
    std::string reasonAndAmount = "Reason for ";
    while (std::cin.fail() || index < 0) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        if (index > incomes && index < 0) {
            std::cout << "Invalid index. Please enter a number between 0 and " << incomes - 1 << "." << std::endl;
        } else if (incomesReasonAndAmount[index].empty()) {
            std::cout << "No income found at index " << index << "." << std::endl;
        } else {
            std::cout << "Invalid input. Please enter a valid number: " << std::endl;
        } 
        std::cin >> index;
    }
    for (int i = 0; i < incomesReasonAndAmount[index].length(); i++) {
        if (incomesReasonAndAmount[index - 1][i] == '/') {
            reasonAndAmount = ", with an amount of ";
        } else {
            reasonAndAmount += incomesReasonAndAmount[index - 1][i];
        }
    }
    std::cout << "Income at index " << index << ": " << reasonAndAmount << " and on date " << incomesDates[index] << std::endl;
}
void MainAccount::findIncomeByDate() {
    std::string date, reasonAndAmount = "Reason for ";
    std::cout << "Enter the date to search for income (DD/MM/YYYY): " << std::endl;
    std::cin >> date;
    bool found = false;
    int index = 0, counter = 0;
    for (int i = 0; i < lastIncome; i++) {
        if (incomesDates[i] == date) {
            index = i;
            found = true;
            counter++;
        } else if (counter > 1) {
            std::cout << "Multiple incomes found on " << date << ". Please use findIncomeByIndex to specify." << std::endl;
            showAllIncomeByDate(date, reasonAndAmount);
            return;
        }
    }
    if (found) {
        for (int i = 0; i < incomesReasonAndAmount[index].length(); i++) {
            if (incomesReasonAndAmount[index][i] == '/') {
                reasonAndAmount = ", amount of ";
            } else {
                reasonAndAmount += incomesReasonAndAmount[index][i];
            }
        }
        std::cout << "Income on " << date << ": Reason of " << reasonAndAmount << ".";
    } else {
        std::cout << "No income found on " << date << "." << std::endl;
    }
}
void MainAccount::showAllIncomeByDate(std::string date, std::string reasonAndAmount) {
    std::string answer = "";
    std::cout << "You want to see all incomes on " << date << "." << std::endl;
    std::cin >> answer;
    if (answer != "y" && answer != "Y") {
        std::cout << "Operation cancelled." << std::endl;
        return;
    }
    for (int i = 0; i < lastIncome; i++) {
        if (incomesDates[i] == date) {
            for (int j = 0; j < incomesReasonAndAmount[i].length(); j++) {
                if (incomesReasonAndAmount[i][j] == '/') {
                    reasonAndAmount = ", amount of ";
                } else {
                    reasonAndAmount += incomesReasonAndAmount[i][j];
                }
            }
            std::cout << i << ". Income on " << date << ": " << reasonAndAmount << "." << std::endl;
        }
    }
}
void MainAccount::findIncomeByReason() {
    std::string reason, date, amount = " ";
    int index = 0, counter = 0, limitToStart = 0;
    bool found = false;
    std::cout << "Enter the reason to search for income: " << std::endl;
    std::cin >> reason;
    for (int i = 0; i < lastIncome; i++) {
        if (incomesReasonAndAmount[i].find(reason) != std::string::npos) {
            index = i;
            found = true;
            counter++;
        } else if (counter > 1) {
            std::cout << "Multiple incomes found with reason '" << reason << "'. Please use findIncomeByIndex to specify." << std::endl;
            showAllIncomeByReason(reason, amount, limitToStart);
            return;
        }
    }
    if (found) {
        for (int i = 0; i < incomesReasonAndAmount[index].length(); i++) {
            if (incomesReasonAndAmount[index][i] == '/') {
                limitToStart = -2;
            } else if (limitToStart == -2) {
                amount += incomesReasonAndAmount[index][i];
            }
        }
        date = incomesDates[index];
        std::cout << "Income with reason '" << reason << "': " << amount << ", on date " << date << "." << std::endl;
    } else {
        std::cout << "No income found with reason '" << reason << "'." << std::endl;
    }
}
void MainAccount::showAllIncomeByReason(std::string reason, std::string amount, int limitToStart) {
    std::string answer = "";
    std::cout << "You want to see all incomes with reason '" << reason << "'." << std::endl;
    std::cin >> answer;
    if (answer != "y" && answer != "Y") {
        std::cout << "Operation cancelled." << std::endl;
        return;
    }
    for (int i = 0; i < lastIncome; i++) {
        if (incomesReasonAndAmount[i].find(reason) != std::string::npos) {
            for (int j = 0; j < incomesReasonAndAmount[i].length(); j++) {
                if (incomesReasonAndAmount[i][j] == '/') {
                    amount = "Amount of ";
                    limitToStart = -2;
                } else if (limitToStart == -2) {
                    amount += incomesReasonAndAmount[i][j];
                }
            }
            std::cout << i << ". Income with reason '" << reason << "': " << amount << ", on date " << incomesDates[i] << "." << std::endl;
        }
    }
}

void MainAccount::addExpense() {
    if (lastExpense >= SIZE) {
        char choice;
        std::cout << "Caution, the transaction limit is 100, if you make one more you will exceed it and the oldest transaction will be deleted." << std::endl;
        std::cout << "If you want to continue, please enter 'Y' or 'N': " << std::endl;
        std::cin >> choice;
        if (choice != 'Y' && choice != 'y') {
            std::cout << "Transaction cancelled." << std::endl;
            return;
        }
    }
    double amount;
    std::string reason;
    std::cout << "Enter expense amount: " << std::endl;
    std::cin >> amount;
    while (std::cin.fail() || amount < 0) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        if (amount < 0) {
            std::cout << "Invalid amount. Expense must be positive." << std::endl;
        } else {
            std::cout << "Invalid input. Please enter a valid number: " << std::endl;
        }
        std::cin >> amount;
    }
    std::cout << "Enter expense reason: " << std::endl;
    std::cin >> reason;  //Formart "RR/HM"
    expensesReasonAndAmount[lastExpense] = reason + "/" + std::to_string(amount);
    std::cout << "Enter expense date (DD/MM/YYYY): " << std::endl;
    std::cin >> expensesDate[lastExpense];
    balance -= amount;
    moves++;
    expenses++;
    if (lastExpense > SIZE - 1) {
        lastExpense++;
    }
    std::cout << "Expense added: " << amount << "\n";
}
void MainAccount::findExpenseByIndex() {
    int index = 0;
    std::string reasonAndAmount = "Reason for ";
    while (std::cin.fail() || index < 0) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        if (index > expenses && index < 0) {
            std::cout << "Invalid index. Please enter a number between 0 and " << expenses - 1 << "." << std::endl;
        } else if (expensesReasonAndAmount[index].empty()) {
            std::cout << "No expense found at index " << index << "." << std::endl;
        } else {
            std::cout << "Invalid input. Please enter a valid number: " << std::endl;
        } 
        std::cin >> index;
    }
    for (int i = 0; i < expensesReasonAndAmount[index].length(); i++) {
        if (expensesReasonAndAmount[index - 1][i] == '/') {
            reasonAndAmount = ", with an amount of ";
        } else {
            reasonAndAmount += expensesReasonAndAmount[index - 1][i];
        }
    }
    std::cout << "Expense at index " << index << ": " << reasonAndAmount << " and on date " << expensesDate[index] << std::endl;
}
void MainAccount::findExpenseByDate() {
    std::string date, reasonAndAmount = "Reason for ";
    std::cout << "Enter the date to search for expense (DD/MM/YYYY): " << std::endl;
    std::cin >> date;
    bool found = false;
    int index = 0, counter = 0;
    for (int i = 0; i < lastExpense; i++) {
        if (expensesDate[i] == date) {
            index = i;
            found = true;
            counter++;
        } else if (counter > 1) {
            std::cout << "Multiple expenses found on " << date << ". Please use findExpenseByIndex to specify." << std::endl;
            showAllExpenseByDate(date, reasonAndAmount);
            return;
        }
    }
    if (found) {
        for (int i = 0; i < expensesReasonAndAmount[index].length(); i++) {
            if (expensesReasonAndAmount[index][i] == '/') {
                reasonAndAmount = ", amount of ";
            } else {
                reasonAndAmount += expensesReasonAndAmount[index][i];
            }
        }
        std::cout << "Expense on " << date << ": Reason of " << reasonAndAmount << "." << std::endl;
    } else {
        std::cout << "No expense found on " << date << "." << std::endl;
    }
}
void MainAccount::showAllExpenseByDate(std::string date, std::string reasonAndAmount) {
    std::string answer = "";
    std::cout << "You want to see all expenses on " << date << "." << std::endl;
    std::cin >> answer;
    if (answer != "y" && answer != "Y") {
        std::cout << "Operation cancelled." << std::endl;
        return;
    }
    for (int i = 0; i < lastExpense; i++) {
        if (expensesDate[i] == date) {
            for (int i = 0; i < expensesReasonAndAmount[i].length(); i++) {
                if (expensesReasonAndAmount[i][i] == '/') {
                    reasonAndAmount = ", amount of ";
                } else {
                    reasonAndAmount += expensesReasonAndAmount[i][i];
                }
            }
            std::cout << i << " .Expense on " << date << ": " << reasonAndAmount << "." << std::endl;
        }
    }
}
void MainAccount::findExpenseByReason() {
    std::string reason, date, amount = " ";
    int index = 0, counter = 0, limitToStart = 0;
    bool found = false;
    std::cout << "Enter the reason to search for expense: " << std::endl;
    std::cin >> reason;
    for (int i = 0; i < lastExpense; i++) {
        if (expensesReasonAndAmount[i].find(reason) != std::string::npos) {
            index = i;
            found = true;
            counter++;
        } else if (counter > 1) {
            std::cout << "Multiple expenses found with reason '" << reason << "'. Please use findExpenseByIndex to specify." << std::endl;
            showAllExpenseByReason(reason, amount, limitToStart);
            return;
        }
    }
    if (found) {
        for (int i = 0; i < expensesReasonAndAmount[index].length(); i++) {
            if (expensesReasonAndAmount[index][i] == '/') {
                limitToStart = -2;
            } else if (limitToStart == -2) {
                amount += expensesReasonAndAmount[index][i];
            }
        }
        date = expensesDate[index];
        std::cout << "Expense with reason '" << reason << "': " << amount << ", on date " << date << "." << std::endl;
    } else {
        std::cout << "No expense found with reason '" << reason << "'." << std::endl;
    }
}
void MainAccount::showAllExpenseByReason(std::string reason, std::string amount, int limitToStart) {
    std::string answer = "";
    std::cout << "You want to see all expenses with reason '" << reason << "'." << std::endl;
    std::cin >> answer;
    if (answer != "y" && answer != "Y") {
        std::cout << "Operation cancelled." << std::endl;
        return;
    }
    for (int i = 0; i < lastExpense; i++) {
        if (expensesReasonAndAmount[i].find(reason) != std::string::npos) {
            for (int j = 0; j < expensesReasonAndAmount[i].length(); j++) {
                if (expensesReasonAndAmount[i][j] == '/') {
                    amount = "Amount of ";
                    limitToStart = -2;
                } else if (limitToStart == -2) {
                    amount += expensesReasonAndAmount[i][j];
                }
            }
            std::cout << i << " .Expense with reason '" << reason << "': " << amount << ", on date " << expensesDate[i] << "." << std::endl;
        }
    }
}

std::string MainAccount::display() {
    std::stringstream ss;
    ss << "Balance: " << balance << "\n"
    << "Moves: " << moves << "\n"
    << "Incomes: " << incomes << "\n"
    << "Last Income: " << lastIncome << "\n"
    << "Expenses: " << expenses << "\n"
    << "Last Expense: " << lastExpense;
    return ss.str();
}