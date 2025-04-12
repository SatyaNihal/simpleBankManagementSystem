#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account
{
private:
    long accountNumber;
    std::string name;
    double balance;
    static long nextAccountNumber;

public:
    Account();
    Account(std::string name, double balance);
    Account(long accountNumber, std::string name, double balance);

    long getAccountNumber() const;
    std::string getName() const;
    double getBalance() const;

    bool deposit(double amount);
    bool withdraw(double amount);

    friend std::ostream &operator<<(std::ostream &os, const Account &account);
};

#endif // ACCOUNT_H