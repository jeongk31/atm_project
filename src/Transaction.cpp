#include "Transaction.hpp"

namespace ATMSystem
{
    Transaction::Transaction(const std::string &id, const std::string &card,
                             TransactionType transType, double amt)
        : transactionId(id), cardNumber(card), type(transType), amount(amt),
          timestamp(std::chrono::system_clock::now()) {}

    std::string Transaction::getTransactionId() const { return transactionId; }
    TransactionType Transaction::getType() const { return type; }
    double Transaction::getAmount() const { return amount; }
}