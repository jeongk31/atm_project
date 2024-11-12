// src/Account.cpp
#include "Account.hpp"

namespace ATMSystem
{

    Account::Account(std::shared_ptr<Bank> b, const std::string &user, const std::string &accNum)
        : bank(b), userName(user), accountNumber(accNum), balance(0)
    {
    }

    bool Account::deposit(double amount)
    {
        balance += amount;
        return true;
    }

    bool Account::withdraw(double amount)
    {
        if (amount > balance)
        {
            return false;
        }
        balance -= amount;
        return true;
    }

    bool Account::transfer(const std::string &toAccount, double amount)
    {
        if (amount > balance)
        {
            return false;
        }
        balance -= amount;
        return true;
    }

    double Account::getBalance() const
    {
        return balance;
    }

    std::vector<Transaction> Account::getTransactionHistory() const
    {
        return transactionHistory;
    }

} // namespace ATMSystem