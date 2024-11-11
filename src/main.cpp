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

void displayCashBreakdown(int amount, const std::shared_ptr<ATM> &atm)
{
    int remaining = amount;
    std::map<int, int> bills;

    // Calculate bills needed (largest to smallest)
    const std::vector<int> denominations = {50000, 10000, 5000, 1000};
    for (int denom : denominations)
    {
        if (remaining >= denom)
        {
            int needed = remaining / denom;
            // Use the ATM's getCashBreakdown method instead
            auto breakdown = atm->getCashBreakdown(amount);
            bills = breakdown;
            break;
        }
    }

    std::cout << "Bills breakdown:\n";
    for (const auto &[denom, count] : bills)
    {
        if (count > 0)
        {
            std::cout << count << " × " << formatCurrency(denom) << "\n";
        }
    }
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

        // Display available ATMs
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
            std::cin >> atmChoice;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            if (atmChoice < 1 || atmChoice > static_cast<int>(atms.size()))
            {
                std::cout << "Invalid choice. Please select a number between 1 and " << atms.size() << ".\n";
            }
        } while (atmChoice < 1 || atmChoice > static_cast<int>(atms.size()));
        atmChoice--;

        auto selectedATM = atms[atmChoice];
        UI ui(selectedATM->getLanguageSupport() == LanguageSupport::BILINGUAL);

        // Language selection for bilingual ATMs
        if (selectedATM->getLanguageSupport() == LanguageSupport::BILINGUAL)
        {
            ui.displayMessage("SELECT_LANGUAGE");
            std::string langChoice;
            bool validChoice = false;
            do
            {
                langChoice = ui.getInput();
                if (langChoice == "1" || langChoice == "2")
                {
                    validChoice = true;
                }
                else
                {
                    std::cout << "Please enter 1 for English or 2 for Korean.\n";
                }
            } while (!validChoice);

            ui.setLanguage(langChoice == "2");
        }

        ui.displayMessage("WELCOME");

        // Card input with error handling
        std::string cardNumber;
        bool validCard = false;
        do
        {
            ui.showDisplayPanel("INSERT_CARD");
            cardNumber = ui.getInput();
            if (cardNumber.length() != 12)
            { // Changed from 16 to 12
                std::cout << "Invalid card number length. Please enter a 12-digit account number.\n";
            }
            else
            {
                // We're using account numbers as card numbers in this implementation
                // Verify if the card is valid for this ATM based on the bank
                auto bank = selectedATM->getPrimaryBank();
                auto account = bank->getAccount(cardNumber);

                if (selectedATM->getBankType() == BankType::SINGLE_BANK)
                {
                    // For single bank ATM, card must be from primary bank
                    if (account)
                    {
                        validCard = true;
                    }
                    else
                    {
                        std::cout << "Card not valid for this ATM (Single Bank ATM only accepts cards from "
                                  << bank->getName() << ").\n";
                    }
                }
                else
                {
                    // For multi-bank ATM, card can be from any bank
                    validCard = true;
                    for (const auto &bank : initializer.getBanks())
                    {
                        if (bank->getAccount(cardNumber))
                        {
                            validCard = true;
                            break;
                        }
                    }
                    if (!validCard)
                    {
                        std::cout << "Invalid card number. Account not found in any bank.\n";
                    }
                }
            }
        } while (!validCard);

        // PIN input with error handling
        std::string pin;
        bool validPin = false;
        int attempts = 0;
        const int MAX_ATTEMPTS = 3;

        do
        {
            std::cout << "\n----------------------------------------\n";
            std::cout << "Enter your PIN:";
            std::cout << "\n----------------------------------------\n";
            pin = ui.getInput();

            if (pin.length() != 4)
            {
                std::cout << "Invalid PIN length. Please enter a 4-digit PIN.\n";
                attempts++;
            }
            else
            {
                // Here you would verify the PIN with the bank
                validPin = true;
            }

            if (attempts >= MAX_ATTEMPTS)
            {
                std::cout << "Maximum PIN attempts exceeded. Session terminated.\n";
                return 1;
            }
        } while (!validPin && attempts < MAX_ATTEMPTS);

        // Main ATM operation loop
        int currentBalance = 0; // This should come from the account
        std::vector<std::string> transactionLog;
        bool running = true;

        while (running)
        {
            ui.displayMenu();
            std::string choice = ui.getInput();

            switch (choice[0])
            {
            case '1':
            { // Deposit
                auto cashInput = ui.getCashInput();
                int depositAmount = 0;
                std::cout << "\nDeposited:\n";

                for (const auto &[denomination, count] : cashInput)
                {
                    int amount = denomination * count;
                    depositAmount += amount;
                    if (count > 0)
                    {
                        std::cout << count << " × " << formatCurrency(denomination) << "\n";
                    }
                }

                // Add deposit fee
                const int depositFee = 1000; // Primary bank fee
                std::cout << "\nDeposit fee: " << formatCurrency(depositFee) << "\n";

                currentBalance += depositAmount - depositFee;
                transactionLog.push_back("Deposit: " + formatCurrency(depositAmount) +
                                         " (Fee: " + formatCurrency(depositFee) + ")");
                std::cout << "\nDeposit successful!\nNew balance: " << formatCurrency(currentBalance) << "\n";
                break;
            }
            case '2':
            { // Withdraw
                int amount;
                bool validAmount = false;
                do
                {
                    std::cout << "Enter amount to withdraw: ";
                    std::string amountStr = ui.getInput();
                    try
                    {
                        amount = std::stoi(amountStr);
                        if (amount <= 0)
                        {
                            std::cout << "Please enter a positive amount.\n";
                        }
                        else if (amount > MAX_WITHDRAWAL_PER_TRANSACTION)
                        {
                            std::cout << "Amount exceeds maximum withdrawal limit of " << formatCurrency(MAX_WITHDRAWAL_PER_TRANSACTION) << "\n";
                        }
                        else
                        {
                            validAmount = true;
                        }
                    }
                    catch (const std::exception &)
                    {
                        std::cout << "Invalid amount. Please enter a number.\n";
                    }
                } while (!validAmount);

                const int withdrawalFee = 1000; // Primary bank fee

                if (amount + withdrawalFee > currentBalance)
                {
                    std::cout << "Insufficient funds! (Amount + " << formatCurrency(withdrawalFee) << " fee)\n";
                }
                else if (!selectedATM->hasSufficientCash(amount))
                {
                    std::cout << "ATM does not have sufficient cash for this withdrawal.\n";
                }
                else
                {
                    currentBalance -= (amount + withdrawalFee);
                    transactionLog.push_back("Withdrawal: " + formatCurrency(amount) +
                                             " (Fee: " + formatCurrency(withdrawalFee) + ")");
                    std::cout << "\nWithdrawal successful!\n";
                    displayCashBreakdown(amount, selectedATM); // Pass the ATM object
                    std::cout << "Fee: " << formatCurrency(withdrawalFee) << "\n";
                    std::cout << "New balance: " << formatCurrency(currentBalance) << "\n";
                }
                break;
            }
            case '3':
            { // Transfer
                std::string destAccount;
                bool validDestAccount = false;
                do
                {
                    std::cout << "Enter destination account (12 digits): ";
                    destAccount = ui.getInput();
                    if (destAccount.length() != 12)
                    {
                        std::cout << "Invalid account number. Please enter a 12-digit number.\n";
                    }
                    else
                    {
                        validDestAccount = true;
                    }
                } while (!validDestAccount);

                int amount;
                bool validAmount = false;
                do
                {
                    std::cout << "Enter amount to transfer: ";
                    std::string amountStr = ui.getInput();
                    try
                    {
                        amount = std::stoi(amountStr);
                        if (amount <= 0)
                        {
                            std::cout << "Please enter a positive amount.\n";
                        }
                        else
                        {
                            validAmount = true;
                        }
                    }
                    catch (const std::exception &)
                    {
                        std::cout << "Invalid amount. Please enter a number.\n";
                    }
                } while (!validAmount);

                const int transferFee = 2000; // Primary bank transfer fee

                if (amount + transferFee > currentBalance)
                {
                    std::cout << "Insufficient funds! (Amount + " << formatCurrency(transferFee) << " fee)\n";
                }
                else
                {
                    currentBalance -= (amount + transferFee);
                    transactionLog.push_back("Transfer to " + destAccount + ": " +
                                             formatCurrency(amount) +
                                             " (Fee: " + formatCurrency(transferFee) + ")");
                    std::cout << "\nTransfer successful!\n";
                    std::cout << "Fee: " << formatCurrency(transferFee) << "\n";
                    std::cout << "New balance: " << formatCurrency(currentBalance) << "\n";
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
        std::vector<std::string> summary;
        summary.push_back("Card: " + cardNumber.substr(0, 4) + " **** **** " +
                          cardNumber.substr(12));
        summary.push_back("Total Transactions: " + std::to_string(transactionLog.size()));

        // Add individual transactions
        for (const auto &transaction : transactionLog)
        {
            summary.push_back(transaction);
        }

        summary.push_back("Final Balance: " + formatCurrency(currentBalance));

        ui.showTransactionSummary(summary);

        // Ask for receipt
        std::string receiptChoice;
        do
        {
            std::cout << "Would you like a receipt? (Y/N): ";
            receiptChoice = ui.getInput();
            if (receiptChoice != "Y" && receiptChoice != "y" &&
                receiptChoice != "N" && receiptChoice != "n")
            {
                std::cout << "Invalid choice. Please enter Y or N.\n";
            }
        } while (receiptChoice != "Y" && receiptChoice != "y" &&
                 receiptChoice != "N" && receiptChoice != "n");

        if (receiptChoice == "Y" || receiptChoice == "y")
        {
            ui.printReceipt(summary);
        }

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}