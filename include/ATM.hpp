#ifndef ATM_HPP
#define ATM_HPP

#include <string>
#include <map>
#include <memory>
#include <vector>
#include "Constants.hpp"
#include "Bank.hpp"
#include "UI.hpp"

namespace ATMSystem
{
    class ATM
    {
    private:
        std::string serialNumber; // 6-digit
        BankType bankType;
        LanguageSupport languageSupport;
        std::shared_ptr<Bank> primaryBank;
        std::vector<std::shared_ptr<Bank>> connectedBanks;
        std::map<int, int> cashInventory; // denomination -> count
        bool isValidCheck(double amount) const
        {
            return amount >= MIN_CHECK_AMOUNT;
        }
        UI ui;

    public:
        ATM(const std::string &serial, BankType type, LanguageSupport lang, std::shared_ptr<Bank> primary);

        // Add method to connect banks for multi-bank ATMs
        void addConnectedBank(std::shared_ptr<Bank> bank);

        // Basic operation methods
        bool insertCard(const std::string &cardNumber);
        bool validatePin(const std::string &pin);
        bool deposit(const std::string &accountNumber, double amount, bool isCash, int &depositedAmount, int &fee);
        bool withdraw(const std::string &accountNumber, double amount, int &withdrawnAmount, int &fee, std::map<int, int> &bills);
        bool transfer(const std::string &fromAccount, const std::string &toAccount, double amount, bool isCashTransfer, int &transferredAmount, int &fee);
        void printTransactionHistory() const;
        void endSession();

        // Cash management methods
        bool addCash(const std::map<int, int> &cash);
        bool hasSufficientCash(int amount) const;
        std::map<int, int> getCashBreakdown(int amount) const;
        void updateCashInventory(double amount);

        // Validation methods
        bool isValidCard(const std::string &cardNumber, const std::shared_ptr<Bank> &issuingBank) const;
        int getTransactionFee(const std::shared_ptr<Bank> &sourceBank,
                              const std::shared_ptr<Bank> &destBank,
                              TransactionType type) const;

        // Getters
        std::string getSerialNumber() const { return serialNumber; }
        BankType getBankType() const { return bankType; }
        LanguageSupport getLanguageSupport() const { return languageSupport; }
        std::shared_ptr<Bank> getPrimaryBank() const { return primaryBank; }
    };
}

#endif