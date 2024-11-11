// src/SystemInitializer.cpp
#include "SystemInitializer.hpp"
#include <iostream>
#include <random>

namespace ATMSystem
{

    std::string SystemInitializer::generateSerialNumber()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, 999999);

        std::string serial = std::to_string(dis(gen));
        while (serial.length() < 6)
        {
            serial = "0" + serial;
        }
        return serial;
    }

    void SystemInitializer::initializeSystem()
    {
        std::cout << "=== ATM System Initialization ===\n\n";

        // Initialize banks
        initializeBanks();

        // Initialize ATMs
        initializeATMs();

        std::cout << "\nSystem initialization completed!\n";
    }

    void SystemInitializer::initializeBanks()
    {
        std::cout << "Creating banks...\n";
        std::cout << "Enter number of banks to create: ";
        int numBanks;
        std::cin >> numBanks;
        std::cin.ignore();

        for (int i = 0; i < numBanks; i++)
        {
            std::cout << "\nBank " << (i + 1) << " name: ";
            std::string bankName;
            std::getline(std::cin, bankName);

            auto bank = std::make_shared<Bank>(bankName);
            banks.push_back(bank);

            // Initialize accounts for this bank
            initializeBankAccounts(bank);
        }
    }

    // In SystemInitializer.cpp, modify initializeATMs():

    void SystemInitializer::initializeATMs()
    {
        std::cout << "\nCreating ATMs...\n";
        std::cout << "Enter number of ATMs to create: ";
        int numATMs;
        while (!(std::cin >> numATMs) || numATMs <= 0)
        {
            std::cout << "Please enter a valid number greater than 0: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore();

        for (int i = 0; i < numATMs; i++)
        {
            // Generate unique serial number
            std::string serial = generateSerialNumber();

            // Get ATM type
            int typeChoice;
            do
            {
                std::cout << "\nATM " << (i + 1) << " type (1: Single Bank, 2: Multi-Bank): ";
                std::cin >> typeChoice;
                if (typeChoice != 1 && typeChoice != 2)
                {
                    std::cout << "Invalid choice. Please enter 1 or 2.\n";
                }
            } while (typeChoice != 1 && typeChoice != 2);
            BankType bankType = (typeChoice == 1) ? BankType::SINGLE_BANK : BankType::MULTI_BANK;

            // Get language support
            int langChoice;
            do
            {
                std::cout << "Language support (1: Unilingual, 2: Bilingual): ";
                std::cin >> langChoice;
                if (langChoice != 1 && langChoice != 2)
                {
                    std::cout << "Invalid choice. Please enter 1 or 2.\n";
                }
            } while (langChoice != 1 && langChoice != 2);
            LanguageSupport langSupport = (langChoice == 1) ? LanguageSupport::UNILINGUAL : LanguageSupport::BILINGUAL;

            // Select primary bank
            std::cout << "Available banks:\n";
            for (size_t j = 0; j < banks.size(); j++)
            {
                std::cout << (j + 1) << ". " << banks[j]->getName() << "\n";
            }

            int bankChoice;
            do
            {
                std::cout << "Select primary bank (1-" << banks.size() << "): ";
                std::cin >> bankChoice;
                if (bankChoice < 1 || bankChoice > static_cast<int>(banks.size()))
                {
                    std::cout << "Invalid choice. Please select a number between 1 and " << banks.size() << ".\n";
                }
            } while (bankChoice < 1 || bankChoice > static_cast<int>(banks.size()));
            bankChoice--;

            // Initialize cash inventory
            std::cout << "\nInitialize cash inventory for ATM " << serial << ":\n";
            std::map<int, int> inventory;
            for (const auto &[denom, _] : VALID_DENOMINATIONS)
            {
                int count;
                do
                {
                    std::cout << "Enter number of " << denom << " KRW bills: ";
                    std::cin >> count;
                    if (count < 0)
                    {
                        std::cout << "Please enter a non-negative number.\n";
                    }
                } while (count < 0);
                inventory[denom] = count;
            }

            // Create ATM and initialize cash
            auto atm = std::make_shared<ATM>(serial, bankType, langSupport, banks[bankChoice]);
            atm->addCash(inventory);
            atms.push_back(atm);

            std::cout << "ATM " << serial << " created successfully!\n";
        }
        std::cin.ignore();
    }

    void SystemInitializer::initializeBankAccounts(const std::shared_ptr<Bank> &bank)
    {
        std::cout << "Enter number of users for " << bank->getName() << ": ";
        int numUsers;
        std::cin >> numUsers;
        std::cin.ignore();

        for (int i = 0; i < numUsers; i++)
        {
            std::cout << "User " << (i + 1) << " name: ";
            std::string userName;
            std::getline(std::cin, userName);

            std::cout << "Number of accounts for " << userName << ": ";
            int numAccounts;
            std::cin >> numAccounts;
            std::cin.ignore();

            for (int j = 0; j < numAccounts; j++)
            {
                // Generate 12-digit account number with proper padding
                std::string accountNum = std::to_string(std::rand() % 1000000000000LL);
                while (accountNum.length() < 12)
                {
                    accountNum = "0" + accountNum;
                }
                accountNum = accountNum.substr(0, 12); // Ensure exactly 12 digits

                bank->createAccount(userName, accountNum);
                std::cout << "Created account " << accountNum << " for " << userName << "\n";
            }
        }
    }

    const std::vector<std::shared_ptr<ATM>> &SystemInitializer::getATMs() const
    {
        return atms;
    }

    const std::vector<std::shared_ptr<Bank>> &SystemInitializer::getBanks() const
    {
        return banks;
    }

} // namespace ATMSystem