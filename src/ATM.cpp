// src/ATM.cpp
#include <iostream>
#include "ATM.hpp"

namespace ATMSystem
{

    ATM::ATM(const std::string &serial, BankType type, LanguageSupport lang, std::shared_ptr<Bank> primary)
        : serialNumber(serial),
          bankType(type),
          languageSupport(lang),
          primaryBank(primary),
          ui(lang == LanguageSupport::BILINGUAL)
    {
    }

    void ATM::addConnectedBank(std::shared_ptr<Bank> bank)
    {
        if (bank != primaryBank) // Don't add primary bank twice
        {
            connectedBanks.push_back(bank);
        }
    }

    bool ATM::insertCard(const std::string &cardNumber)
    {
        return true; // Placeholder implementation
    }

    bool ATM::validatePin(const std::string &pin)
    {
        return true; // Placeholder implementation
    }

    bool ATM::deposit(const std::string &accountNumber, double amount, bool isCash, int &depositedAmount, int &fee)
    {
        auto account = primaryBank->getAccount(accountNumber);
        bool isPrimaryBank = true;

        if (!account && bankType == BankType::MULTI_BANK)
        {
            for (const auto &bank : connectedBanks)
            {
                account = bank->getAccount(accountNumber);
                if (account)
                {
                    isPrimaryBank = false;
                    break;
                }
            }
        }

        if (!account)
        {
            std::cout << "Account not found.\n";
            return false;
        }

        // Calculate fee
        fee = isPrimaryBank ? TransactionFees::DEPOSIT_PRIMARY
                            : TransactionFees::DEPOSIT_NON_PRIMARY;

        std::cout << "\nTransaction fee: KRW " << fee << "\n";

        if (amount <= fee)
        {
            std::cout << "Deposit amount must be greater than fee amount.\n";
            return false;
        }

        if (isCash)
        {
            updateCashInventory(amount);
        }

        // Calculate deposited amount after fee
        depositedAmount = amount - fee;

        // Deposit amount minus fee
        bool success = account->deposit(depositedAmount);
        if (success)
        {
            return true;
        }
        else
        {
            std::cout << "Deposit failed. Please try again.\n";
            return false;
        }
    }

    bool ATM::withdraw(const std::string &accountNumber, double amount,
                       int &withdrawnAmount, int &fee, std::map<int, int> &bills)
    {
        auto account = primaryBank->getAccount(accountNumber);
        bool isPrimaryBank = true;

        if (!account && bankType == BankType::MULTI_BANK)
        {
            for (const auto &bank : connectedBanks)
            {
                account = bank->getAccount(accountNumber);
                if (account)
                {
                    isPrimaryBank = false;
                    break;
                }
            }
        }

        if (!account)
        {
            std::cout << "Account not found.\n";
            return false;
        }

        fee = isPrimaryBank ? TransactionFees::WITHDRAWAL_PRIMARY
                            : TransactionFees::WITHDRAWAL_NON_PRIMARY;

        withdrawnAmount = amount;

        if (!hasSufficientCash(amount))
        {
            std::cout << "ATM has insufficient cash.\n";
            return false;
        }

        if (account->getBalance() < amount + fee)
        {
            std::cout << "Insufficient funds (including fee).\n";
            return false;
        }

        bills = getCashBreakdown(amount);
        if (account->withdraw(amount + fee))
        {
            updateCashInventory(-amount);
            return true;
        }

        return false;
    }

    bool ATM::transfer(const std::string &fromAccount, const std::string &toAccount,
                       double amount, bool isCashTransfer,
                       int &transferredAmount, int &fee)
    {
        if (isCashTransfer)
        {
            auto destAccount = primaryBank->getAccount(toAccount);
            bool isDestPrimary = true;

            if (!destAccount && bankType == BankType::MULTI_BANK)
            {
                for (const auto &bank : connectedBanks)
                {
                    destAccount = bank->getAccount(toAccount);
                    if (destAccount)
                    {
                        isDestPrimary = false;
                        break;
                    }
                }
            }

            if (!destAccount)
            {
                std::cout << "Destination account not found.\n";
                return false;
            }

            fee = TransactionFees::TRANSFER_CASH;
            transferredAmount = amount - fee;

            if (transferredAmount <= 0)
            {
                std::cout << "Transfer amount must be greater than fee.\n";
                return false;
            }

            updateCashInventory(amount);
            return destAccount->deposit(transferredAmount);
        }
        else
        {
            auto sourceAccount = primaryBank->getAccount(fromAccount);
            auto destAccount = primaryBank->getAccount(toAccount);
            bool isSourcePrimary = true;
            bool isDestPrimary = true;

            if (!sourceAccount && bankType == BankType::MULTI_BANK)
            {
                for (const auto &bank : connectedBanks)
                {
                    sourceAccount = bank->getAccount(fromAccount);
                    if (sourceAccount)
                    {
                        isSourcePrimary = false;
                        break;
                    }
                }
            }

            if (!destAccount && bankType == BankType::MULTI_BANK)
            {
                for (const auto &bank : connectedBanks)
                {
                    destAccount = bank->getAccount(toAccount);
                    if (destAccount)
                    {
                        isDestPrimary = false;
                        break;
                    }
                }
            }

            if (!sourceAccount || !destAccount)
            {
                std::cout << "One or both accounts not found.\n";
                return false;
            }

            // Calculate transfer fee based on bank relationships
            if (isSourcePrimary && isDestPrimary)
            {
                fee = TransactionFees::TRANSFER_PRIMARY;
            }
            else if (!isSourcePrimary && !isDestPrimary)
            {
                fee = TransactionFees::TRANSFER_NON_PRIMARY;
            }
            else
            {
                fee = TransactionFees::TRANSFER_MIXED;
            }

            transferredAmount = amount;

            if (sourceAccount->getBalance() < amount + fee)
            {
                std::cout << "Insufficient funds (including " << fee << " KRW fee).\n";
                return false;
            }

            if (sourceAccount->withdraw(amount + fee))
            {
                return destAccount->deposit(amount);
            }
            return false;
        }
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

    int ATM::getTransactionFee(const std::shared_ptr<Bank> &sourceBank,
                               const std::shared_ptr<Bank> &destBank,
                               TransactionType type) const
    {
        bool isSourcePrimary = (sourceBank == primaryBank);
        bool isDestPrimary = (destBank == primaryBank);

        switch (type)
        {
        case TransactionType::DEPOSIT:
            return isSourcePrimary ? TransactionFees::DEPOSIT_PRIMARY
                                   : TransactionFees::DEPOSIT_NON_PRIMARY;

        case TransactionType::WITHDRAWAL:
            return isSourcePrimary ? TransactionFees::WITHDRAWAL_PRIMARY
                                   : TransactionFees::WITHDRAWAL_NON_PRIMARY;

        case TransactionType::TRANSFER_ACCOUNT:
            if (isSourcePrimary && isDestPrimary)
                return TransactionFees::TRANSFER_PRIMARY;
            else if (!isSourcePrimary && !isDestPrimary)
                return TransactionFees::TRANSFER_NON_PRIMARY;
            else
                return TransactionFees::TRANSFER_MIXED;

        case TransactionType::TRANSFER_CASH:
            return TransactionFees::TRANSFER_CASH;

        default:
            return 0;
        }
    }

    void ATM::updateCashInventory(double amount)
    {
        // For deposited cash, we already have the denomination breakdown
        if (amount > 0)
        {
            // The cash input has already been validated and broken down by denomination
            return;
        }

        // For withdrawals (negative amount), calculate the denomination breakdown
        int remainingAmount = -amount; // Make positive for calculation
        std::vector<int> denominations = {50000, 10000, 5000, 1000};

        for (int denom : denominations)
        {
            if (remainingAmount >= denom && cashInventory[denom] > 0)
            {
                int numBills = std::min(remainingAmount / denom, cashInventory[denom]);
                cashInventory[denom] -= numBills;
                remainingAmount -= numBills * denom;
            }
        }
    }

} // namespace ATMSystem