#include "Transaction.hpp"
#include "UI.hpp"
#include <sstream>
#include <iomanip>

namespace ATMSystem
{
  Transaction::Transaction(const std::string &id, const std::string &card,
                           TransactionType transType, double amt,
                           double transactionFee, const std::string &transDetails)
      : transactionId(id), cardNumber(card), type(transType),
        amount(amt), fee(transactionFee), details(transDetails),
        timestamp(std::chrono::system_clock::now()) {}

  std::string Transaction::getTypeString() const
  {
    UI ui(false);
    switch (type)
    {
    case TransactionType::DEPOSIT:
      return ui.getLocalizedMessage("TRANSACTION_TYPE_DEPOSIT");
    case TransactionType::WITHDRAWAL:
      return ui.getLocalizedMessage("TRANSACTION_TYPE_WITHDRAWAL");
    case TransactionType::TRANSFER_CASH:
      return ui.getLocalizedMessage("TRANSACTION_TYPE_CASH_TRANSFER");
    case TransactionType::TRANSFER_ACCOUNT:
      return ui.getLocalizedMessage("TRANSACTION_TYPE_ACCOUNT_TRANSFER");
    default:
      return ui.getLocalizedMessage("TRANSACTION_TYPE_UNKNOWN");
    }
  }

  std::string Transaction::getFormattedTimestamp() const
  {
    UI ui(false);
    auto time = std::chrono::system_clock::to_time_t(timestamp);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), ui.getLocalizedMessage("TIMESTAMP_FORMAT").c_str());
    return ss.str();
  }
}