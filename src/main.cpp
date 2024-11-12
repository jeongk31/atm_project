// src/main.cpp
#include <iostream>
#include <memory>
#include <iomanip>
#include "SystemInitializer.hpp"
#include "UI.hpp"
#include "ATM.hpp"
#include "Bank.hpp"

using namespace ATMSystem;

std::string formatCurrency(int amount)
{
    std::string str = std::to_string(amount);
    int pos = str.length() - 3;
    while (pos > 0)
    {
        str.insert(pos, ",");
        pos -= 3;
    }
    return "KRW " + str;
}

void displayCashBreakdown(const std::map<int, int> &bills)
{
    std::cout << "Bills breakdown:\n";
    for (const auto &[denom, count] : bills)
    {
        if (count > 0)
        {
            std::cout << count << " × " << formatCurrency(denom) << "\n";
        }
    }
}

bool processDepositFee(UI &ui, const std::shared_ptr<ATM> &atm, bool isPrimaryBank)
{
    int fee = isPrimaryBank ? TransactionFees::DEPOSIT_PRIMARY : TransactionFees::DEPOSIT_NON_PRIMARY;
    std::cout << "\nDeposit fee required: " << formatCurrency(fee) << "\n";
    std::cout << "Please insert cash for the fee:\n";

    auto feeInput = ui.getCashInput();
    int totalFeeInput = 0;
    for (const auto &[denom, count] : feeInput)
    {
        totalFeeInput += denom * count;
    }

    if (totalFeeInput < fee)
    {
        std::cout << "Insufficient fee amount. Transaction cancelled.\n";
        return false;
    }

    // Add fee to ATM cash inventory
    atm->addCash(feeInput);
    return true;
}

int main()
{
    try
    {
        // Initialize the system
        SystemInitializer initializer;
        initializer.initializeSystem();

        // Get available ATMs
        const auto &atms = initializer.getATMs();
        const auto &banks = initializer.getBanks();

        std::cout << "\nAvailable ATMs:\n";
        for (size_t i = 0; i < atms.size(); i++)
        {
            const auto &atm = atms[i];
            std::cout << (i + 1) << ". ATM " << atm->getSerialNumber()
                      << " (" << (atm->getBankType() == BankType::SINGLE_BANK ? "Single" : "Multi")
                      << "-Bank, Primary: " << atm->getPrimaryBank()->getName() << ")\n";
        }

        // ATM selection with error handling
        int atmChoice;
        do
        {
            std::cout << "Select ATM (1-" << atms.size() << "): ";
            if (!(std::cin >> atmChoice) || atmChoice < 1 || atmChoice > static_cast<int>(atms.size()))
            {
                std::cout << "Invalid choice. Please try again.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            break;
        } while (true);
        std::cin.ignore();
        atmChoice--;

        auto selectedATM = atms[atmChoice];
        UI ui(selectedATM->getLanguageSupport() == LanguageSupport::BILINGUAL);

        if (selectedATM->getLanguageSupport() == LanguageSupport::BILINGUAL)
        {
            ui.displayMessage("SELECT_LANGUAGE");
            std::string langChoice;
            do
            {
                langChoice = ui.getInput();
                if (langChoice != "1" && langChoice != "2")
                {
                    std::cout << "Please enter 1 for English or 2 for Korean.\n";
                }
            } while (langChoice != "1" && langChoice != "2");
            ui.setLanguage(langChoice == "2");
        }

        ui.displayMessage("WELCOME");

        // Card input and validation
        std::string cardNumber;
        std::shared_ptr<Bank> cardBank;
        std::shared_ptr<Account> userAccount;
        bool validCard = false;

        do
        {
            ui.showDisplayPanel("INSERT_CARD");
            cardNumber = ui.getInput();
            if (cardNumber.length() != 12)
            {
                std::cout << "Invalid card number length. Please enter a 12-digit number.\n";
                continue;
            }

            // Find the bank and account for this card
            for (const auto &bank : banks)
            {
                auto account = bank->getAccount(cardNumber);
                if (account)
                {
                    cardBank = bank;
                    userAccount = account;
                    break;
                }
            }

            if (!userAccount)
            {
                std::cout << "Invalid card: Account not found.\n";
                continue;
            }

            // Validate card based on ATM type
            if (selectedATM->getBankType() == BankType::SINGLE_BANK)
            {
                if (cardBank == selectedATM->getPrimaryBank())
                {
                    validCard = true;
                }
                else
                {
                    std::cout << "This ATM only accepts cards from " << selectedATM->getPrimaryBank()->getName() << ".\n";
                }
            }
            else
            {
                validCard = true;
            }
        } while (!validCard);

        // PIN validation
        int pinAttempts = 0;
        bool validPin = false;
        do
        {
            ui.showDisplayPanel("ENTER_PIN");
            std::string pin = ui.getInput();

            if (pin.length() != 4)
            {
                std::cout << "Invalid PIN length. Please enter a 4-digit PIN.\n";
                pinAttempts++;
            }
            else
            {
                validPin = true; // Simplified PIN validation
            }

            if (pinAttempts >= 3)
            {
                std::cout << "Maximum PIN attempts exceeded. Card retained.\n";
                return 1;
            }
        } while (!validPin && pinAttempts < 3);

        // Main transaction loop
        bool running = true;
        int withdrawalCount = 0;
        std::vector<std::string> transactionLog;

        while (running)
        {
            std::cout << "\n";
            for (int i = 0; i < 50; i++)
                std::cout << "#";
            std::cout << "\n\n";

            ui.displayMenu();
            std::string choice = ui.getInput();

            if (choice.empty() || (choice[0] != '1' && choice[0] != '2' &&
                                   choice[0] != '3' && choice[0] != '4'))
            {
                std::cout << "Invalid choice. Please select a valid option.\n";
                continue;
            }

            switch (choice[0])
            {
            case '1':
            { // Deposit
                std::cout << "\nSelect deposit type:\n1. Cash\n2. Check\n";
                std::string depositType = ui.getInput();

                if (depositType != "1" && depositType != "2")
                {
                    std::cout << "Invalid deposit type. Please try again.\n";
                    continue;
                }

                if (depositType == "1")
                { // Cash deposit
                    std::cout << "Enter cash to deposit:\n";
                    auto cashInput = ui.getCashInput();
                    int depositAmount = 0;
                    for (const auto &[denom, count] : cashInput)
                    {
                        depositAmount += denom * count;
                    }

                    if (depositAmount <= 0)
                    {
                        std::cout << "Invalid deposit amount.\n";
                        continue;
                    }

                    int depositedAmount;
                    int fee;
                    if (selectedATM->deposit(cardNumber, depositAmount, true, depositedAmount, fee))
                    {
                        std::cout << "\nDeposit successful!\n";
                        std::cout << "Amount deposited: " << formatCurrency(depositedAmount) << "\n";
                        std::cout << "Fee: " << formatCurrency(fee) << "\n";
                        std::cout << "New balance: " << formatCurrency(userAccount->getBalance()) << "\n";

                        transactionLog.push_back("Cash Deposit: " + formatCurrency(depositAmount) +
                                                 " (Fee: " + formatCurrency(fee) + ")");
                    }
                }
                else
                { // Check deposit
                    int checkAmount;
                    std::cout << "Enter check amount (minimum " << formatCurrency(MIN_CHECK_AMOUNT) << "): ";
                    if (!(std::cin >> checkAmount))
                    {
                        std::cout << "Invalid input.\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                    }
                    std::cin.ignore();

                    if (checkAmount < MIN_CHECK_AMOUNT)
                    {
                        std::cout << "Invalid check amount. Minimum is " << formatCurrency(MIN_CHECK_AMOUNT) << "\n";
                        continue;
                    }

                    int depositedAmount;
                    int fee;
                    if (selectedATM->deposit(cardNumber, checkAmount, false, depositedAmount, fee))
                    {
                        std::cout << "\nCheck deposit successful!\n";
                        std::cout << "Amount deposited: " << formatCurrency(depositedAmount) << "\n";
                        std::cout << "Fee: " << formatCurrency(fee) << "\n";
                        std::cout << "New balance: " << formatCurrency(userAccount->getBalance()) << "\n";

                        transactionLog.push_back("Check Deposit: " + formatCurrency(checkAmount) +
                                                 " (Fee: " + formatCurrency(fee) + ")");
                    }
                }
                break;
            }

            case '2':
            { // Withdraw
                if (withdrawalCount >= MAX_WITHDRAWALS_PER_SESSION)
                {
                    std::cout << "Maximum withdrawals per session (" << MAX_WITHDRAWALS_PER_SESSION << ") reached.\n";
                    continue;
                }

                int amount;
                std::cout << "Enter amount to withdraw (max " << formatCurrency(MAX_WITHDRAWAL_PER_TRANSACTION) << "): ";
                if (!(std::cin >> amount))
                {
                    std::cout << "Invalid input.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                std::cin.ignore();

                if (amount <= 0)
                {
                    std::cout << "Please enter a positive amount.\n";
                    continue;
                }

                if (amount > MAX_WITHDRAWAL_PER_TRANSACTION)
                {
                    std::cout << "Amount exceeds maximum withdrawal limit.\n";
                    continue;
                }

                int withdrawnAmount;
                int fee;
                std::map<int, int> bills;
                if (selectedATM->withdraw(cardNumber, amount, withdrawnAmount, fee, bills))
                {
                    withdrawalCount++;
                    std::cout << "\nWithdrawal successful!\n";
                    displayCashBreakdown(bills);
                    std::cout << "Fee: " << formatCurrency(fee) << "\n";
                    std::cout << "New balance: " << formatCurrency(userAccount->getBalance()) << "\n";

                    transactionLog.push_back("Withdrawal: " + formatCurrency(withdrawnAmount) +
                                             " (Fee: " + formatCurrency(fee) + ")");
                }
                break;
            }

            case '3':
            { // Transfer
                std::cout << "\nSelect transfer type:\n1. Cash Transfer\n2. Account Transfer\n";
                std::string transferType = ui.getInput();

                if (transferType != "1" && transferType != "2")
                {
                    std::cout << "Invalid transfer type. Please try again.\n";
                    continue;
                }

                std::cout << "Enter destination account number: ";
                std::string destAccountNum = ui.getInput();

                if (transferType == "1")
                { // Cash transfer
                    std::cout << "Enter cash to transfer:\n";
                    auto cashInput = ui.getCashInput();
                    int transferAmount = 0;
                    for (const auto &[denom, count] : cashInput)
                    {
                        transferAmount += denom * count;
                    }

                    int transferredAmount;
                    int fee;
                    if (selectedATM->transfer(cardNumber, destAccountNum, transferAmount, true, transferredAmount, fee))
                    {
                        std::cout << "\nCash transfer successful!\n";
                        std::cout << "Amount transferred: " << formatCurrency(transferredAmount) << "\n";
                        std::cout << "Fee: " << formatCurrency(fee) << "\n";

                        transactionLog.push_back("Cash Transfer: " + formatCurrency(transferredAmount) +
                                                 " to " + destAccountNum +
                                                 " (Fee: " + formatCurrency(fee) + ")");
                    }
                }
                else
                { // Account transfer
                    int amount;
                    std::cout << "Enter amount to transfer: ";
                    if (!(std::cin >> amount))
                    {
                        std::cout << "Invalid input.\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                    }
                    std::cin.ignore();

                    int transferredAmount;
                    int fee;
                    if (selectedATM->transfer(cardNumber, destAccountNum, amount, false, transferredAmount, fee))
                    {
                        std::cout << "\nAccount transfer successful!\n";
                        std::cout << "Amount transferred: " << formatCurrency(transferredAmount) << "\n";
                        std::cout << "Fee: " << formatCurrency(fee) << "\n";
                        std::cout << "New balance: " << formatCurrency(userAccount->getBalance()) << "\n";

                        transactionLog.push_back("Account Transfer: " + formatCurrency(transferredAmount) +
                                                 " to " + destAccountNum +
                                                 " (Fee: " + formatCurrency(fee) + ")");
                    }
                }
                break;
            }

            case '4': // Exit
                running = false;
                break;

            default:
                std::cout << "Invalid choice. Please select a valid option.\n";
            }
        }

        // Show transaction summary
        if (!transactionLog.empty())
        {
            std::cout << "\n=== Transaction Summary ===\n";
            std::cout << "Card: " << cardNumber << "\n";
            std::cout << "Bank: " << cardBank->getName() << "\n";
            for (const auto &transaction : transactionLog)
            {
                std::cout << transaction << "\n";
            }
            std::cout << "Final Balance: " << formatCurrency(userAccount->getBalance()) << "\n";
        }

        std::cout << "\nThank you for using our ATM service!\n";
        return 0;
    }
    catch (const std::exception &e)
    {
    }
}