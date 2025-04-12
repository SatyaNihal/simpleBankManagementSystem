#include <iostream>
#include <limits>
#include "account.h"
#include "bank.h"

using namespace std;

void displayMenu()
{
    cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
    cout << "1. Create New Account\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. Check Balance\n";
    cout << "5. Display All Accounts\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    Bank bank;
    int choice;
    long accountNumber;
    string name;
    double amount;

    bank.loadAccounts(); // Load existing accounts from file

    while (true)
    {
        displayMenu();
        cin >> choice;

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1: // Create account
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Initial Deposit: $";
            cin >> amount;

            if (amount < 0)
            {
                cout << "Error: Initial deposit cannot be negative.\n";
            }
            else
            {
                Account newAccount(name, amount);
                bank.addAccount(newAccount);
                cout << "Account created successfully. Account Number: " << newAccount.getAccountNumber() << endl;
            }
            break;

        case 2: // Deposit
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            cout << "Enter Deposit Amount: $";
            cin >> amount;

            if (bank.deposit(accountNumber, amount))
            {
                cout << "Deposit successful.\n";
            }
            else
            {
                cout << "Deposit failed.\n";
            }
            break;

        case 3: // Withdraw
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            cout << "Enter Withdrawal Amount: $";
            cin >> amount;

            if (bank.withdraw(accountNumber, amount))
            {
                cout << "Withdrawal successful.\n";
            }
            else
            {
                cout << "Withdrawal failed.\n";
            }
            break;

        case 4: // Check balance
            cout << "Enter Account Number: ";
            cin >> accountNumber;

            if (!bank.checkBalance(accountNumber))
            {
                cout << "Account not found.\n";
            }
            break;

        case 5: // Display all accounts
            bank.displayAllAccounts();
            break;

        case 6:                  // Exit
            bank.saveAccounts(); // Save accounts before exiting
            cout << "Thank you for using the Bank Management System!\n";
            return 0;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}