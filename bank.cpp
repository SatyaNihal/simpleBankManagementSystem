#include "bank.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

// Constructor
Bank::Bank()
{
    ACCOUNTS_FILE = "accounts.dat"; // Initialize in constructor instead
}

// Load accounts from file
void Bank::loadAccounts()
{
    ifstream infile(ACCOUNTS_FILE);

    if (!infile)
    {
        cout << "No existing accounts file found. Starting fresh.\n";
        return;
    }

    string line;
    while (getline(infile, line))
    {
        stringstream ss(line);
        long accountNumber;
        string name;
        double balance;

        ss >> accountNumber;

        // Get name (may contain spaces)
        ss >> ws; // Skip whitespace
        getline(ss, name, ' ');

        // The last token is the balance
        ss >> balance;

        Account account(accountNumber, name, balance);
        accounts.push_back(account);
    }

    infile.close();
    cout << accounts.size() << " accounts loaded successfully.\n";
}

// Save accounts to file
void Bank::saveAccounts()
{
    ofstream outfile(ACCOUNTS_FILE);

    if (!outfile)
    {
        cout << "Error: Unable to save accounts.\n";
        return;
    }

    for (const Account &account : accounts)
    {
        outfile << account << endl;
    }

    outfile.close();
    cout << accounts.size() << " accounts saved successfully.\n";
}

// Add a new account
void Bank::addAccount(const Account &account)
{
    accounts.push_back(account);
}

// Find account by account number, returns index or -1 if not found
int Bank::findAccount(long accountNumber)
{
    for (size_t i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getAccountNumber() == accountNumber)
        {
            return i;
        }
    }
    return -1;
}

// Deposit money into an account
bool Bank::deposit(long accountNumber, double amount)
{
    int index = findAccount(accountNumber);

    if (index == -1)
    {
        cout << "Error: Account not found.\n";
        return false;
    }

    return accounts[index].deposit(amount);
}

// Withdraw money from an account
bool Bank::withdraw(long accountNumber, double amount)
{
    int index = findAccount(accountNumber);

    if (index == -1)
    {
        cout << "Error: Account not found.\n";
        return false;
    }

    return accounts[index].withdraw(amount);
}

// Check account balance
bool Bank::checkBalance(long accountNumber)
{
    int index = findAccount(accountNumber);

    if (index == -1)
    {
        return false;
    }

    cout << "\n----- ACCOUNT DETAILS -----\n";
    cout << "Account Number: " << accounts[index].getAccountNumber() << endl;
    cout << "Account Holder: " << accounts[index].getName() << endl;
    cout << "Current Balance: $" << fixed << setprecision(2) << accounts[index].getBalance() << endl;

    return true;
}

// Display all accounts
void Bank::displayAllAccounts()
{
    if (accounts.empty())
    {
        cout << "No accounts found.\n";
        return;
    }

    cout << "\n----- ALL ACCOUNTS -----\n";
    cout << left << setw(15) << "Account No." << setw(20) << "Name" << "Balance" << endl;
    cout << string(45, '-') << endl;

    for (const Account &account : accounts)
    {
        cout << left << setw(15) << account.getAccountNumber()
             << setw(20) << account.getName()
             << "$" << fixed << setprecision(2) << account.getBalance() << endl;
    }
}

// New API methods
std::vector<Account> Bank::getAllAccounts() const
{
    return accounts;
}

Account Bank::getAccount(long accountNumber) const
{
    for (const Account &account : accounts)
    {
        if (account.getAccountNumber() == accountNumber)
        {
            return account;
        }
    }
    throw std::runtime_error("Account not found");
}