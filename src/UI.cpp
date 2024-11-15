#include "UI.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

namespace ATMSystem
{
    UI::UI(bool bilingual) : isBilingual(bilingual), isKorean(false) {}

    std::string UI::getLocalizedMessage(const std::string &key) const
    {
        auto it = messages.find(key);
        if (it != messages.end())
        {
            return isKorean ? it->second.second : it->second.first;
        }
        return getLocalizedMessage("MESSAGE_NOT_FOUND");
    }

    void UI::displayMessage(const std::string &messageKey) const
    {
        std::cout << "\n"
                  << getLocalizedMessage(messageKey) << std::endl;
    }

    void UI::setLanguage(bool korean)
    {
        isKorean = korean;
    }

    void UI::displayMenu() const
    {
        displayMessage("SELECT_SERVICE");
    }

    std::string UI::getInput() const
    {
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    bool UI::processCardInsertion()
    {
        showDisplayPanel("INSERT_CARD");
        std::string cardNumber = getInput();

        if (cardNumber.length() != 12)
        {
            displayMessage("INVALID_CARD");
            return false;
        }
        return true;
    }

    void UI::showDisplayPanel(const std::string &messageKey) const
    {
        std::string border = getLocalizedMessage("SYSTEM_BORDER");
        std::cout << "\n"
                  << border << "\n";
        std::cout << getLocalizedMessage(messageKey);
        std::cout << "\n"
                  << border << "\n";
    }

    std::string UI::getKeypadInput() const
    {
        return getInput();
    }

    std::map<int, int> UI::getCashInput() const
    {
        std::map<int, int> cashInput;
        int totalBills = 0;

        displayMessage("ENTER_BILLS");

        for (const auto &[denomination, _] : VALID_DENOMINATIONS)
        {
            int count;
            do
            {
                std::string message = getLocalizedMessage("BILL_PROMPT");
                size_t pos = message.find("{}");
                if (pos != std::string::npos)
                {
                    message.replace(pos, 2, std::to_string(denomination));
                }
                std::cout << message << " ";

                if (!(std::cin >> count) || count < 0)
                {
                    std::cout << getLocalizedMessage("INVALID_AMOUNT") << "\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }

                if (totalBills + count > MAX_CASH_INSERT)
                {
                    std::cout << getLocalizedMessage("MAX_DEPOSIT_EXCEEDED") << "\n";
                    continue;
                }
                break;
            } while (true);

            if (count > 0)
            {
                cashInput[denomination] = count;
                totalBills += count;
            }
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return cashInput;
    }

    void UI::showTransactionSummary(const std::vector<std::string> &summary) const
    {
        std::cout << "\n=== " << getLocalizedMessage("TRANSACTION_SUMMARY") << " ===\n";
        for (const auto &line : summary)
        {
            std::cout << line << "\n";
        }
        std::cout << getLocalizedMessage("THANK_YOU") << std::endl;
    }

    void UI::printReceipt(const std::vector<std::string> &transactionDetails) const
    {
        std::cout << "\n=== " << getLocalizedMessage("TRANSACTION_SUMMARY") << " ===\n";
        for (const auto &detail : transactionDetails)
        {
            std::cout << detail << "\n";
        }
        std::cout << getLocalizedMessage("THANK_YOU") << std::endl;
    }

    void UI::showCashDispenser(const std::map<int, int> &cash) const
    {
        displayMessage("BILLS_BREAKDOWN");
        for (const auto &[denomination, count] : cash)
        {
            if (count > 0)
            {
                std::string format = getLocalizedMessage("BILL_FORMAT");
                size_t pos = format.find("{}");
                format.replace(pos, 2, std::to_string(count));
                pos = format.find("{}");
                format.replace(pos, 2, std::to_string(denomination));
                std::cout << format << "\n";
            }
        }
    }
}