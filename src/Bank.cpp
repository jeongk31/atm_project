// src/Bank.cpp
#include "Bank.hpp"

namespace ATMSystem
{

    Bank::Bank(const std::string &bankName) : name(bankName) {}

    bool Bank::createAccount(const std::string &userName, const std::string &accountNumber)
    {
        auto account = std::make_shared<Account>(name, userName, accountNumber);
        accounts[accountNumber] = account;
        userAccounts[userName].push_back(accountNumber);
        return true;
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

} // namespace ATMSystem