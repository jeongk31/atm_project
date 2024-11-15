#include "Session.hpp"
#include "ATM.hpp"
#include "Account.hpp"
#include "UI.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

namespace ATMSystem
{
    std::atomic<uint64_t> Session::nextTransactionId{0};

    Session::Session(const std::string &card, std::shared_ptr<Account> acc, std::shared_ptr<ATM> atmPtr)
        : cardNumber(card), account(acc), atm(atmPtr),
          startTime(std::chrono::system_clock::now()), isActive(true),
          withdrawalCount(0), checkDepositCount(0)
    {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        sessionId = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
    }

    std::string Session::generateTransactionId()
    {
        auto now = std::chrono::system_clock::now();
        auto now_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&now_t), "%Y%m%d-%H%M%S-");
        ss << std::setfill('0') << std::setw(6) << nextTransactionId++;
        return ss.str();
    }

    std::string Session::addTransaction(TransactionType type, double amount, double fee, const std::string &details)
    {
        if (!isActive)
            return "";

        std::string transId = generateTransactionId();
        Transaction transaction(transId, cardNumber, type, amount, fee, details);
        transactions.push_back(transaction);

        // add to ATM's global transaction history
        if (auto atmPtr = atm.lock())
        {
            atmPtr->addToHistory(transaction);
        }

        return transId;
    }

    void Session::endSession(const std::string &reason)
    {
        if (!isActive)
            return;

        isActive = false;
        status.lastError = reason;

        // log session end if needed
        if (!reason.empty())
        {
            UI ui(false);
            std::string message = ui.getLocalizedMessage("SYSTEM_ERROR_LOG");
            size_t pos = message.find("{}");
            if (pos != std::string::npos)
            {
                message.replace(pos, 2, reason);
            }
            std::cout << message << std::endl;
        }
    }

    void Session::endSessionWithError(const std::string &error)
    {
        UI ui(false);
        status.lastError = error;

        // set appropriate error
        if (error.find(ui.getLocalizedMessage("INSUFFICIENT_FUNDS")) != std::string::npos)
        {
            status.insufficientFunds = true;
        }
        else if (error.find(ui.getLocalizedMessage("INSUFFICIENT_CASH_ERROR")) != std::string::npos)
        {
            status.insufficientCash = true;
        }
        else if (error.find(ui.getLocalizedMessage("CARD_ERROR")) != std::string::npos)
        {
            status.cardError = true;
        }
        else
        {
            status.systemError = true;
        }

        endSession(error);
    }

}