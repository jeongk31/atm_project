#ifndef SYSTEM_SNAPSHOT_HPP
#define SYSTEM_SNAPSHOT_HPP

#include <memory>
#include <vector>
#include <string>
#include "ATM.hpp"
#include "Bank.hpp"

namespace ATMSystem
{

    class SystemSnapshot
    {
    private:
        const std::vector<std::shared_ptr<ATM>> &atms;
        const std::vector<std::shared_ptr<Bank>> &banks;

        // Helper methods
        std::string formatATMInfo(const std::shared_ptr<ATM> &atm) const;
        std::string formatCashInventory(const std::map<int, int> &inventory) const;
        std::string formatAccountInfo(const std::shared_ptr<Account> &account, const std::string &bankName) const;

    public:
        SystemSnapshot(const std::vector<std::shared_ptr<ATM>> &atms,
                       const std::vector<std::shared_ptr<Bank>> &banks)
            : atms(atms), banks(banks) {}

        void displaySnapshot() const;
    };

}

#endif