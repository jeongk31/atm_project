#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <sstream>
#include <chrono>
#include "ATM.hpp"
#include "Bank.hpp"
#include "Account.hpp"
#include "Transaction.hpp"
#include "Session.hpp"
#include "Constants.hpp"
#include "UI.hpp"

namespace ATMSystem
{

    const int ATM::MAX_PIN_ATTEMPTS = 3;

    ATM::ATM(const std::string &serial, BankType type, LanguageSupport lang, std::shared_ptr<Bank> primary)
        : serialNumber(serial),
          bankType(type),
          languageSupport(lang),
          primaryBank(primary),
          ui(lang == LanguageSupport::BILINGUAL)
    {
    }

    void ATM::printTransactionHistory() const
    {
        ui.displayMessage("TRANSACTION_HISTORY_HEADER");

        // Header row
        std::cout << std::left
                  << std::setw(25) << ui.getLocalizedMessage("TRANSACTION_ID_HEADER")
                  << std::setw(15) << ui.getLocalizedMessage("CARD_NUMBER_HEADER")
                  << std::setw(25) << ui.getLocalizedMessage("TYPE_HEADER")
                  << std::setw(12) << ui.getLocalizedMessage("AMOUNT_HEADER")
                  << std::setw(10) << ui.getLocalizedMessage("FEE_HEADER")
                  << std::setw(35) << ui.getLocalizedMessage("TIMESTAMP_HEADER")
                  << ui.getLocalizedMessage("DETAILS_HEADER") << "\n";

        std::cout << std::string(150, '-') << '\n';

        // Transaction rows
        for (const auto &transaction : transactionHistory)
        {
            std::cout << std::left
                      << std::setw(25) << transaction.getTransactionId()
                      << std::setw(15) << transaction.getCardNumber()
                      << std::setw(25) << transaction.getTypeString()
                      << std::setw(12) << std::fixed << std::setprecision(2) << transaction.getAmount()
                      << std::setw(10) << std::fixed << std::setprecision(2) << transaction.getFee()
                      << transaction.getFormattedTimestamp() << "  "
                      << std::left << transaction.getDetails() << '\n';
        }

        std::cout << std::string(150, '-') << '\n';
    }

    void ATM::exportTransactionHistory(const std::string &filename) const
    {
        std::ofstream file(filename);
        if (!file)
        {
            ui.displayMessage("ERROR_SYSTEM");
            return;
        }

        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);

        file << ui.getLocalizedMessage("TRANSACTION_HISTORY_HEADER") << " - "
             << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")
             << "\n\n";

        // Header row
        file << std::left
             << std::setw(25) << ui.getLocalizedMessage("TRANSACTION_ID_HEADER")
             << std::setw(15) << ui.getLocalizedMessage("CARD_NUMBER_HEADER")
             << std::setw(20) << ui.getLocalizedMessage("TYPE_HEADER")
             << std::right << std::setw(12) << ui.getLocalizedMessage("AMOUNT_HEADER")
             << std::setw(10) << ui.getLocalizedMessage("FEE_HEADER")
             << std::setw(25) << ui.getLocalizedMessage("TIMESTAMP_HEADER")
             << std::left << ui.getLocalizedMessage("DETAILS_HEADER") << "\n";

        file << std::string(150, '-') << '\n';

        // Transaction rows
        for (const auto &transaction : transactionHistory)
        {
            file << std::left
                 << std::setw(25) << transaction.getTransactionId()
                 << std::setw(15) << transaction.getCardNumber()
                 << std::setw(20) << transaction.getTypeString()
                 << std::right << std::setw(10) << std::fixed << std::setprecision(2) << transaction.getAmount()
                 << std::setw(8) << std::fixed << std::setprecision(2) << transaction.getFee()
                 << transaction.getFormattedTimestamp() << "  "
                 << std::left << transaction.getDetails() << '\n';
        }

        file << std::string(150, '-') << '\n';

        file.close();
        ui.displayMessage("EXPORT_SUCCESS");
    }

    bool ATM::isAdminCard(const std::string &cardNumber) const
    {
        return cardNumber == ADMIN_CARD;
    }

    void ATM::displayAdminMenu(UI &ui)
    {
        ui.displayMessage("ADMIN_MENU");
        std::string choice = ui.getInput();

        if (choice == "1")
        {
            printTransactionHistory();
            exportTransactionHistory("transaction_history.txt");
        }

        endCurrentSession();
        ui.displayMessage("THANK_YOU");
        std::cout << "\n";
        for (int i = 0; i < 60; i++)
            std::cout << "#";
        std::cout << "\n\n";
    }

    void ATM::startSession(const std::string &cardNumber, std::shared_ptr<Account> account)
    {
        currentSession = std::make_shared<Session>(cardNumber, account, shared_from_this());
    }

    void ATM::endCurrentSession(const std::string &reason)
    {
        if (currentSession)
        {
            currentSession->endSession(reason);
            currentSession.reset();
        }
    }

    void ATM::addConnectedBank(std::shared_ptr<Bank> bank)
    {
        if (bank != primaryBank)
        {
            connectedBanks.push_back(bank);
        }
    }

    bool ATM::insertCard(const std::string &cardNumber)
    {
        return true;
    }

    bool ATM::validatePin(const std::string &accountNumber, const std::string &pin, int &attempts)
    {
        std::shared_ptr<Bank> cardBank = primaryBank;
        bool found = false;

        // find which bank card belongs to
        if (auto account = primaryBank->getAccount(accountNumber))
        {
            found = true;
        }
        else if (bankType == BankType::MULTI_BANK)
        {
            for (const auto &bank : connectedBanks)
            {
                if (auto account = bank->getAccount(accountNumber))
                {
                    cardBank = bank;
                    found = true;
                    break;
                }
            }
        }

        if (!found)
        {
            return false;
        }

        // verify PIN with bank
        if (!cardBank->verifyPIN(accountNumber, pin))
        {
            attempts++;
            if (attempts >= MAX_PIN_ATTEMPTS)
            {
                ui.displayMessage("MAX_ATTEMPTS_EXCEEDED");
                if (currentSession)
                {
                    currentSession->endSessionWithError(ui.getLocalizedMessage("MAX_PIN_EXCEEDED"));
                }
                return false;
            }
            ui.displayMessage("WRONG_PIN");
            std::string message = ui.getLocalizedMessage("ATTEMPTS_REMAINING");
            size_t pos = message.find("{}");
            message.replace(pos, 2, std::to_string(MAX_PIN_ATTEMPTS - attempts));
            std::cout << message << "\n";
            return false;
        }

        return true;
    }

    bool ATM::processCashDeposit(const std::string &accountNumber, int amount,
                                 const std::map<int, int> &cashInput,
                                 const std::map<int, int> &feeInput,
                                 int &depositedAmount)
    {
        // count total bills in deposit
        int totalBills = 0;
        for (const auto &[denom, count] : cashInput)
        {
            totalBills += count;
        }

        if (totalBills > MAX_CASH_INSERT)
        {
            ui.displayMessage("MAX_DEPOSIT_EXCEEDED");
            return false;
        }

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
            ui.displayMessage("ACCOUNT_NOT_FOUND");
            return false;
        }

        // update ATM cash inventory
        for (const auto &[denom, count] : cashInput)
        {
            cashInventory[denom] += count;
        }
        for (const auto &[denom, count] : feeInput)
        {
            cashInventory[denom] += count;
        }

        depositedAmount = amount;
        return account->deposit(depositedAmount);
    }

    bool ATM::processCheckDeposit(const std::string &accountNumber, int amount,
                                  const std::map<int, int> &feeInput,
                                  int &depositedAmount)
    {
        if (!currentSession->canDepositCheck())
        {
            ui.displayMessage("MAX_CHECK_DEPOSIT_EXCEEDED");
            return false;
        }

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
            ui.displayMessage("ACCOUNT_NOT_FOUND");
            return false;
        }

        // update ATM cash inventory
        for (const auto &[denom, count] : feeInput)
        {
            cashInventory[denom] += count;
        }

        depositedAmount = amount;
        if (account->deposit(depositedAmount))
        {
            currentSession->incrementCheckDeposit();
            return true;
        }
        else
        {
            return false;
        }
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
            ui.displayMessage("ACCOUNT_NOT_FOUND");
            return false;
        }

        fee = isPrimaryBank ? TransactionFees::DEPOSIT_PRIMARY
                            : TransactionFees::DEPOSIT_NON_PRIMARY;

        if (isCash)
        {
            updateCashInventory(amount);
        }

        depositedAmount = amount;

        if (account->deposit(depositedAmount))
        {
            // add transaction to history
            if (currentSession)
            {
                currentSession->addTransaction(
                    TransactionType::DEPOSIT,
                    depositedAmount,
                    fee,
                    isCash ? ui.getLocalizedMessage("CASH_DEPOSIT_TYPE") : ui.getLocalizedMessage("CHECK_DEPOSIT_TYPE"));
            }
            return true;
        }
        return false;
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
            ui.displayMessage("ACCOUNT_NOT_FOUND");
            return false;
        }

        fee = isPrimaryBank ? TransactionFees::WITHDRAWAL_PRIMARY
                            : TransactionFees::WITHDRAWAL_NON_PRIMARY;

        withdrawnAmount = amount;

        if (!hasSufficientCash(amount))
        {
            ui.displayMessage("ERROR_INSUFFICIENT_CASH");
            return false;
        }

        if (account->getBalance() < amount + fee)
        {
            ui.displayMessage("INSUFFICIENT_FUNDS");
            return false;
        }

        bills = getCashBreakdown(amount);
        if (bills.empty())
        {
            ui.displayMessage("ERROR_INVALID_OPERATION");
            return false;
        }

        if (account->withdraw(amount + fee))
        {
            updateCashInventory(-amount);
            // add transaction to history
            if (currentSession)
            {
                currentSession->addTransaction(
                    TransactionType::WITHDRAWAL,
                    amount,
                    fee,
                    ui.getLocalizedMessage("WITHDRAWAL_TYPE"));
                currentSession->incrementWithdrawalCount();
            }
            return true;
        }
        return false;
    }

    bool ATM::transfer(const std::string &fromAccount, const std::string &toAccount,
                       double amount, bool isCashTransfer,
                       int &transferredAmount, int &fee)
    {
        // validate destination account exists
        std::shared_ptr<Account> destAccount = primaryBank->getAccount(toAccount);
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
            ui.displayMessage("INVALID_ACCOUNT");
            return false;
        }

        if (isCashTransfer)
        {
            fee = TransactionFees::TRANSFER_CASH;
            transferredAmount = amount;

            if (transferredAmount <= 0)
            {
                ui.displayMessage("INVALID_AMOUNT");
                return false;
            }

            // update ATM cash inventory
            updateCashInventory(amount);

            // add transaction to session history
            if (currentSession)
            {
                currentSession->addTransaction(
                    TransactionType::TRANSFER_CASH,
                    transferredAmount,
                    fee,
                    ui.getLocalizedMessage("TO") + " " + toAccount);
            }

            return destAccount->deposit(transferredAmount);
        }
        else
        {
            auto sourceAccount = primaryBank->getAccount(fromAccount);
            bool isSourcePrimary = true;

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

            if (!sourceAccount)
            {
                ui.displayMessage("INVALID_ACCOUNT");
                return false;
            }

            // calculate transfer fee
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
                ui.displayMessage("INSUFFICIENT_FUNDS");
                return false;
            }

            if (sourceAccount->withdraw(amount + fee))
            {
                if (destAccount->deposit(amount))
                {
                    if (currentSession)
                    {
                        currentSession->addTransaction(
                            TransactionType::TRANSFER_ACCOUNT,
                            transferredAmount,
                            fee,
                            ui.getLocalizedMessage("FROM") + " " + fromAccount + " " + ui.getLocalizedMessage("TO") + " " + toAccount);
                    }
                    return true;
                }
                else
                {
                    sourceAccount->deposit(amount + fee);
                }
            }
            return false;
        }
    }

    void ATM::endSession()
    {
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

        // use largest denominations first
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

        if (remaining > 0)
        {
            breakdown.clear();
        }

        return breakdown;
    }

    bool ATM::isValidCard(const std::string &cardNumber, const std::shared_ptr<Bank> &issuingBank) const
    {
        if (bankType == BankType::SINGLE_BANK)
        {
            return issuingBank == primaryBank;
        }
        return true;
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
        if (amount > 0)
        {
            return;
        }

        int remainingAmount = -amount;
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

}