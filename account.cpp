#include "account.h"
#include <iostream>

long Account::nextAccountNumber = 10000;

Account::Account() : accountNumber(0), name(""), balance(0.0)
{
}

Account::Account(std::string name, double balance) : name(name), balance(balance)
{
    accountNumber = nextAccountNumber++;
}

Account::Account(long accountNumber, std::string name, double balance)
    : accountNumber(accountNumber), name(name), balance(balance)
{
    if (accountNumber >= nextAccountNumber)
    {
        nextAccountNumber = accountNumber + 1;
    }
}

long Account::getAccountNumber() const
{
    return accountNumber;
}

std::string Account::getName() const
{
    return name;
}

double Account::getBalance() const
{
    return balance;
}

bool Account::deposit(double amount)
{
    if (amount <= 0)
    {
        std::cout << "Error: Deposit amount must be positive.\n";
        return false;
    }

    balance += amount;
    return true;
}

bool Account::withdraw(double amount)
{
    if (amount <= 0)
    {
        std::cout << "Error: Withdrawal amount must be positive.\n";
        return false;
    }

    if (amount > balance)
    {
        std::cout << "Error: Insufficient funds.\n";
        return false;
    }

    balance -= amount;
    return true;
}

std::ostream &operator<<(std::ostream &os, const Account &account)
{
    os << account.accountNumber << " "
       << account.name << " "
       << account.balance;
    return os;
}