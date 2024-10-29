#include <iostream>
#include <vector>
#include <string>

class Transaction {
public:
    std::string type;
    double amount;
    std::string timestamp;

    Transaction(const std::string& t, double a, const std::string& ts)
        : type(t), amount(a), timestamp(ts) {}
};

class Account {
private:
    std::string accountNumber;
    std::string password;
    double balance;
    std::vector<Transaction> transactions;

public:
    Account(const std::string& accNum, const std::string& pwd) 
        : accountNumber(accNum), password(pwd), balance(0.0) {}

    bool verifyPassword(const std::string& pwd) const {
        return password == pwd;
    }

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount, "Timestamp"); // Placeholder for timestamp
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            std::cout << "Insufficient funds." << std::endl;
            return false;
        }
        balance -= amount;
        transactions.emplace_back("Withdrawal", amount, "Timestamp"); // Placeholder for timestamp
        return true;
    }

    void transfer(Account& other, double amount) {
        if (withdraw(amount)) {
            other.deposit(amount);
            transactions.emplace_back("Transfer", amount, "Timestamp"); // Placeholder for timestamp
        }
    }

    void printTransactions(const std::string& pwd) const {
        if (!verifyPassword(pwd)) {
            std::cout << "Invalid password. Access denied." << std::endl;
            return;
        }

        std::cout << "Transactions for account " << accountNumber << ":\n";
        for (const auto& txn : transactions) {
            std::cout << txn.timestamp << ": " << txn.type << " of $" << txn.amount << std::endl;
        }
        std::cout << "Remaining balance: $" << balance << std::endl;
    }

    double getBalance() const {
        return balance;
    }

    const std::string& getAccountNumber() const {
        return accountNumber;
    }
};

class Bank {
private:
    std::vector<Account> accounts;

public:
    void createAccount(const std::string& accNum, const std::string& pwd) {
        accounts.emplace_back(accNum, pwd);
        std::cout << "Account " << accNum << " created successfully." << std::endl;
    }

    Account* findAccount(const std::string& accNum) {
        for (auto& acc : accounts) {
            if (acc.getAccountNumber() == accNum) {
                return &acc;
            }
        }
        std::cout << "Account not found." << std::endl;
        return nullptr;
    }
};

int main() {
    Bank bank;
    int choice;
    std::string accNum;
    std::string toAccNum;
    std::string password;

    while (true) {
        std::cout << "1. Create Account\n2. Deposit\n3. Withdraw\n4. Transfer\n5. View Transactions\n6. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter account number: ";
                std::cin >> accNum;
                std::cout << "Set your password: ";
                std::cin >> password;
                bank.createAccount(accNum, password);
                break;

            case 2:
                std::cout << "Enter account number: ";
                std::cin >> accNum;
                {
                    Account* acc = bank.findAccount(accNum);
                    if (acc) {
                        double amount;
                        std::cout << "Enter amount to deposit: ";
                        std::cin >> amount;
                        acc->deposit(amount);
                    }
                }
                break;

            case 3:
                std::cout << "Enter account number: ";
                std::cin >> accNum;
                {
                    Account* acc = bank.findAccount(accNum);
                    if (acc) {
                        double amount;
                        std::cout << "Enter amount to withdraw: ";
                        std::cin >> amount;
                        acc->withdraw(amount);
                    }
                }
                break;

            case 4:
                std::cout << "Enter your account number: ";
                std::cin >> accNum;
                {
                    Account* acc = bank.findAccount(accNum);
                    if (acc) {
                        std::cout << "Enter recipient account number: ";
                        std::cin >> toAccNum;
                        Account* toAcc = bank.findAccount(toAccNum);
                        if (toAcc) {
                            double amount;
                            std::cout << "Enter amount to transfer: ";
                            std::cin >> amount;
                            acc->transfer(*toAcc, amount);
                        }
                    }
                }
                break;

            case 5:
                std::cout << "Enter account number: ";
                std::cin >> accNum;
                {
                    Account* acc = bank.findAccount(accNum);
                    if (acc) {
                        std::cout << "Enter your password for verification: ";
                        std::cin >> password; // Get password for verification
                        acc->printTransactions(password);
                    }
                }
                break;

            case 6:
                std::cout << "Exiting..." << std::endl;
                return 0;

            default:
                std::cout << "Invalid option. Please try again." << std::endl;
        }
    }
}