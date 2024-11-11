#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <string>
#include <vector>
#include "Transaction.hpp"

namespace ATMSystem
{
    class Account
    {
    private:
        std::string bankName;
        std::string userName;
        std::string accountNumber; // 12-digit
        double balance;
        std::vector<Transaction> transactionHistory;

    public:
        Account(const std::string &bank, const std::string &user, const std::string &accNum);
        bool deposit(double amount);
        bool withdraw(double amount);
        bool transfer(const std::string &toAccount, double amount);
        double getBalance() const;
        std::vector<Transaction> getTransactionHistory() const;
    };
}

#endif