#ifndef SESSION_HPP
#define SESSION_HPP

#include <string>
#include <vector>
#include <memory>
#include "Transaction.hpp"
#include "Account.hpp"

namespace ATMSystem
{
    class Session
    {
    private:
        std::string cardNumber;
        std::shared_ptr<Account> account;
        std::vector<Transaction> sessionTransactions;
        int withdrawalCount;

    public:
        explicit Session(const std::string &card, std::shared_ptr<Account> acc);
        bool addTransaction(const Transaction &transaction);
        void endSession();
        bool canWithdraw() const;
        void printSessionSummary() const;
    };
}

#endif