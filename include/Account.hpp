#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <string>
#include <vector>
#include <memory>
#include "Transaction.hpp"

namespace ATMSystem
{
    class Bank; // Forward declaration

    class Account
    {
    private:
        std::shared_ptr<Bank> bank; // Changed from string to shared_ptr
        std::string userName;
        std::string accountNumber; // 12-digit
        double balance;
        std::vector<Transaction> transactionHistory;

    public:
        Account(std::shared_ptr<Bank> bank, const std::string &user, const std::string &accNum);
        bool deposit(double amount);
        bool withdraw(double amount);
        bool transfer(const std::string &toAccount, double amount);
        double getBalance() const;
        std::vector<Transaction> getTransactionHistory() const;
        std::shared_ptr<Bank> getBank() const { return bank; } // Added this getter
    };
}

#endif