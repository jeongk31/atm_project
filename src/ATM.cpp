// src/ATM.cpp
#include "ATM.hpp"

namespace ATMSystem
{

    ATM::ATM(const std::string &serial, BankType type, LanguageSupport lang, std::shared_ptr<Bank> primary)
        : serialNumber(serial), bankType(type), languageSupport(lang), primaryBank(primary)
    {
    }

    bool ATM::insertCard(const std::string &cardNumber)
    {
        return true; // Placeholder implementation
    }

    bool ATM::validatePin(const std::string &pin)
    {
        return true; // Placeholder implementation
    }

    bool ATM::deposit(double amount)
    {
        return true; // Placeholder implementation
    }

    bool ATM::withdraw(double amount)
    {
        return true; // Placeholder implementation
    }

    bool ATM::transfer(const std::string &toAccount, double amount)
    {
        return true; // Placeholder implementation
    }

    void ATM::printTransactionHistory() const
    {
        // Placeholder implementation
    }

    void ATM::endSession()
    {
        // Placeholder implementation
    }

    bool ATM::addCash(const std::map<int, int> &cash)
    {
        for (const auto &[denomination, count] : cash)
        {
            cashInventory[denomination] += count;
        }
        return true;
    }

    bool ATM::hasSufficientCash(int amount) const
    {
        int totalAvailable = 0;
        for (const auto &[denomination, count] : cashInventory)
        {
            totalAvailable += denomination * count;
        }
        return totalAvailable >= amount;
    }

    std::map<int, int> ATM::getCashBreakdown(int amount) const
    {
        std::map<int, int> breakdown;
        int remaining = amount;

        // Try to use largest denominations first
        std::vector<int> denoms = {50000, 10000, 5000, 1000};
        for (int denom : denoms)
        {
            if (remaining >= denom)
            {
                int needed = remaining / denom;
                int available = cashInventory.at(denom);
                int use = std::min(needed, available);
                if (use > 0)
                {
                    breakdown[denom] = use;
                    remaining -= denom * use;
                }
            }
        }

        return breakdown;
    }

    bool ATM::isValidCard(const std::string &cardNumber, const std::shared_ptr<Bank> &issuingBank) const
    {
        if (bankType == BankType::SINGLE_BANK)
        {
            return issuingBank == primaryBank;
        }
        return true; // Multi-bank ATM accepts all cards
    }

    int ATM::getTransactionFee(const std::shared_ptr<Bank> &bank, TransactionType type) const
    {
        bool isPrimaryBank = (bank == primaryBank);

        switch (type)
        {
        case TransactionType::DEPOSIT:
            return isPrimaryBank ? TransactionFees::DEPOSIT_PRIMARY : TransactionFees::DEPOSIT_NON_PRIMARY;
        case TransactionType::WITHDRAWAL:
            return isPrimaryBank ? TransactionFees::WITHDRAWAL_PRIMARY : TransactionFees::WITHDRAWAL_NON_PRIMARY;
        case TransactionType::TRANSFER_ACCOUNT:
            if (isPrimaryBank)
                return TransactionFees::TRANSFER_PRIMARY;
            return TransactionFees::TRANSFER_NON_PRIMARY;
        case TransactionType::TRANSFER_CASH:
            return TransactionFees::TRANSFER_CASH;
        default:
            return 0;
        }
    }

} // namespace ATMSystem