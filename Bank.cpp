#include <iostream>
#include <string>
#include <stdexcept>

class NegativeDepositException : public std::exception {
public:
    const char* what() const throw() {
        return "Deposit amount cannot be negative.";
    }
};

class InsufficientFundsException : public std::exception {
public:
    const char* what() const throw() {
        return "Insufficient funds for withdrawal.";
    }
};

class BankAccount {
private:
    int accountNumber;
    std::string accountHolderName;
    double balance;

public:
    BankAccount(int accNum, std::string accHolderName, double initialBalance)
        : accountNumber(accNum), accountHolderName(accHolderName), balance(initialBalance) {}

    void deposit(double amount) {
        if (amount < 0) {
            throw NegativeDepositException();
        }
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            throw InsufficientFundsException();
        }
        balance -= amount;
    }

    void displayBalance() const {
        std::cout << "Account Number: " << accountNumber << "\n"
                  << "Account Holder: " << accountHolderName << "\n"
                  << "Balance: $" << balance << "\n";
    }

    int getAccountNumber() const {
        return accountNumber;
    }
};

int main() {
    const int MAX_ACCOUNTS = 5;
    BankAccount* accounts[MAX_ACCOUNTS];
    int accountCount = 0;

    while (true) {
        std::cout << "1. Add a new account\n"
                  << "2. Deposit funds\n"
                  << "3. Withdraw funds\n"
                  << "4. Display balance\n"
                  << "5. Exit\n"
                  << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 5) break;

        int accNum;
        std::string accHolderName;
        double amount;

        switch (choice) {
            case 1:
                if (accountCount >= MAX_ACCOUNTS) {
                    std::cout << "Maximum number of accounts reached.\n";
                    break;
                }
                std::cout << "Enter account number: ";
                std::cin >> accNum;
                std::cout << "Enter account holder name: ";
                std::cin.ignore();
                std::getline(std::cin, accHolderName);
                std::cout << "Enter initial balance: ";
                std::cin >> amount;
                accounts[accountCount++] = new BankAccount(accNum, accHolderName, amount);
                break;
            case 2:
                std::cout << "Enter account number: ";
                std::cin >> accNum;
                std::cout << "Enter deposit amount: ";
                std::cin >> amount;
                try {
                    for (int i = 0; i < accountCount; ++i) {
                        if (accounts[i]->getAccountNumber() == accNum) {
                            accounts[i]->deposit(amount);
                            break;
                        }
                    }
                } catch (const NegativeDepositException& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            case 3:
                std::cout << "Enter account number: ";
                std::cin >> accNum;
                std::cout << "Enter withdrawal amount: ";
                std::cin >> amount;
                try {
                    for (int i = 0; i < accountCount; ++i) {
                        if (accounts[i]->getAccountNumber() == accNum) {
                            accounts[i]->withdraw(amount);
                            break;
                        }
                    }
                } catch (const InsufficientFundsException& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            case 4:
                std::cout << "Enter account number: ";
                std::cin >> accNum;
                for (int i = 0; i < accountCount; ++i) {
                    if (accounts[i]->getAccountNumber() == accNum) {
                        accounts[i]->displayBalance();
                        break;
                    }
                }
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    for (int i = 0; i < accountCount; ++i) {
        delete accounts[i];
    }

    return 0;
}
