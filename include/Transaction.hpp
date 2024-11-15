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
        double fee;
        std::chrono::system_clock::time_point timestamp;
        std::string details;

    public:
        Transaction(const std::string &id, const std::string &card,
                    TransactionType transType, double amt,
                    double transactionFee = 0, const std::string &transDetails = "");

        // Getters
        std::string getTransactionId() const { return transactionId; }
        std::string getCardNumber() const { return cardNumber; }
        TransactionType getType() const { return type; }
        double getAmount() const { return amount; }
        double getFee() const { return fee; }
        std::string getDetails() const { return details; }
        std::chrono::system_clock::time_point getTimestamp() const { return timestamp; }

        std::string getTypeString() const;
        std::string getFormattedTimestamp() const;
    };
}

#endif