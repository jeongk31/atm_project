#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <map>

namespace ATMSystem
{
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
        static const int DEPOSIT_PRIMARY = 1000;
        static const int DEPOSIT_NON_PRIMARY = 2000;
        static const int WITHDRAWAL_PRIMARY = 1000;
        static const int WITHDRAWAL_NON_PRIMARY = 2000;
        static const int TRANSFER_PRIMARY = 2000;
        static const int TRANSFER_MIXED = 3000;
        static const int TRANSFER_NON_PRIMARY = 4000;
        static const int TRANSFER_CASH = 1000;
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