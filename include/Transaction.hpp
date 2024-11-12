#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include <chrono>
#include "Constants.hpp"

namespace ATMSystem
{
    class Transaction
    {
    private:
        std::string transactionId;
        std::string cardNumber;
        TransactionType type;
        double amount;
        std::chrono::system_clock::time_point timestamp;

    public:
        Transaction(const std::string &id, const std::string &card,
                    TransactionType transType, double amt);
        std::string getTransactionId() const;
        TransactionType getType() const;
        double getAmount() const;
    };
}

#endif