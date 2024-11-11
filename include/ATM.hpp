// include/ATM.hpp
#ifndef ATM_HPP
#define ATM_HPP

#include <string>
#include <map>
#include <memory>
#include "Constants.hpp"
#include "Bank.hpp"

namespace ATMSystem
{
    class ATM
    {
    private:
        std::string serialNumber; // 6-digit
        BankType bankType;
        LanguageSupport languageSupport;
        std::shared_ptr<Bank> primaryBank;
        std::map<int, int> cashInventory; // denomination -> count

    public:
        // Constructor now includes primaryBank parameter
        ATM(const std::string &serial, BankType type, LanguageSupport lang, std::shared_ptr<Bank> primary);

        // Basic operation methods
        bool insertCard(const std::string &cardNumber);
        bool validatePin(const std::string &pin);
        bool deposit(double amount);
        bool withdraw(double amount);
        bool transfer(const std::string &toAccount, double amount);
        void printTransactionHistory() const;
        void endSession();

        // Cash management methods
        bool addCash(const std::map<int, int> &cash);
        bool hasSufficientCash(int amount) const;
        std::map<int, int> getCashBreakdown(int amount) const;

        // Validation methods
        bool isValidCard(const std::string &cardNumber, const std::shared_ptr<Bank> &issuingBank) const;
        int getTransactionFee(const std::shared_ptr<Bank> &bank, TransactionType type) const;

        // Getters
        std::string getSerialNumber() const { return serialNumber; }
        BankType getBankType() const { return bankType; }
        LanguageSupport getLanguageSupport() const { return languageSupport; }
        std::shared_ptr<Bank> getPrimaryBank() const { return primaryBank; }
    };
}

#endif