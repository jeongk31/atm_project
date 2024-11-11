// include/UI.hpp
#ifndef UI_HPP
#define UI_HPP

#include <string>
#include <map>
#include "Constants.hpp"

namespace ATMSystem
{
    class UI
    {
    protected:
        bool isBilingual;
        bool isKorean;

        // Messages in different languages
        std::map<std::string, std::pair<std::string, std::string>> messages = {
            {"WELCOME", {"Welcome to ATM Service", "ATM 서비스에 오신 것을 환영합니다"}},
            {"SELECT_LANGUAGE", {"Select Language (1: English, 2: Korean)", "언어 선택 (1: 영어, 2: 한국어)"}},
            {"INSERT_CARD", {"Please insert your card (Enter card number):", "카드를 넣어주세요 (카드 번호 입력):"}},
            {"ENTER_PIN", {"Enter your PIN:", "비밀번호를 입력하세요:"}},
            {"INVALID_CARD", {"Invalid card number length. Please enter a 12-digit account number.", "잘못된 카드 번호입니다. 12자리 계좌번호를 입력해주세요."}},
            {"WRONG_PIN", {"Wrong PIN.", "잘못된 비밀번호입니다."}},
            {"SELECT_SERVICE", {"Select Service:\n1. Deposit\n2. Withdraw\n3. Transfer\n4. Exit", "서비스 선택:\n1. 입금\n2. 출금\n3. 이체\n4. 종료"}},
            {"ENTER_BILLS", {"Enter number of bills for each denomination:", "권종별 지폐 수량을 입력하세요:"}},
            {"BILL_PROMPT", {"KRW {} bills:", "{} 원권 지폐 수:"}},
            {"WITHDRAWAL_AMOUNT", {"Enter amount to withdraw:", "출금하실 금액을 입력하세요:"}},
            {"INSUFFICIENT_FUNDS", {"Insufficient funds!", "잔액이 부족합니다!"}},
            {"TRANSFER_TYPE", {"Select transfer type:\n1. Cash Transfer\n2. Account Transfer", "이체 유형 선택:\n1. 현금 이체\n2. 계좌 이체"}},
            {"TRANSFER_ACCOUNT", {"Enter destination account (12 digits):", "이체할 계좌번호 (12자리)를 입력하세요:"}},
            {"SOURCE_ACCOUNT", {"Enter source account (12 digits):", "출금할 계좌번호 (12자리)를 입력하세요:"}},
            {"TRANSFER_AMOUNT", {"Enter amount to transfer:", "이체할 금액을 입력하세요:"}},
            {"INVALID_ACCOUNT", {"Invalid account number. Please enter a 12-digit number.", "잘못된 계좌번호입니다. 12자리 번호를 입력해주세요."}},
            {"TRANSACTION_COMPLETE", {"Transaction complete!", "거래가 완료되었습니다!"}},
            {"DEPOSITED", {"Deposited:", "입금 내역:"}},
            {"WITHDRAWAL_SUCCESS", {"Withdrawal successful!", "출금이 완료되었습니다!"}},
            {"BILLS_BREAKDOWN", {"Bills breakdown:", "지폐 내역:"}},
            {"NEW_BALANCE", {"New balance:", "현재 잔액:"}},
            {"FEE", {"Fee:", "수수료:"}},
            {"WANT_RECEIPT", {"Would you like a receipt? (Y/N):", "영수증이 필요하십니까? (Y/N):"}},
            {"TRANSACTION_SUMMARY", {"Transaction Summary", "거래내역 요약"}},
            {"THANK_YOU", {"Thank you for using our ATM service!", "ATM 서비스를 이용해주셔서 감사합니다!"}},
            {"DEPOSIT_SUCCESS", {"Deposit successful!", "입금이 완료되었습니다!"}},
            {"TRANSFER_SUCCESS", {"Transfer successful!", "이체가 완료되었습니다!"}},
            {"MAX_WITHDRAWAL_EXCEEDED", {"Amount exceeds maximum withdrawal limit of KRW 500,000", "출금 한도 500,000원을 초과하였습니다"}},
            {"INVALID_AMOUNT", {"Please enter a valid amount.", "올바른 금액을 입력해주세요."}},
            {"SESSION_TIMEOUT", {"Session timed out. Please try again.", "세션이 만료되었습니다. 다시 시도해주세요."}},
            {"CARD_RETAINED", {"Your card has been retained. Please contact your bank.", "카드가 회수되었습니다. 은행에 문의하세요."}},
            {"CASH_INSUFFICIENT", {"ATM does not have sufficient cash.", "ATM에 현금이 부족합니다."}},
            {"MAX_ATTEMPTS_EXCEEDED", {"Maximum PIN attempts exceeded. Card retained.", "비밀번호 입력 횟수 초과. 카드가 회수되었습니다."}},
            {"ADMIN_MENU", {"Admin Menu:\n1. View Transaction History\n2. Exit", "관리자 메뉴:\n1. 거래내역 조회\n2. 종료"}},
            {"INSERT_FEE", {"Please insert transaction fee:", "거래 수수료를 넣어주세요:"}},
            {"CONFIRM_AMOUNT", {"Confirm amount (Y/N):", "금액이 맞습니까? (Y/N):"}},
            {"PROCESSING", {"Processing transaction...", "거래를 처리중입니다..."}},
            {"CANCEL_TRANSACTION", {"Transaction cancelled.", "거래가 취소되었습니다."}},
            {"SESSION_END", {"Ending session...", "세션을 종료합니다..."}},
            {"INVALID_CHOICE", {"Invalid choice. Please try again.", "잘못된 선택입니다. 다시 시도해주세요."}},
            {"PLEASE_WAIT", {"Please wait...", "잠시만 기다려주세요..."}}};

        std::string getLocalizedMessage(const std::string &key) const;

    public:
        explicit UI(bool bilingual);
        virtual ~UI() = default;

        virtual void displayMessage(const std::string &messageKey) const;
        void displayMenu() const;
        std::string getInput() const;
        void setLanguage(bool korean);

        void showDisplayPanel(const std::string &message) const;
        std::string getKeypadInput() const;
        bool processCardInsertion();
        void showTransactionSummary(const std::vector<std::string> &summary) const;

        std::map<int, int> getCashInput() const;
        void showCashDispenser(const std::map<int, int> &cash) const;

        void printReceipt(const std::vector<std::string> &transactionDetails) const;
    };
}

#endif