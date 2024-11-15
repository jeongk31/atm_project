#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <string>
#include <vector>
#include <memory>
#include "Transaction.hpp"

namespace ATMSystem
{
    class Bank;

    class Account
    {
    private:
        std::shared_ptr<Bank> bank;
        std::string userName;
        std::string accountNumber;
        std::string pin;
        double balance;
        std::vector<Transaction> transactionHistory;

    public:
        Account(std::shared_ptr<Bank> bank, const std::string &user, const std::string &accNum, const std::string &pin);

        std::string getPin() const { return pin; }
        bool deposit(double amount);
        bool withdraw(double amount);
        bool transfer(const std::string &toAccount, double amount);
        double getBalance() const;
        std::vector<Transaction> getTransactionHistory() const;
        std::shared_ptr<Bank> getBank() const { return bank; }
        std::string getUserName() const { return userName; }
        std::string getAccountNumber() const { return accountNumber; }
    };
}

#endif