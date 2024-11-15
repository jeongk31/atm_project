#include "SystemSnapshot.hpp"
#include <sstream>
#include <iostream>

namespace ATMSystem
{

    std::string SystemSnapshot::formatCashInventory(const std::map<int, int> &inventory) const
    {
        UI ui(false);

        std::stringstream ss;
        ss << ui.getLocalizedMessage("CASH_INVENTORY_START");
        bool first = true;
        for (const auto &[denomination, count] : inventory)
        {
            if (!first)
                ss << ui.getLocalizedMessage("CASH_INVENTORY_SEPARATOR");

            std::string format = ui.getLocalizedMessage("CASH_INVENTORY_FORMAT");
            size_t pos = format.find("{}");
            format.replace(pos, 2, std::to_string(denomination));
            pos = format.find("{}");
            format.replace(pos, 2, std::to_string(count));
            ss << format;

            first = false;
        }
        ss << ui.getLocalizedMessage("CASH_INVENTORY_END");
        return ss.str();
    }

    std::string SystemSnapshot::formatATMInfo(const std::shared_ptr<ATM> &atm) const
    {
        UI ui(false);
        std::stringstream ss;
        std::string format = ui.getLocalizedMessage("ATM_INFO_FORMAT");

        size_t pos = format.find("{}");
        format.replace(pos, 2, atm->getSerialNumber());
        pos = format.find("{}");
        format.replace(pos, 2, formatCashInventory(atm->getCashInventory()));

        ss << format;
        return ss.str();
    }

    std::string SystemSnapshot::formatAccountInfo(const std::shared_ptr<Account> &account,
                                                  const std::string &bankName) const
    {
        UI ui(false);
        std::stringstream ss;
        std::string format = ui.getLocalizedMessage("ACCOUNT_INFO_FORMAT");

        size_t pos = format.find("{}");
        format.replace(pos, 2, bankName);
        pos = format.find("{}");
        format.replace(pos, 2, account->getAccountNumber());
        pos = format.find("{}");
        format.replace(pos, 2, account->getUserName());
        pos = format.find("{}");
        format.replace(pos, 2, std::to_string(account->getBalance()));

        ss << format;
        return ss.str();
    }

    void SystemSnapshot::displaySnapshot() const
    {
        UI ui(false);

        // Display ATM info
        std::cout << "\n=== " << ui.getLocalizedMessage("ATM_SNAPSHOT") << " ===\n";
        bool firstAtm = true;
        for (const auto &atm : atms)
        {
            if (!firstAtm)
            {
                std::cout << ",\n";
            }
            std::cout << formatATMInfo(atm);
            firstAtm = false;
        }

        // Display Account info
        std::cout << "\n\n=== " << ui.getLocalizedMessage("ACCOUNT_SNAPSHOT") << " ===\n";
        bool firstAccount = true;
        for (const auto &bank : banks)
        {
            for (const auto &account : bank->getAllAccounts())
            {
                if (!firstAccount)
                {
                    std::cout << ",\n";
                }
                std::cout << formatAccountInfo(account, bank->getName());
                firstAccount = false;
            }
        }
        std::cout << "\n"
                  << std::endl;
    }

}