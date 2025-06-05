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
    std::string incomesReasonAndAmount[SIZE]; //Formart "RE/AM" where RE is the reason and AM is the amount
    std::string incomesDates[SIZE]; //Date formart "DD/MM/YYYY"
    std::string expensesReasonAndAmount[SIZE];
    std::string expensesDate[SIZE];

public:
    MainAccount() {
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
    MainAccount(double newBalance, int newMoves, int newIncomes, int newLastIncome, int newExpenses, int newLastExpense) {
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
    ~MainAccount() {
        std::cout << "Destructor called for MainAccount" << std::endl;
    }

    void setBalance(double newBalance) {
        balance = newBalance;
    }
    void setMoves(int newMoves) {
        moves = newMoves;
    }
    void setIncomes(int newIncomes) {
        incomes = newIncomes;
    }
    void setLastIncome(int newLastIncome) {
        lastIncome = newLastIncome;
    }
    void setExpenses(int newExpenses) {
        expenses = newExpenses;
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
    int getIncomes() {
        return incomes;
    }
    int getLastIncome() {
        return lastIncome;
    }
    int getExpenses() {
        return expenses;
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
    void addIncome() {
        if (lastIncome >= SIZE) {
            char choice;
            std::cout << "Caution, the transaction limit is 100, if you make one more you will exceed it and the oldest transaction will be deleted." << std::endl;
            std::cout << "If you want to continue, please enter 'Y' or 'N': " << std::endl;
            std::cin >> choice;
            if (choice != 'Y' && choice != 'y') {
                std::cout << "Transaction cancelled." << std::endl;
                return;
            } else {
                deleteoldestIncome();
            }
        }
        double amount;
        std::string reason = "", date = "";
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
        std::cout << "Enter income Reason: " << std::endl;
        std::cin >> reason;
        while (reason.find("/") != std::string::npos) {
            std::cin.clear();
            std::cout << "The reason cannot be empty or with a '/' inside. Please enter a valid reason: " << std::endl;
            std::cin >> reason;
        }
        incomesReasonAndAmount[lastIncome] = reason + "/" + std::to_string(amount); //Formart "RE/AM"
        std::cout << "Enter income date DD/MM/YYYY: " << std::endl;
        std::cin >> date;
        while (date.length() != 10 || date[2] != '/' || date[5] != '/') {
            std::cout << "Invalid date format. Please enter in DD/MM/YYYY format: " << std::endl;
            std::cin >> date;
        }
        incomesDates[lastIncome] = date;
        balance += amount;
        moves++;
        incomes++;
        lastIncome++;
        std::cout << "Income added by: " << amount << "\n";
        verifyLastIncomeAndExpense();
    }
    void deleteoldestIncome() {
        for (int i = 0; i < lastIncome - 1; i++) {
            incomesReasonAndAmount[i] = incomesReasonAndAmount[i + 1];
            incomesDates[i] = incomesDates[i + 1];
        }
        lastIncome--;
        std::cout << "Oldest income deleted." << std::endl;
    }
    void findIncomeByIndex(int index) {
        if (index == 0) {
            return;
        }
        index--;
        std::string reasonAndAmount = "Reason: ";
        int length = incomesReasonAndAmount[index].length();
        for (int i = 0; i < length; i++) {
            if (incomesReasonAndAmount[index].at(i) == '/') {
                reasonAndAmount = ".\nAmount: ";
            } else {
                reasonAndAmount += incomesReasonAndAmount[index].at(i);
            }
        }
        std::cout << "Income at index " << index << ":\n"
            << reasonAndAmount << ".\nDate: "
            << incomesDates[index] << ".\n"
            << "Press ENTER to continue." << std::endl;
    }
    void findIncomeByDate() {
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
            }
        }
        if (counter > 1) {
            std::cout << "Multiple incomes found on " << date << ". Please use findIncomeByIndex to specify." << std::endl;
            showAllIncomeByDate(date, reasonAndAmount);
            return;
        }
        if (found) {
            int length = incomesReasonAndAmount[index].length();
            for (int i = 0; i < length; i++) {
                if (incomesReasonAndAmount[index][i] == '/') {
                    reasonAndAmount = ", amount of ";
                } else {
                    reasonAndAmount += incomesReasonAndAmount[index][i];
                }
            }
            std::cout << "Income on " << date << ": Reason of " << reasonAndAmount << "." << std::endl;
        } else {
            std::cout << "No income found on " << date << "." << std::endl;
        }
    }

    void showAllIncomeByDate(std::string date, std::string reasonAndAmount) {
        std::string answer = "";
        std::cout << "You want to see all incomes on " << date << "." << std::endl;
        std::cin >> answer;
        if (answer != "y" && answer != "Y") {
            std::cout << "Operation cancelled." << std::endl;
            return;
        }
        for (int i = 0; i < lastIncome; i++) {
            if (incomesDates[i] == date) {
                reasonAndAmount = "";
                int length = incomesReasonAndAmount[i].length();
                for (int j = 0; j < length; j++) {
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

    void findIncomeByReason() {
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
            }
        }
        if (counter > 1) {
            std::cout << "Multiple incomes found with reason '" << reason << "'. Please use findIncomeByIndex to specify." << std::endl;
            showAllIncomeByReason(reason, amount, limitToStart);
            return;
        }
        if (found) {
            int length = incomesReasonAndAmount[index].length();
            for (int i = 0; i < length; i++) {
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

    void showAllIncomeByReason(std::string reason, std::string amount, int limitToStart) {
        std::string answer = "";
        std::cout << "You want to see all incomes with reason '" << reason << "'." << std::endl;
        std::cin >> answer;
        if (answer != "y" && answer != "Y") {
            std::cout << "Operation cancelled." << std::endl;
            return;
        }
        for (int i = 0; i < lastIncome; i++) {
            if (incomesReasonAndAmount[i].find(reason) != std::string::npos) {
                amount = "";
                limitToStart = 0;
                int length = incomesReasonAndAmount[i].length();
                for (int j = 0; j < length; j++) {
                    if (incomesReasonAndAmount[i][j] == '/') {
                        limitToStart = -2;
                        continue;
                    }
                    if (limitToStart == -2) {
                        amount += incomesReasonAndAmount[i][j];
                    }
                }
                std::cout << i << ". Income with reason '" << reason << "': " << amount << ", on date " << incomesDates[i] << "." << std::endl;
            }
        }
    }

    void addExpense() {
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
    void findExpenseByIndex() {
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
        int length = expensesReasonAndAmount[index].length();
        for (int i = 0; i < length; i++) {
            if (expensesReasonAndAmount[index][i] == '/') {
                reasonAndAmount = ", with an amount of ";
            } else {
                reasonAndAmount += expensesReasonAndAmount[index][i];
            }
        }
        std::cout << "Expense at index " << index << ": " << reasonAndAmount << " and on date " << expensesDate[index] << std::endl;
    }
    void findExpenseByDate() {
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
            }
        }
        if (counter > 1) {
            std::cout << "Multiple expenses found on " << date << ". Please use findExpenseByIndex to specify." << std::endl;
            showAllExpenseByDate(date, reasonAndAmount);
            return;
        }
        if (found) {
            int length = expensesReasonAndAmount[index].length();
            for (int i = 0; i < length; i++) {
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
    void showAllExpenseByDate(std::string date, std::string reasonAndAmount) {
        std::string answer = "";
        std::cout << "You want to see all expenses on " << date << "." << std::endl;
        std::cin >> answer;
        if (answer != "y" && answer != "Y") {
            std::cout << "Operation cancelled." << std::endl;
            return;
        }
        for (int i = 0; i < lastExpense; i++) {
            if (expensesDate[i] == date) {
                reasonAndAmount = "";
                int length = expensesReasonAndAmount[i].length();
                for (int j = 0; j < length; j++) {
                    if (expensesReasonAndAmount[i][j] == '/') {
                        reasonAndAmount = ", amount of ";
                    } else {
                        reasonAndAmount += expensesReasonAndAmount[i][j];
                    }
                }
                std::cout << i << ". Expense on " << date << ": " << reasonAndAmount << "." << std::endl;
            }
        }
    }
    void findExpenseByReason() {
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
            }
        }
        if (counter > 1) {
            std::cout << "Multiple expenses found with reason '" << reason << "'. Please use findExpenseByIndex to specify." << std::endl;
            showAllExpenseByReason(reason, amount, limitToStart);
            return;
        }
        if (found) {
            int length = expensesReasonAndAmount[index].length();
            for (int i = 0; i < length; i++) {
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
    void showAllExpenseByReason(std::string reason, std::string amount, int limitToStart) {
        std::string answer = "";
        std::cout << "You want to see all expenses with reason '" << reason << "'." << std::endl;
        std::cin >> answer;
        if (answer != "y" && answer != "Y") {
            std::cout << "Operation cancelled." << std::endl;
            return;
        }
        for (int i = 0; i < lastExpense; i++) {
            if (expensesReasonAndAmount[i].find(reason) != std::string::npos) {
                int length = expensesReasonAndAmount[i].length();
                for (int j = 0; j < length; j++) {
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

    std::string display() {
        std::stringstream ss;
        ss << "Balance: " << balance << "\n"
           << "Moves: " << moves << "\n"
           << "Incomes: " << incomes << "\n"
           << "Last Income: " << lastIncome << "\n"
           << "Expenses: " << expenses << "\n"
           << "Last Expense: " << lastExpense;
        return ss.str();
    }
};

class MenusAndCheckers {
private:
    bool working;
    int index = 0;
    std::string option = "";

public:
    MenusAndCheckers() {
        working = true;
    }
    ~MenusAndCheckers() {
    }

    void showMainMenu(int incomes, int expenses) {
        std::cout << "Welcome to the Main Account Menu!\n";
        std::cout << "1. Add Income(" << incomes << "/100)\n";
        std::cout << "2. Find Income by Index\n";
        std::cout << "3. Find Income by Date\n";
        std::cout << "4. Find Income by Reason\n";
        std::cout << "5. Add Expense(" << expenses << "/100)\n";
        std::cout << "6. Find Expense by Index\n";
        std::cout << "7. Find Expense by Date\n";
        std::cout << "8. Find Expense by Reason\n";
        std::cout << "9. Display Account Status\n";
        std::cout << "0. Exit\n";
    }
    int verifyOption(std::string allowedOptions) {
        while (true) {
            std::cout << "Please enter an option (0-9): ";
            std::cin >> option;
            working = option.find(allowedOptions) != std::string::npos;
            if (working || option.length() != 1) {
                std::cout << "Invalid option, try again.\n";
            } else {
                return std::stoi(option);
            }
        } 
    }
    int chooseIndex(int lastTransaction) {
        std::cout << "Enter the index of the transaction(1-" << lastTransaction <<"): ";
        std::cin >> index;
        while (std::cin.fail() || index < 0 || index > lastTransaction) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a valid index(1 - " << lastTransaction << "): ";
            std::cin >> index;
        }
        return index;
    }
    void clearScreen() {
        std::cout << "\033[2J\033[1;1H"; // ANSI escape code to clear the screen
    }

        

};

int main() {
    std::cout << "Welcome, press ENTER to start.\n";
    std::cin.get();
    std::string allowedOptions = "1234567890";
    std::cout << "This is the MainAccount class, which allows you to manage your finances.\n";
    std::cout << "You can add incomes and expenses, search by index, date, or reason, and view all transactions.\n";
    MainAccount accountOne;
    MenusAndCheckers menuAndCheckers;
    while (true) {
        menuAndCheckers.clearScreen();
        menuAndCheckers.showMainMenu(accountOne.getIncomes(), accountOne.getExpenses());
        switch (menuAndCheckers.verifyOption(allowedOptions)) {
            case 1:
            accountOne.addIncome();
            break;
            case 2:
            accountOne.findIncomeByIndex(menuAndCheckers.chooseIndex(accountOne.getLastIncome()));
            break;
            case 3:
            accountOne.findIncomeByDate();
            break;
            case 4:
            accountOne.findIncomeByReason();
            break;
            case 5:
            accountOne.addExpense();
            break;
            case 6:
            accountOne.findExpenseByIndex();
            break;
            case 7:
            accountOne.findExpenseByDate();
            break;
            case 8:
            accountOne.findExpenseByReason();
            break;
            case 9:
            std::cout << accountOne.display() << "\n";
            break;
            case 0:
            std::cout << "Exiting the program.\n";
            return 0;
            default:
            std::cout << "Invalid option, please try again.\n";
        }
    }
    std::cout << "Current account status:\n" << accountOne.display() << "\n";
    
    return 0;
}