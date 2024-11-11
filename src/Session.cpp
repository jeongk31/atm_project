#include "Session.hpp"

namespace ATMSystem
{
    Session::Session(const std::string &card, std::shared_ptr<Account> acc)
        : cardNumber(card), account(acc), withdrawalCount(0) {}

    bool Session::addTransaction(const Transaction &transaction) { return true; }
    void Session::endSession() {}
    bool Session::canWithdraw() const { return withdrawalCount < 3; }
    void Session::printSessionSummary() const {}
}