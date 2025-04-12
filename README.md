
# Banking System REST API

A C++ implementation of a banking system with both a terminal interface and a RESTful API. Manage accounts, perform transactions, and access banking functionality through an HTTP interface. Created by **Satya Nihal Kodukula** to make use of low-level programming knowledge learnt in **CISC 221, Computer Architecture** and **CISC 235, Data Structures.**

## Features

- **Account Management**: Create new accounts, check balances, deposit, and withdraw funds.
- **Data Persistence**: Store and retrieve account data using a text file.
- **REST API Interface**: Access banking functions via a modern web API with JSON responses.
- **Terminal Interface**: Use a command-line interface for direct system interaction.
- **CORS Support**: Enable secure integration with web applications.
- **React Frontend**: Interact with the API through a user-friendly interface built with React, HTML, and CSS.

## How It Works

1. **Initialization**:
   - The `Bank` class initializes a collection of `Account` objects.
   - Each account is assigned a unique account number, name, and balance.
   - Account data is loaded from a text file on startup.

2. **Account Operations**:
   - Create new accounts with a name and initial balance.
   - Deposit or withdraw funds with transaction validation to ensure valid operations.
   - Check account balances and retrieve account details.

3. **REST API**:
   - Built using the Crow C++ microframework.
   - Exposes endpoints for all banking operations, returning JSON responses.
   - Supports CORS for secure cross-origin requests.

4. **API Endpoints**:
   - `GET /api/accounts`: Retrieve a list of all accounts.
   - `POST /api/accounts`: Create a new account.
   - `GET /api/accounts/<id>`: Fetch details for a specific account.
   - `POST /api/accounts/<id>/deposit`: Deposit funds into an account.
   - `POST /api/accounts/<id>/withdraw`: Withdraw funds from an account.

5. **Frontend Interaction**:
   - A React-based interface communicates with the API endpoints.
   - Users can create accounts, deposit, withdraw, and check balances via a clean UI.
   - Built with HTML and CSS for a responsive experience.

6. **Data Persistence**:
   - Account data is saved to a text file after each operation.
   - Data is reloaded automatically when the system starts.

## Requirements

- A modern **C++ compiler** supporting C++11 or newer (e.g., `g++`).
- The **Crow** framework for building the REST API.
- A **text editor** or IDE for modifying code.
- **npm** to run the React frontend.

## Compilation

```bash
# Compile the terminal interface
g++ -o bank_cli main.cpp bank.cpp account.cpp -std=c++11

# Compile the REST API (requires Crow headers)
g++ -o bank_api bank_api.cpp bank.cpp account.cpp -std=c++11 -I./include
