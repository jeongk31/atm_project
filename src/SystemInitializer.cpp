#include "SystemInitializer.hpp"
#include <iostream>
#include <random>
#include <set>

namespace ATMSystem
{

    std::string SystemInitializer::generateSerialNumber()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, 999999);
        static std::set<std::string> usedSerials;

        std::string serial;
        do
        {
            // generate new serial number
            serial = std::to_string(dis(gen));
            while (serial.length() < 6)
            {
                serial = "0" + serial;
            }
        } while (usedSerials.find(serial) != usedSerials.end());

        usedSerials.insert(serial);
        return serial;
    }

    void SystemInitializer::initializeSystem()
    {
        ui.displayMessage("SYSTEM_INIT");
        initializeBanks();
        initializeATMs();
        ui.displayMessage("SYSTEM_INIT_COMPLETE");
    }

    void SystemInitializer::initializeBanks()
    {
        std::cout << ui.getLocalizedMessage("ENTER_NUM_BANKS");
        int numBanks;
        std::cin >> numBanks;
        std::cin.ignore();

        for (int i = 0; i < numBanks; i++)
        {
            std::string message = ui.getLocalizedMessage("BANK_NAME_PROMPT");
            size_t pos = message.find("{}");
            message.replace(pos, 2, std::to_string(i + 1));
            std::cout << "\n"
                      << message;

            std::string bankName;
            std::getline(std::cin, bankName);

            auto bank = std::make_shared<Bank>(bankName);
            banks.push_back(bank);
            initializeBankAccounts(bank);
        }
    }

    void SystemInitializer::initializeATMs()
    {
        std::cout << "\n"
                  << ui.getLocalizedMessage("ENTER_NUM_ATMS");
        int numATMs;
        while (!(std::cin >> numATMs) || numATMs <= 0)
        {
            ui.displayMessage("ENTER_VALID_NUMBER");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore();

        for (int i = 0; i < numATMs; i++)
        {
            std::string serial = generateSerialNumber();

            // Get ATM type
            int typeChoice;
            do
            {
                std::string prompt = ui.getLocalizedMessage("ATM_TYPE_PROMPT");
                size_t pos = prompt.find("{}");
                prompt.replace(pos, 2, std::to_string(i + 1));
                std::cout << prompt;
                std::cin >> typeChoice;
                if (typeChoice != 1 && typeChoice != 2)
                {
                    ui.displayMessage("INVALID_CHOICE");
                }
            } while (typeChoice != 1 && typeChoice != 2);
            BankType bankType = (typeChoice == 1) ? BankType::SINGLE_BANK : BankType::MULTI_BANK;

            // Language selection
            int langChoice;
            do
            {
                std::cout << "Language support (1: Unilingual, 2: Bilingual): ";
                std::cin >> langChoice;
                if (langChoice != 1 && langChoice != 2)
                {
                    ui.displayMessage("INVALID_CHOICE");
                }
            } while (langChoice != 1 && langChoice != 2);
            LanguageSupport langSupport = (langChoice == 1) ? LanguageSupport::UNILINGUAL : LanguageSupport::BILINGUAL;

            // Primary bank selection
            ui.displayMessage("AVAILABLE_BANKS");
            for (size_t j = 0; j < banks.size(); j++)
            {
                std::cout << (j + 1) << ". " << banks[j]->getName() << "\n";
            }

            int bankChoice;
            do
            {
                std::string prompt = ui.getLocalizedMessage("SELECT_PRIMARY_BANK");
                size_t pos = prompt.find("{}");
                prompt.replace(pos, 2, std::to_string(banks.size()));
                std::cout << prompt;
                std::cin >> bankChoice;
                if (bankChoice < 1 || bankChoice > static_cast<int>(banks.size()))
                {
                    ui.displayMessage("INVALID_CHOICE");
                }
            } while (bankChoice < 1 || bankChoice > static_cast<int>(banks.size()));
            bankChoice--;

            // Initialize cash inventory
            std::string message = ui.getLocalizedMessage("INIT_CASH");
            size_t pos = message.find("{}");
            message.replace(pos, 2, serial);
            std::cout << message << "\n";

            std::map<int, int> inventory;
            for (const auto &[denom, _] : VALID_DENOMINATIONS)
            {
                int count;
                do
                {
                    std::string prompt = ui.getLocalizedMessage("BILL_PROMPT");
                    pos = prompt.find("{}");
                    prompt.replace(pos, 2, std::to_string(denom));
                    std::cout << prompt;
                    std::cin >> count;
                    if (count < 0)
                    {
                        ui.displayMessage("ENTER_VALID_NUMBER");
                    }
                } while (count < 0);
                inventory[denom] = count;
            }

            auto atm = std::make_shared<ATM>(serial, bankType, langSupport, banks[bankChoice]);
            atm->addCash(inventory);

            if (bankType == BankType::MULTI_BANK)
            {
                for (const auto &bank : banks)
                {
                    if (bank != banks[bankChoice])
                    {
                        atm->addConnectedBank(bank);
                    }
                }
            }

            atms.push_back(atm);

            std::string successMsg = ui.getLocalizedMessage("ATM_CREATED");
            pos = successMsg.find("{}");
            successMsg.replace(pos, 2, serial);
            std::cout << successMsg << "\n";
        }
        std::cin.ignore();
    }

    void SystemInitializer::initializeBankAccounts(const std::shared_ptr<Bank> &bank)
    {
        int numUsers;
        bool validInput = false;

        do
        {
            std::string message = ui.getLocalizedMessage("ENTER_NUM_USERS");
            size_t pos = message.find("{}");
            message.replace(pos, 2, bank->getName());
            std::cout << message;

            if (std::cin >> numUsers && numUsers > 0)
            {
                validInput = true;
            }
            else
            {
                ui.displayMessage("ENTER_VALID_NUMBER");
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } while (!validInput);

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (int i = 0; i < numUsers; i++)
        {
            std::string prompt = ui.getLocalizedMessage("USER_NAME_PROMPT");
            size_t pos = prompt.find("{}");
            prompt.replace(pos, 2, std::to_string(i + 1));
            std::cout << prompt;

            std::string userName;
            std::getline(std::cin, userName);

            int numAccounts;
            validInput = false;

            do
            {
                std::string message = ui.getLocalizedMessage("NUM_ACCOUNTS_PROMPT");
                pos = message.find("{}");
                message.replace(pos, 2, userName);
                std::cout << message;

                if (std::cin >> numAccounts && numAccounts > 0)
                {
                    validInput = true;
                }
                else
                {
                    ui.displayMessage("ENTER_VALID_NUMBER");
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            } while (!validInput);

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            for (int j = 0; j < numAccounts; j++)
            {
                std::string accountNum;
                do
                {
                    accountNum = std::to_string(rand() % 1000000000000LL);
                    while (accountNum.length() < 12)
                    {
                        accountNum = "0" + accountNum;
                    }
                } while (bank->getAccount(accountNum) != nullptr);

                std::string pin;
                bool validPin = false;
                do
                {
                    std::string prompt = ui.getLocalizedMessage("ENTER_PIN_FOR_ACCOUNT");
                    pos = prompt.find("{}");
                    prompt.replace(pos, 2, accountNum);
                    std::cout << prompt;
                    std::getline(std::cin, pin);

                    if (pin.length() == 4 && std::all_of(pin.begin(), pin.end(), ::isdigit))
                    {
                        validPin = true;
                    }
                    else
                    {
                        ui.displayMessage("INVALID_PIN_FORMAT");
                    }
                } while (!validPin);

                if (bank->createAccount(userName, accountNum, pin))
                {
                    std::string successMsg = ui.getLocalizedMessage("ACCOUNT_CREATED");
                    pos = successMsg.find("{}");
                    successMsg.replace(pos, 2, accountNum);
                    pos = successMsg.find("{}");
                    successMsg.replace(pos, 2, userName);
                    std::cout << successMsg << "\n";
                }
                else
                {
                    ui.displayMessage("ACCOUNT_CREATION_FAILED");
                    j--;
                }
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

}