#include <iostream>
#include <memory>
#include <iomanip>
#include "SystemInitializer.hpp"
#include "UI.hpp"
#include "ATM.hpp"
#include "Bank.hpp"
#include "SystemSnapshot.hpp"

using namespace ATMSystem;

std::string formatCurrency(int amount)
{
    std::string str = std::to_string(amount);
    int pos = str.length() - 3;
    while (pos > 0)
    {
        str.insert(pos, ",");
        pos -= 3;
    }
    return "KRW " + str;
}

void displayHorizontalLine(int length = 50)
{
    std::cout << "\n"
              << std::string(length, '#') << "\n\n";
}

void handleATMSelection(UI &ui, const std::vector<std::shared_ptr<ATM>> &atms, std::string &atmChoice)
{
    std::string prompt = ui.getLocalizedMessage("SELECT_ATM");
    size_t pos = prompt.find("{}");
    prompt.replace(pos, 2, std::to_string(atms.size()));
    std::cout << prompt;
    atmChoice = ui.getInput();
}

void displayTransferOptions(UI &ui, std::string &transferType)
{
    ui.displayMessage("TRANSFER_TYPE");
    transferType = ui.getInput();

    if (transferType != "1" && transferType != "2")
    {
        ui.displayMessage("INVALID_CHOICE");
    }
}

void handleTransferAmount(UI &ui, int &amount, bool &shouldContinue)
{
    ui.displayMessage("TRANSFER_AMOUNT");
    if (!(std::cin >> amount))
    {
        ui.displayMessage("INVALID_AMOUNT");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        shouldContinue = false;
        return;
    }
    std::cin.ignore();
    shouldContinue = true;
}

void displayTransferResult(UI &ui, int transferredAmount, int fee, const std::string &destAccountNum, double newBalance)
{
    ui.displayMessage("TRANSFER_SUCCESS");
    std::cout << ui.getLocalizedMessage("AMOUNT") << " " << formatCurrency(transferredAmount) << "\n";
    std::cout << ui.getLocalizedMessage("FEE_LABEL") << " " << formatCurrency(fee) << "\n";
    std::cout << ui.getLocalizedMessage("NEW_BALANCE_LABEL") << " " << formatCurrency(newBalance) << "\n";
}

void displayCashBreakdown(UI &ui, const std::map<int, int> &bills)
{
    ui.displayMessage("BILLS_BREAKDOWN");
    for (const auto &[denom, count] : bills)
    {
        if (count > 0)
        {
            std::cout << count << " × " << formatCurrency(denom) << "\n";
        }
    }
}

bool processDepositFee(UI &ui, const std::shared_ptr<ATM> &atm, bool isPrimaryBank)
{
    int fee = isPrimaryBank ? TransactionFees::DEPOSIT_PRIMARY : TransactionFees::DEPOSIT_NON_PRIMARY;

    std::string message = ui.getLocalizedMessage("DEPOSIT_FEE_REQUIRED");
    size_t pos = message.find("{}");
    message.replace(pos, 2, formatCurrency(fee));
    std::cout << message << "\n";

    ui.displayMessage("ENTER_FEE_CASH");

    auto feeInput = ui.getCashInput();
    int totalFeeInput = 0;
    for (const auto &[denom, count] : feeInput)
    {
        totalFeeInput += denom * count;
    }

    if (totalFeeInput < fee)
    {
        ui.displayMessage("INSUFFICIENT_FEE");
        return false;
    }

    atm->addCash(feeInput);
    return true;
}

void displayAvailableATMs(const std::vector<std::shared_ptr<ATM>> &atms, UI &ui)
{
    ui.displayMessage("AVAILABLE_ATMS");
    for (size_t i = 0; i < atms.size(); i++)
    {
        const auto &atm = atms[i];
        std::string message = ui.getLocalizedMessage("ATM_LIST_ENTRY");
        size_t pos;

        pos = message.find("{}");
        message.replace(pos, 2, std::to_string(i + 1));

        pos = message.find("{}");
        message.replace(pos, 2, atm->getSerialNumber());

        pos = message.find("{}");
        message.replace(pos, 2, atm->getBankType() == BankType::SINGLE_BANK ? "Single" : "Multi");

        pos = message.find("{}");
        message.replace(pos, 2, atm->getPrimaryBank()->getName());

        std::cout << message << "\n";
    }
    ui.displayMessage("QUIT_PROMPT");
}

void displaySessionSummary(const std::shared_ptr<Session> &session,
                           const std::string &cardNumber,
                           const std::shared_ptr<Bank> &cardBank,
                           const std::vector<std::string> &transactionLog,
                           const std::shared_ptr<Account> &userAccount,
                           UI &ui)
{
    ui.displayMessage("SESSION_SUMMARY_HEADER");

    std::string sessionMsg = ui.getLocalizedMessage("SESSION_ID");
    size_t pos = sessionMsg.find("{}");
    sessionMsg.replace(pos, 2, session->getSessionId());
    std::cout << sessionMsg << "\n";

    std::cout << ui.getLocalizedMessage("CARD_NUMBER_LABEL") << " " << cardNumber << "\n";
    std::cout << ui.getLocalizedMessage("BANK_LABEL") << " " << cardBank->getName() << "\n";

    auto startTime = session->getStartTime();
    auto endTime = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::minutes>(endTime - startTime).count();

    std::string durationMsg = ui.getLocalizedMessage("SESSION_DURATION");
    pos = durationMsg.find("{}");
    durationMsg.replace(pos, 2, std::to_string(duration));
    std::cout << durationMsg << "\n\n";

    for (const auto &transaction : transactionLog)
    {
        std::cout << transaction << "\n";
    }
    std::cout << "\n=================\n";

    std::string balanceMsg = ui.getLocalizedMessage("FINAL_BALANCE");
    pos = balanceMsg.find("{}");
    balanceMsg.replace(pos, 2, formatCurrency(userAccount->getBalance()));
    std::cout << balanceMsg << "\n";
}

bool handleDepositFee(UI &ui, const std::shared_ptr<ATM> &atm, bool isPrimaryBank, int &totalFeeInput)
{
    int fee = isPrimaryBank ? TransactionFees::DEPOSIT_PRIMARY : TransactionFees::DEPOSIT_NON_PRIMARY;

    std::string message = ui.getLocalizedMessage("DEPOSIT_FEE_REQUIRED");
    size_t pos = message.find("{}");
    message.replace(pos, 2, formatCurrency(fee));
    std::cout << message << "\n";

    ui.displayMessage("ENTER_FEE_CASH");
    auto feeInput = ui.getCashInput();
    totalFeeInput = 0;

    for (const auto &[denom, count] : feeInput)
    {
        totalFeeInput += denom * count;
    }

    if (totalFeeInput < fee)
    {
        ui.displayMessage("INSUFFICIENT_FEE");
        return false;
    }

    // Only handle change once
    if (totalFeeInput > fee)
    {
        int change = totalFeeInput - fee;
        std::string changeMsg = ui.getLocalizedMessage("CHANGE_AMOUNT");
        pos = changeMsg.find("{}");
        changeMsg.replace(pos, 2, formatCurrency(change));
        std::cout << changeMsg << "\n";

        ui.displayMessage("TAKE_CHANGE");
        std::string response = ui.getInput();
        if (response != "y" && response != "Y")
        {
            ui.displayMessage("CANCEL_TRANSACTION");
            return false;
        }

        // Adjust the totalFeeInput to exactly match the fee
        totalFeeInput = fee;
    }

    atm->addCash(feeInput);
    return true;
}

void handleWithdrawalInput(UI &ui, int &amount, bool &shouldContinue)
{

    std::string prompt = ui.getLocalizedMessage("WITHDRAWAL_AMOUNT");
    size_t pos = prompt.find("{}");
    // prompt.replace(pos, 2, formatCurrency(MAX_WITHDRAWAL_PER_TRANSACTION));
    std::cout << prompt;

    if (!(std::cin >> amount))
    {
        ui.displayMessage("INVALID_AMOUNT");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        shouldContinue = false;
        return;
    }
    std::cin.ignore();

    if (amount <= 0)
    {
        ui.displayMessage("INVALID_AMOUNT");
        shouldContinue = false;
        return;
    }

    if (amount > MAX_WITHDRAWAL_PER_TRANSACTION)
    {

        ui.displayMessage("MAX_WITHDRAWAL_EXCEEDED");
        shouldContinue = false;
        return;
    }
    shouldContinue = true;
}

std::string formatTransactionLog(UI &ui, const std::string &typeKey, int amount, int fee, const std::string &destAccount = "")
{
    std::string logEntry = ui.getLocalizedMessage(typeKey) + ": " + formatCurrency(amount) + " (" + ui.getLocalizedMessage("FEE_LABEL") + " " + formatCurrency(fee) + ")";
    if (!destAccount.empty())
    {
        logEntry += " " + ui.getLocalizedMessage("TO") + " " + destAccount;
    }
    return logEntry;
}

int main()
{
    try
    {
        // initialize system
        UI ui(false);
        SystemInitializer initializer(ui);
        initializer.initializeSystem();

        // Get available ATMs
        const auto &atms = initializer.getATMs();
        const auto &banks = initializer.getBanks();

        bool programRunning = true;

        while (programRunning)
        {
            UI ui(false);
            displayAvailableATMs(atms, ui);

            // ATM selection with error handling
            std::string atmChoice;
            do
            {
                handleATMSelection(ui, atms, atmChoice);

                if (atmChoice == "/")
                {
                    SystemSnapshot snapshot(atms, banks);
                    snapshot.displaySnapshot();
                    continue;
                }

                if (atmChoice == "q" || atmChoice == "Q")
                {
                    programRunning = false;
                    ui.displayMessage("GOODBYE");
                    return 0;
                }

                try
                {
                    int choice = std::stoi(atmChoice);
                    if (choice < 1 || choice > static_cast<int>(atms.size()))
                    {
                        ui.displayMessage("INVALID_CHOICE");
                        continue;
                    }
                    atmChoice = std::to_string(choice);
                    break;
                }
                catch (...)
                {
                    ui.displayMessage("INVALID_CHOICE");
                }
            } while (true);

            auto selectedATM = atms[std::stoi(atmChoice) - 1];
            ui = UI(selectedATM->getLanguageSupport() == LanguageSupport::BILINGUAL);

            if (selectedATM->getLanguageSupport() == LanguageSupport::BILINGUAL)
            {
                ui.displayMessage("SELECT_LANGUAGE");
                std::string langChoice;
                bool validChoice = false;

                do
                {
                    langChoice = ui.getInput();
                    if (langChoice == "1" || langChoice == "2")
                    {
                        validChoice = true;
                        bool isKorean = (langChoice == "2");
                        ui.setLanguage(isKorean);
                        selectedATM->setLanguage(isKorean); // true for Korean, false for English
                    }
                    else
                    {
                        ui.displayMessage("INVALID_CHOICE");
                    }
                } while (!validChoice);
            }

            ui.displayMessage("WELCOME");

            // Card input + validation
            std::string cardNumber;
            std::shared_ptr<Bank> cardBank;
            std::shared_ptr<Account> userAccount;
            bool validCard = false;

            do
            {
                ui.showDisplayPanel("INSERT_CARD");
                cardNumber = ui.getInput();
                if (cardNumber.length() != 12)
                {
                    ui.displayMessage("INVALID_CARD");
                    continue;
                }

                if (selectedATM->isAdminCard(cardNumber))
                {
                    ui.displayMessage("ADMIN_DETECTED");
                    selectedATM->startSession(cardNumber, nullptr); // admin session
                    selectedATM->displayAdminMenu(ui);
                    break;
                }

                // find bank and account for card
                for (const auto &bank : banks)
                {
                    auto account = bank->getAccount(cardNumber);
                    if (account)
                    {
                        cardBank = bank;
                        userAccount = account;
                        break;
                    }
                }

                if (!userAccount)
                {
                    ui.displayMessage("INVALID_CARD");
                    continue;
                }

                // Validate card based on ATM type
                if (selectedATM->getBankType() == BankType::SINGLE_BANK)
                {
                    if (cardBank == selectedATM->getPrimaryBank())
                    {
                        validCard = true;
                    }
                    else
                    {
                        std::string message = ui.getLocalizedMessage("SINGLE_BANK_ONLY");
                        size_t pos = message.find("{}");
                        message.replace(pos, 2, selectedATM->getPrimaryBank()->getName());
                        std::cout << message << "\n";
                    }
                }
                else
                {
                    validCard = true;
                }
            } while (!validCard);

            if (selectedATM->isAdminCard(cardNumber))
            {
                continue;
            }

            // PIN validation
            int pinAttempts = 0;
            bool validPin = false;
            do
            {
                ui.displayMessage("ENTER_PIN");
                std::string pin = ui.getInput();

                if (pin.length() != 4)
                {
                    ui.displayMessage("INVALID_PIN_FORMAT");
                    pinAttempts++;
                }
                else
                {
                    validPin = selectedATM->validatePin(cardNumber, pin, pinAttempts);
                }

                if (pinAttempts >= ATMSystem::ATM::MAX_PIN_ATTEMPTS)
                {
                    ui.displayMessage("CARD_RETAINED");
                    return 1;
                }
            } while (!validPin && pinAttempts < ATMSystem::ATM::MAX_PIN_ATTEMPTS);

            if (!validPin)
            {
                return 1;
            }

            selectedATM->startSession(cardNumber, userAccount);

            // Main transaction loop
            bool running = true;
            std::vector<std::string> transactionLog;

            while (running)
            {
                displayHorizontalLine();

                ui.displayMenu();
                std::string choice = ui.getInput();

                if (choice == "/")
                {
                    SystemSnapshot snapshot(atms, banks);
                    snapshot.displaySnapshot();
                    continue;
                }

                if (choice.empty() || (choice[0] != '1' && choice[0] != '2' &&
                                       choice[0] != '3' && choice[0] != '4'))
                {
                    ui.displayMessage("INVALID_CHOICE");
                    continue;
                }

                switch (choice[0])
                {
                case '1': // Deposit
                {
                    ui.displayMessage("SELECT_DEPOSIT_TYPE");
                    std::string depositType = ui.getInput();

                    if (depositType != "1" && depositType != "2")
                    {
                        ui.displayMessage("INVALID_CHOICE");
                        continue;
                    }

                    if (depositType == "1")
                    { // Cash deposit
                        ui.displayMessage("ENTER_CASH_DEPOSIT");
                        auto cashInput = ui.getCashInput();
                        int depositAmount = 0;
                        for (const auto &[denom, count] : cashInput)
                        {
                            depositAmount += denom * count;
                        }

                        if (depositAmount <= 0)
                        {
                            ui.displayMessage("INVALID_AMOUNT");
                            continue;
                        }

                        int depositedAmount;
                        int fee;
                        int totalFeeInput = 0;

                        // Calculate fee
                        if (selectedATM->deposit(cardNumber, depositAmount, true, depositedAmount, fee))
                        {
                            if (!handleDepositFee(ui, selectedATM, cardBank == selectedATM->getPrimaryBank(), totalFeeInput))
                            {
                                userAccount->withdraw(depositAmount);
                                continue;
                            }

                            selectedATM->addCash(cashInput);
                            ui.displayMessage("DEPOSIT_SUCCESS");
                            std::cout << ui.getLocalizedMessage("AMOUNT_DEPOSITED") << " " << formatCurrency(depositAmount) << "\n";
                            std::cout << ui.getLocalizedMessage("FEE_LABEL") << " " << formatCurrency(fee) << "\n";
                            std::cout << ui.getLocalizedMessage("NEW_BALANCE_LABEL") << " " << formatCurrency(userAccount->getBalance()) << "\n";

                            transactionLog.push_back(formatTransactionLog(ui, "CASH_DEPOSIT_TYPE", depositAmount, fee));
                        }
                    }
                    else
                    { // Check deposit
                        int checkAmount;
                        std::string checkPrompt = ui.getLocalizedMessage("CHECK_PROMPT");
                        size_t pos = checkPrompt.find("{}");
                        checkPrompt.replace(pos, 2, formatCurrency(MIN_CHECK_AMOUNT));
                        std::cout << checkPrompt;
                        if (!(std::cin >> checkAmount))
                        {
                            ui.displayMessage("INVALID_CHECK_INPUT");
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            continue;
                        }
                        std::cin.ignore();

                        if (checkAmount < MIN_CHECK_AMOUNT)
                        {
                            std::string message = ui.getLocalizedMessage("INVALID_CHECK_AMOUNT");
                            size_t pos = message.find("{}");
                            message.replace(pos, 2, formatCurrency(MIN_CHECK_AMOUNT));
                            std::cout << message << "\n";
                            continue;
                        }

                        int depositedAmount;
                        int fee;

                        // calculate fee
                        if (selectedATM->deposit(cardNumber, checkAmount, false, depositedAmount, fee))
                        {
                            std::string feeMsg = ui.getLocalizedMessage("TRANSACTION_FEE");
                            pos = feeMsg.find("{}");
                            feeMsg.replace(pos, 2, formatCurrency(fee));
                            std::cout << feeMsg << "\n";
                            ui.displayMessage("ENTER_FEE_CASH");
                            auto feeInput = ui.getCashInput();
                            int totalFeeInput = 0;
                            for (const auto &[denom, count] : feeInput)
                            {
                                totalFeeInput += denom * count;
                            }

                            if (totalFeeInput < fee)
                            {
                                ui.displayMessage("INSUFFICIENT_FEE");
                                continue;
                            }

                            if (totalFeeInput > fee)
                            {
                                int change = totalFeeInput - fee;
                                std::string changeMsg = ui.getLocalizedMessage("CHANGE_AMOUNT");
                                size_t pos = changeMsg.find("{}");
                                changeMsg.replace(pos, 2, formatCurrency(change));
                                std::cout << changeMsg << "\n";
                                ui.displayMessage("TAKE_CHANGE");
                                std::string response;
                                std::getline(std::cin, response);
                                if (response != "y" && response != "Y")
                                {
                                    ui.displayMessage("CANCEL_TRANSACTION");
                                    continue;
                                }
                            }

                            selectedATM->addCash(feeInput);
                            ui.displayMessage("CHECK_DEPOSIT_SUCCESS");
                            std::cout << ui.getLocalizedMessage("AMOUNT_DEPOSITED") << " " << formatCurrency(checkAmount) << "\n";
                            std::cout << ui.getLocalizedMessage("FEE_LABEL") << " " << formatCurrency(fee) << "\n";
                            std::cout << ui.getLocalizedMessage("NEW_BALANCE_LABEL") << " " << formatCurrency(userAccount->getBalance()) << "\n";

                            transactionLog.push_back(formatTransactionLog(ui, "CHECK_DEPOSIT_TYPE", checkAmount, fee));
                        }
                    }
                    break;
                }

                case '2': // Withdraw
                {
                    if (!selectedATM->getCurrentSession()->canWithdraw())
                    {
                        std::string message = ui.getLocalizedMessage("WITHDRAWAL_MAX_REACHED");
                        size_t pos = message.find("{}");
                        message.replace(pos, 2, std::to_string(MAX_WITHDRAWALS_PER_SESSION));
                        std::cout << message << "\n";
                        continue;
                    }

                    int amount;
                    bool shouldContinue;
                    handleWithdrawalInput(ui, amount, shouldContinue);
                    if (!shouldContinue)
                        continue;

                    int withdrawnAmount;
                    int fee;
                    std::map<int, int> bills;
                    if (!selectedATM->withdraw(cardNumber, amount, withdrawnAmount, fee, bills))
                    {

                        // insufficient cash
                        if (!selectedATM->hasActiveSession())
                        {
                            running = false;
                            break;
                        }
                        continue;
                    }

                    ui.displayMessage("WITHDRAWAL_SUCCESS");
                    displayCashBreakdown(ui, bills);
                    std::cout << ui.getLocalizedMessage("FEE_LABEL") << " " << formatCurrency(fee) << "\n";
                    std::cout << ui.getLocalizedMessage("NEW_BALANCE_LABEL") << " " << formatCurrency(userAccount->getBalance()) << "\n";

                    transactionLog.push_back(formatTransactionLog(ui, "WITHDRAWAL_TYPE", withdrawnAmount, fee));
                    break;
                }

                case '3':
                { // Transfer
                    std::string transferType;
                    displayTransferOptions(ui, transferType);

                    if (transferType != "1" && transferType != "2")
                    {
                        ui.displayMessage("INVALID_CHOICE");
                        continue;
                    }

                    ui.displayMessage("TRANSFER_ACCOUNT");
                    std::string destAccountNum = ui.getInput();

                    if (transferType == "1")
                    { // Cash transfer
                        int transferAmount;
                        auto cashInput = ui.getCashInput();

                        for (const auto &[denom, count] : cashInput)
                        {
                            transferAmount += denom * count;
                        }

                        int transferredAmount;
                        int fee;

                        fee = TransactionFees::TRANSFER_CASH;
                        std::string feeMsg = ui.getLocalizedMessage("TRANSACTION_FEE");
                        size_t pos = feeMsg.find("{}");
                        feeMsg.replace(pos, 2, formatCurrency(fee));
                        std::cout << feeMsg << "\n";
                        ui.displayMessage("ENTER_FEE_CASH");
                        auto feeInput = ui.getCashInput();
                        int totalFeeInput = 0;
                        for (const auto &[denom, count] : feeInput)
                        {
                            totalFeeInput += denom * count;
                        }

                        if (totalFeeInput < fee)
                        {
                            ui.displayMessage("INSUFFICIENT_FEE");
                            continue;
                        }

                        // change if too much fee was provided
                        if (totalFeeInput > fee)
                        {
                            int change = totalFeeInput - fee;
                            std::string changeMsg = ui.getLocalizedMessage("CHANGE_AMOUNT");
                            size_t pos = changeMsg.find("{}");
                            changeMsg.replace(pos, 2, formatCurrency(change));
                            std::cout << changeMsg << "\n";
                            ui.displayMessage("TAKE_CHANGE");
                            std::string response;
                            std::getline(std::cin, response);
                            if (response != "y" && response != "Y")
                            {
                                ui.displayMessage("CANCEL_TRANSACTION");
                                continue;
                            }
                        }

                        if (selectedATM->transfer(cardNumber, destAccountNum, transferAmount, true, transferredAmount, fee))
                        {
                            // Add to ATM's inventory
                            selectedATM->addCash(cashInput);
                            selectedATM->addCash(feeInput);
                            ui.displayMessage("CASH_TRANSFER_SUCCESS");
                            std::cout << ui.getLocalizedMessage("AMOUNT_TRANSFERRED") << " " << formatCurrency(transferredAmount) << "\n";
                            std::cout << ui.getLocalizedMessage("FEE_LABEL") << " " << formatCurrency(fee) << "\n";

                            transactionLog.push_back(formatTransactionLog(ui, "CASH_TRANSFER_TYPE", transferredAmount, fee, destAccountNum));
                        }
                    }
                    else
                    { // Account transfer
                        int amount;
                        ui.displayMessage("TRANSFER_AMOUNT");
                        if (!(std::cin >> amount))
                        {
                            ui.displayMessage("INVALID_AMOUNT");
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            continue;
                        }
                        std::cin.ignore();

                        int transferredAmount;
                        int fee;
                        if (selectedATM->transfer(cardNumber, destAccountNum, amount, false, transferredAmount, fee))
                        {
                            ui.displayMessage("ACCOUNT_TRANSFER_SUCCESS");
                            std::cout << ui.getLocalizedMessage("AMOUNT_TRANSFERRED") << " " << formatCurrency(transferredAmount) << "\n";
                            std::cout << ui.getLocalizedMessage("FEE_LABEL") << " " << formatCurrency(fee) << "\n";
                            std::cout << ui.getLocalizedMessage("NEW_BALANCE_LABEL") << " " << formatCurrency(userAccount->getBalance()) << "\n";

                            transactionLog.push_back(formatTransactionLog(ui, "ACCOUNT_TRANSFER_TYPE", transferredAmount, fee, destAccountNum));
                        }
                    }
                    break;
                }

                case '4': // Exit
                    // transaction summary
                    if (!transactionLog.empty())
                    {
                        displaySessionSummary(selectedATM->getCurrentSession(),
                                              cardNumber, cardBank,
                                              transactionLog, userAccount,
                                              ui);
                    }
                    selectedATM->endCurrentSession();
                    displayHorizontalLine(60);
                    displayHorizontalLine(60);
                    std::cout << "\n\n\n";
                    running = false;
                    break;

                default:
                    ui.displayMessage("INVALID_CHOICE");
                }
            }
        }
        return 0;
    }
    catch (const std::exception &e)
    {
    }
}