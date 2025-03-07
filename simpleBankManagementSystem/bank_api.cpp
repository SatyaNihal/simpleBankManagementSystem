#include <sstream>
#include "account.h"
#include "bank.h"
#include "crow.h"                  // Include Crow - a C++ micro web framework
#include "crow/middlewares/cors.h" // make sure you have this include

// Main function to create a REST API
int main()
{
    // Initialize the bank
    Bank bank;
    bank.loadAccounts();

    // Create a crow application with CORS middleware
    crow::App<crow::CORSHandler> app;

    // Configure CORS
    auto &cors = app.get_middleware<crow::CORSHandler>();
    cors
        .global()
        .headers("Content-Type")
        .methods(
            crow::HTTPMethod::Post,
            crow::HTTPMethod::Get,
            crow::HTTPMethod::Put,
            crow::HTTPMethod::Delete)
        .origin("*");

    // Get all accounts
    CROW_ROUTE(app, "/api/accounts")
        .methods("GET"_method)([&bank]()
                               {
        std::vector<Account> accounts = bank.getAllAccounts();
        crow::json::wvalue response = crow::json::wvalue::list();
        
        for (size_t i = 0; i < accounts.size(); i++) {
            crow::json::wvalue account;
            account["accountNumber"] = accounts[i].getAccountNumber();
            account["name"] = accounts[i].getName();
            account["balance"] = accounts[i].getBalance();
            response[i] = std::move(account);
        }
        
        return response; });

    // Create a new account
    CROW_ROUTE(app, "/api/accounts")
        .methods("POST"_method)([&bank](const crow::request &req)
                                {
        auto json = crow::json::load(req.body);
        if (!json)
            return crow::response(400, "Invalid JSON");
        
        std::string name = json["name"].s();
        double balance = json["balance"].d();
        
        Account newAccount(name, balance);
        bank.addAccount(newAccount);
        bank.saveAccounts();
        
        crow::json::wvalue response;
        response["accountNumber"] = newAccount.getAccountNumber();
        response["name"] = newAccount.getName();
        response["balance"] = newAccount.getBalance();
        
        return crow::response(201, response); });

    // Get account by ID
    CROW_ROUTE(app, "/api/accounts/<int>")
        .methods("GET"_method)([&bank](int accountNumber)
                               {
        if (!bank.checkBalance(accountNumber)) {
            return crow::response(404, "Account not found");
        }
        
        Account account = bank.getAccount(accountNumber);
        crow::json::wvalue response;
        response["accountNumber"] = account.getAccountNumber();
        response["name"] = account.getName();
        response["balance"] = account.getBalance();
        
        return crow::response(200, response); });

    // Deposit
    CROW_ROUTE(app, "/api/accounts/<int>/deposit")
        .methods("POST"_method)([&bank](const crow::request &req, int accountNumber)
                                {
        auto json = crow::json::load(req.body);
        if (!json)
            return crow::response(400, "Invalid JSON");
        
        double amount = json["amount"].d();
        
        if (bank.deposit(accountNumber, amount)) {
            bank.saveAccounts();
            Account account = bank.getAccount(accountNumber);
            
            crow::json::wvalue response;
            response["accountNumber"] = account.getAccountNumber();
            response["name"] = account.getName();
            response["balance"] = account.getBalance();
            response["message"] = "Deposit successful";
            
            return crow::response(200, response);
        } else {
            return crow::response(400, "Deposit failed");
        } });

    // Withdraw
    CROW_ROUTE(app, "/api/accounts/<int>/withdraw")
        .methods("POST"_method)([&bank](const crow::request &req, int accountNumber)
                                {
        auto json = crow::json::load(req.body);
        if (!json)
            return crow::response(400, "Invalid JSON");
        
        double amount = json["amount"].d();
        
        if (bank.withdraw(accountNumber, amount)) {
            bank.saveAccounts();
            Account account = bank.getAccount(accountNumber);
            
            crow::json::wvalue response;
            response["accountNumber"] = account.getAccountNumber();
            response["name"] = account.getName();
            response["balance"] = account.getBalance();
            response["message"] = "Withdrawal successful";
            
            return crow::response(200, response);
        } else {
            return crow::response(400, "Withdrawal failed");
        } });

    // Start the server
    app.port(3001).multithreaded().run();

    return 0;
}