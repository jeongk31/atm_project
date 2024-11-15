#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <map>

namespace ATMSystem
{
    const std::string ADMIN_CARD = "999999999999";
    enum class BankType
    {
        SINGLE_BANK,
        MULTI_BANK
    };

    enum class LanguageSupport
    {
        UNILINGUAL,
        BILINGUAL
    };

    enum class TransactionType
    {
        DEPOSIT,
        WITHDRAWAL,
        TRANSFER_CASH,
        TRANSFER_ACCOUNT
    };

    struct TransactionFees
    {
        // Deposit fees
        static const int DEPOSIT_PRIMARY = 1000;     // Primary bank deposit
        static const int DEPOSIT_NON_PRIMARY = 2000; // Non-primary bank deposit

        // Withdrawal fees
        static const int WITHDRAWAL_PRIMARY = 1000;     // Primary bank withdrawal
        static const int WITHDRAWAL_NON_PRIMARY = 2000; // Non-primary bank withdrawal

        // Account transfer fees
        static const int TRANSFER_PRIMARY = 2000;     // Between primary bank accounts
        static const int TRANSFER_MIXED = 3000;       // Between primary and non-primary
        static const int TRANSFER_NON_PRIMARY = 4000; // Between non-primary banks

        // Cash transfer fee
        static const int TRANSFER_CASH = 1000; // Cash transfer to any bank
    };

    const std::map<int, int> VALID_DENOMINATIONS = {
        {1000, 0},
        {5000, 0},
        {10000, 0},
        {50000, 0}};

    const int MIN_CHECK_AMOUNT = 100000;
    const int MAX_CASH_INSERT = 50;
    const int MAX_CHECK_INSERT = 50;
    const int MAX_WITHDRAWAL_PER_TRANSACTION = 500000;
    const int MAX_WITHDRAWALS_PER_SESSION = 3;
}

#endif