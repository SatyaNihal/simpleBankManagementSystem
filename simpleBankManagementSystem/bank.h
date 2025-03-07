#ifndef BANK_H
#define BANK_H

#include <vector>
#include "account.h"

class Bank
{
private:
    std::vector<Account> accounts;
    std::string ACCOUNTS_FILE; // Removed const and default initialization

public:
    // Constructor
    Bank();

    // File operations
    void loadAccounts();
    void saveAccounts();

    // Account operations
    void addAccount(const Account &account);
    bool deposit(long accountNumber, double amount);
    bool withdraw(long accountNumber, double amount);
    bool checkBalance(long accountNumber);
    void displayAllAccounts();

    // New methods for API
    std::vector<Account> getAllAccounts() const;
    Account getAccount(long accountNumber) const;

private:
    // Helper method to find account by number
    int findAccount(long accountNumber);
};

#endif // BANK_H