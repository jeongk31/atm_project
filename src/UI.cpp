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
        return "Message not found / 메시지를 찾을 수 없습니다";
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

    void UI::showDisplayPanel(const std::string &messageKey) const
    {
        std::cout << "\n----------------------------------------\n";
        std::cout << getLocalizedMessage(messageKey);
        std::cout << "\n----------------------------------------\n";
    }

    std::string UI::getKeypadInput() const
    {
        return getInput();
    }

    bool UI::processCardInsertion()
    {
        showDisplayPanel("INSERT_CARD");
        return true;
    }

    std::map<int, int> UI::getCashInput() const
    {
        std::map<int, int> cashInput;

        displayMessage("ENTER_BILLS");

        for (const auto &[denomination, _] : VALID_DENOMINATIONS)
        {
            std::string message = getLocalizedMessage("BILL_PROMPT");
            size_t pos = message.find("{}");
            if (pos != std::string::npos)
            {
                message.replace(pos, 2, std::to_string(denomination));
            }

            std::cout << message << " ";
            int count;
            std::cin >> count;
            if (count > 0)
            {
                cashInput[denomination] = count;
            }
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return cashInput;
    }

    void UI::showCashDispenser(const std::map<int, int> &cash) const
    {
        displayMessage("BILLS_BREAKDOWN");
        for (const auto &[denomination, count] : cash)
        {
            if (count > 0)
            {
                std::cout << count << " × KRW " << denomination << "\n";
            }
        }
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
}