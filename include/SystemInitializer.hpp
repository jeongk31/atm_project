// include/SystemInitializer.hpp
#ifndef SYSTEM_INITIALIZER_HPP
#define SYSTEM_INITIALIZER_HPP

#include <vector>
#include <memory>
#include "ATM.hpp"
#include "Bank.hpp"
#include "Account.hpp"

namespace ATMSystem
{
    class SystemInitializer
    {
    private:
        std::vector<std::shared_ptr<ATM>> atms;
        std::vector<std::shared_ptr<Bank>> banks;

        // Private helper methods
        std::string generateSerialNumber();
        void initializeBanks();
        void initializeATMs();
        void initializeBankAccounts(const std::shared_ptr<Bank> &bank);

    public:
        SystemInitializer() = default;

        // Main initialization method
        void initializeSystem();

        // Getters
        const std::vector<std::shared_ptr<ATM>> &getATMs() const;
        const std::vector<std::shared_ptr<Bank>> &getBanks() const;
    };
}

#endif