#ifndef SESSION_HPP
#define SESSION_HPP

#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <atomic>
#include "Transaction.hpp"
#include "Constants.hpp"

namespace ATMSystem
{
    class Account;
    class ATM;

    class Session
    {
    private:
        static std::atomic<uint64_t> nextTransactionId;
        std::string sessionId;
        std::string cardNumber;
        std::shared_ptr<Account> account;
        std::vector<Transaction> transactions;
        std::chrono::system_clock::time_point startTime;
        bool isActive;
        int withdrawalCount;
        int checkDepositCount;
        std::weak_ptr<ATM> atm;

        struct SessionStatus
        {
            bool insufficientFunds;
            bool insufficientCash;
            bool cardError;
            bool systemError;
            std::string lastError;

            SessionStatus() : insufficientFunds(false), insufficientCash(false),
                              cardError(false), systemError(false) {}
        } status;

        std::string generateTransactionId();

    public:
        Session(const std::string &card, std::shared_ptr<Account> acc, std::shared_ptr<ATM> atmPtr);
        virtual ~Session() = default;

        // Transaction management
        std::string addTransaction(TransactionType type, double amount,
                                   double fee = 0, const std::string &details = "");

        // Session control
        void endSession(const std::string &reason = "");
        void endSessionWithError(const std::string &error);

        // Getters
        bool isSessionActive() const { return isActive; }
        bool canWithdraw() const { return withdrawalCount < MAX_WITHDRAWALS_PER_SESSION; }
        void incrementWithdrawalCount() { withdrawalCount++; }
        const std::vector<Transaction> &getTransactions() const { return transactions; }
        std::string getSessionId() const { return sessionId; }
        std::chrono::system_clock::time_point getStartTime() const { return startTime; }

        // Check deposit management
        bool canDepositCheck() const { return checkDepositCount < MAX_CHECK_INSERT; }
        void incrementCheckDeposit() { checkDepositCount++; }
    };
}

#endif