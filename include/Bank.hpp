#ifndef BANK_HPP
#define BANK_HPP

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "Account.hpp"

namespace ATMSystem
{
    class Bank : public std::enable_shared_from_this<Bank>
    {
    private:
        std::string name;
        std::map<std::string, std::shared_ptr<Account>> accounts;
        std::map<std::string, std::vector<std::string>> userAccounts;

    public:
        explicit Bank(const std::string &bankName);

        // Account management
        bool createAccount(const std::string &userName, const std::string &accountNumber);
        std::shared_ptr<Account> getAccount(const std::string &accountNumber);
        std::vector<std::string> getUserAccounts(const std::string &userName);

        // Getters
        std::string getName() const { return name; }
    };
}

#endif // BANK_HPP