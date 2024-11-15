#include "Bank.hpp"
#include "UI.hpp"
#include <iostream>

namespace ATMSystem
{
    Bank::Bank(const std::string &bankName) : name(bankName) {}

    bool Bank::createAccount(const std::string &userName, const std::string &accountNumber, const std::string &pin)
    {
        UI ui(false);

        // validate PIN format
        if (pin.length() != 4 || !std::all_of(pin.begin(), pin.end(), ::isdigit))
        {
            ui.displayMessage("INVALID_PIN_FORMAT");
            return false;
        }

        auto account = std::make_shared<Account>(shared_from_this(), userName, accountNumber, pin);
        accounts[accountNumber] = account;
        userAccounts[userName].push_back(accountNumber);
        return true;
    }

    bool Bank::verifyPIN(const std::string &accountNumber, const std::string &pin)
    {
        auto it = accounts.find(accountNumber);
        if (it != accounts.end())
        {
            return it->second->getPin() == pin;
        }
        return false;
    }

    std::shared_ptr<Account> Bank::getAccount(const std::string &accountNumber)
    {
        auto it = accounts.find(accountNumber);
        return (it != accounts.end()) ? it->second : nullptr;
    }

    std::vector<std::string> Bank::getUserAccounts(const std::string &userName)
    {
        auto it = userAccounts.find(userName);
        return (it != userAccounts.end()) ? it->second : std::vector<std::string>();
    }
}