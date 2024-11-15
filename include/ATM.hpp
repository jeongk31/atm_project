#ifndef ATM_HPP
#define ATM_HPP

#include <string>
#include <map>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "Constants.hpp"
#include "Bank.hpp"
#include "UI.hpp"
#include "Session.hpp"
#include "Transaction.hpp"

namespace ATMSystem
{
    class ATM : public std::enable_shared_from_this<ATM>
    {
    private:
        std::string serialNumber;
        BankType bankType;
        LanguageSupport languageSupport;
        std::shared_ptr<Bank> primaryBank;
        std::vector<std::shared_ptr<Bank>> connectedBanks;
        std::map<int, int> cashInventory; // denomination -> count
        std::shared_ptr<Session> currentSession;
        std::vector<Transaction> transactionHistory;
        const std::string ADMIN_CARD = "999999999999";

        bool isValidCheck(double amount) const
        {
            return amount >= MIN_CHECK_AMOUNT;
        }
        UI ui;

    public:
        ATM(const std::string &serial, BankType type, LanguageSupport lang, std::shared_ptr<Bank> primary);
        void addConnectedBank(std::shared_ptr<Bank> bank);
        bool insertCard(const std::string &cardNumber);
        bool validatePin(const std::string &accountNumber, const std::string &pin, int &attempts);
        bool deposit(const std::string &accountNumber, double amount, bool isCash, int &depositedAmount, int &fee);
        bool withdraw(const std::string &accountNumber, double amount, int &withdrawnAmount, int &fee, std::map<int, int> &bills);
        bool transfer(const std::string &fromAccount, const std::string &toAccount, double amount, bool isCashTransfer, int &transferredAmount, int &fee);
        void endSession();

        void startSession(const std::string &cardNumber, std::shared_ptr<Account> account);
        void endCurrentSession(const std::string &reason = "");
        bool hasActiveSession() const { return currentSession && currentSession->isSessionActive(); }
        std::shared_ptr<Session> getCurrentSession() const { return currentSession; }

        bool addCash(const std::map<int, int> &cash);
        bool hasSufficientCash(int amount) const;
        std::map<int, int> getCashBreakdown(int amount) const;
        void updateCashInventory(double amount);
        void setLanguage(bool korean)
        {
            ui.setLanguage(korean);
        }

        static const int MAX_PIN_ATTEMPTS;

        bool isValidCard(const std::string &cardNumber, const std::shared_ptr<Bank> &issuingBank) const;
        int getTransactionFee(const std::shared_ptr<Bank> &sourceBank,
                              const std::shared_ptr<Bank> &destBank,
                              TransactionType type) const;

        std::string getSerialNumber() const { return serialNumber; }
        BankType getBankType() const { return bankType; }
        LanguageSupport getLanguageSupport() const { return languageSupport; }
        std::shared_ptr<Bank> getPrimaryBank() const { return primaryBank; }

        bool processCashDeposit(const std::string &accountNumber, int amount,
                                const std::map<int, int> &cashInput,
                                const std::map<int, int> &feeInput,
                                int &depositedAmount);
        bool processCheckDeposit(const std::string &accountNumber, int amount,
                                 const std::map<int, int> &feeInput,
                                 int &depositedAmount);

        bool isAdminCard(const std::string &cardNumber) const;

        void addToHistory(const Transaction &transaction)
        {
            transactionHistory.push_back(transaction);
        }

        void displayAdminMenu(UI &ui);
        void printTransactionHistory() const;
        void exportTransactionHistory(const std::string &filename) const;

        const std::map<int, int> &getCashInventory() const { return cashInventory; }
    };
}

#endif