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

        std::map<std::string, std::pair<std::string, std::string>> messages = {
            // Basic UI messages
            {"WELCOME", {"Welcome to ATM Service", "ATM 서비스에 오신 것을 환영합니다"}},
            {"SELECT_LANGUAGE", {"Select Language (1: English, 2: Korean)", "언어 선택 (1: 영어, 2: 한국어)"}},
            {"INSERT_CARD", {"Please insert your card (Enter card number):", "카드를 넣어주세요 (카드 번호 입력):"}},
            {"ENTER_PIN", {"Enter your PIN:", "비밀번호를 입력하세요:"}},
            {"INVALID_CARD", {"Invalid card number length. Please enter a 12-digit account number.", "잘못된 카드 번호입니다. 12자리 계좌번호를 입력해주세요."}},
            {"WRONG_PIN", {"Wrong PIN.", "잘못된 비밀번호입니다."}},
            {"SELECT_SERVICE", {"Select Service:\n1. Deposit\n2. Withdraw\n3. Transfer\n4. Exit", "서비스 선택:\n1. 입금\n2. 출금\n3. 이체\n4. 종료"}},
            {"AMOUNT", {"Amount:", "금액:"}},
            {"FEE_LABEL", {"Fee:", "수수료:"}},
            {"NEW_BALANCE_LABEL", {"New balance:", "새로운 잔액:"}},

            // Cash handling messages
            {"ENTER_BILLS", {"Enter number of bills for each denomination:", "권종별 지폐 수량을 입력하세요:"}},
            {"BILL_PROMPT", {"KRW {} bills: ", "{} 원권 지폐 수:"}},
            {"BILLS_BREAKDOWN", {"Bills breakdown:", "지폐 내역:"}},
            {"CASH_INSUFFICIENT", {"ATM does not have sufficient cash.", "ATM에 현금이 부족합니다."}},
            {"MAX_DEPOSIT_EXCEEDED", {"Maximum number of bills (50) exceeded for this deposit.", "이번 입금의 지폐 수가 최대 한도(50)를 초과했습니다."}},
            {"MAX_CHECK_DEPOSIT_EXCEEDED", {"Maximum number of checks (50) per session reached.", "세션당 수표 입금 한도(50)에 도달했습니다."}},
            {"SELECT_DEPOSIT_TYPE", {"Select deposit type:\n1. Cash\n2. Check", "입금 유형 선택:\n1. 현금\n2. 수표"}},
            {"ENTER_CASH_DEPOSIT", {"Enter cash to deposit:", "입금할 현금을 넣어주세요:"}},

            // Withdrawal messages
            {"WITHDRAWAL_AMOUNT", {"Enter amount to withdraw:", "출금하실 금액을 입력하세요:"}},
            {"WITHDRAWAL_SUCCESS", {"Withdrawal successful!", "출금이 완료되었습니다!"}},
            {"MAX_WITHDRAWAL_EXCEEDED", {"Amount exceeds maximum withdrawal limit of KRW 500,000", "출금 한도 500,000원을 초과하였습니다"}},
            {"WITHDRAWAL_MAX_REACHED", {"Maximum withdrawals per session ({}) reached.", "세션당 최대 출금 횟수({})에 도달했습니다."}},

            // Transfer messages
            {"TRANSFER_TYPE", {"Select transfer type:\n1. Cash Transfer\n2. Account Transfer", "이체 유형 선택:\n1. 현금 이체\n2. 계좌 이체"}},
            {"TRANSFER_ACCOUNT", {"Enter destination account (12 digits):", "이체할 계좌번호 (12자리)를 입력하세요:"}},
            {"SOURCE_ACCOUNT", {"Enter source account (12 digits):", "출금할 계좌번호 (12자리)를 입력하세요:"}},
            {"TRANSFER_AMOUNT", {"Enter amount to transfer:", "이체할 금액을 입력하세요:"}},
            {"TRANSFER_SUCCESS", {"Transfer successful!", "이체가 완료되었습니다!"}},

            // Account and balance messages
            {"INVALID_ACCOUNT", {"Invalid account number. Please enter a 12-digit number.", "잘못된 계좌번호입니다. 12자리 번호를 입력해주세요."}},
            {"INSUFFICIENT_FUNDS", {"Insufficient funds!", "잔액이 부족합니다!"}},
            {"FINAL_BALANCE", {"Final Balance: {}", "최종 잔액: {}"}},

            // Transaction messages
            {"TRANSACTION_COMPLETE", {"Transaction complete!", "거래가 완료되었습니다!"}},
            {"TRANSACTION_CANCELLED", {"Transaction cancelled.", "거래가 취소되었습니다."}},
            {"TRANSACTION_SUMMARY", {"Transaction Summary", "거래내역 요약"}},
            {"DEPOSITED", {"Deposited:", "입금 내역:"}},
            {"DEPOSIT_SUCCESS", {"Deposit successful!", "입금이 완료되었습니다!"}},
            {"PROCESSING", {"Processing transaction...", "거래를 처리중입니다..."}},

            // Fee related messages
            {"INSERT_FEE", {"Please insert transaction fee:", "거래 수수료를 넣어주세요:"}},
            {"ENTER_FEE_CASH", {"Please insert cash for transaction fee:", "거래 수수료를 넣어주세요:"}},
            {"INSUFFICIENT_FEE", {"Insufficient fee amount. Transaction cancelled.", "수수료가 부족합니다. 거래가 취소되었습니다."}},

            // Receipt and confirmation messages
            {"WANT_RECEIPT", {"Would you like a receipt? (Y/N):", "영수증이 필요하십니까? (Y/N):"}},
            {"CONFIRM_AMOUNT", {"Confirm amount (Y/N):", "금액이 맞습니까? (Y/N):"}},
            {"TAKE_CHANGE", {"Press 'y' to take change:", "거스름돈을 받으시려면 'y'를 누르세요:"}},

            // Session messages
            {"SESSION_TIMEOUT", {"Session timed out. Please try again.", "세션이 만료되었습니다. 다시 시도해주세요."}},
            {"SESSION_END", {"Ending session...", "세션을 종료합니다..."}},
            {"SESSION_SUMMARY_HEADER", {"=== Session Summary ===", "=== 세션 요약 ==="}},
            {"SESSION_ID", {"Session ID: {}", "세션 ID: {}"}},
            {"SESSION_DURATION", {"Session Duration: {} minutes", "세션 지속 시간: {}분"}},

            // Admin messages
            {"ADMIN_MENU", {"Admin Menu:\n1. View Transaction History\n2. Exit", "관리자 메뉴:\n1. 거래내역 조회\n2. 종료"}},
            {"ADMIN_DETECTED", {"Admin card detected. Accessing admin menu...", "관리자 카드가 감지되었습니다. 관리자 메뉴에 접속중..."}},
            {"EXPORT_SUCCESS", {"Transaction history has been exported to: ", "거래 내역이 다음 파일로 내보내졌습니다: "}},

            // Card related messages
            {"CARD_RETAINED", {"Your card has been retained. Please contact your bank.", "카드가 회수되었습니다. 은행에 문의하세요."}},
            {"MAX_ATTEMPTS_EXCEEDED", {"Maximum PIN attempts exceeded. Card retained.", "비밀번호 입력 횟수 초과. 카드가 회수되었습니다."}},

            // System initialization messages
            {"SYSTEM_INIT", {"=== ATM System Initialization ===", "=== ATM 시스템 초기화 ==="}},
            {"ENTER_NUM_BANKS", {"Enter number of banks to create: ", "생성할 은행 수를 입력하세요: "}},
            {"BANK_NAME_PROMPT", {"Bank {} name: ", "{}번 은행 이름: "}},
            {"ENTER_VALID_NUMBER", {"Please enter a valid number greater than 0: ", "0보다 큰 올바른 숫자를 입력하세요: "}},
            {"SYSTEM_INIT_COMPLETE", {"System initialization completed!", "시스템 초기화가 완료되었습니다!"}},

            // ATM setup messages
            {"ENTER_NUM_ATMS", {"Enter number of ATMs to create: ", "생성할 ATM 수를 입력하세요: "}},
            {"ATM_TYPE_PROMPT", {"ATM {} type (1: Single Bank, 2: Multi-Bank): ", "ATM {} 유형 (1: 단일 은행, 2: 다중 은행): "}},
            {"AVAILABLE_BANKS", {"Available banks:", "사용 가능한 은행:"}},
            {"SELECT_PRIMARY_BANK", {"Select primary bank (1-{}): ", "주 은행을 선택하세요 (1-{}): "}},
            {"INIT_CASH", {"Initialize cash inventory for ATM {}:", "ATM {}의 현금 재고 초기화:"}},
            {"ATM_CREATED", {"ATM {} created successfully!", "ATM {} 가 성공적으로 생성되었습니다!"}},

            // Account setup messages
            {"ENTER_NUM_USERS", {"Enter number of users for {}: ", "{}의 사용자 수를 입력하세요: "}},
            {"USER_NAME_PROMPT", {"User {} name: ", "{}번 사용자 이름: "}},
            {"NUM_ACCOUNTS_PROMPT", {"Number of accounts for {}: ", "{}의 계좌 수: "}},
            {"ENTER_PIN_FOR_ACCOUNT", {"Enter 4-digit PIN for account {}: ", "계좌 {}의 4자리 PIN을 입력하세요: "}},
            {"ACCOUNT_CREATED", {"Created account {} for {}", "{}의 계좌 {} 가 생성되었습니다"}},
            {"INVALID_PIN_FORMAT", {"Invalid PIN format. PIN must be 4 digits.", "잘못된 PIN 형식입니다. PIN은 4자리 숫자여야 합니다."}},

            // ATM selection messages
            {"AVAILABLE_ATMS", {"Available ATMs:", "사용 가능한 ATM:"}},
            {"ATM_LIST_ENTRY", {"{}. ATM {} ({}-Bank, Primary: {})", "{}. ATM {} ({} 은행, 주 은행: {})"}},
            {"SELECT_ATM", {"Select ATM (1-{}) or 'q' to quit: ", "ATM을 선택하세요 (1-{}) 또는 종료하려면 'q': "}},
            {"QUIT_PROMPT", {"Enter 'q' to quit the program", "프로그램을 종료하려면 'q'를 입력하세요"}},
            {"GOODBYE", {"Thank you for using our ATM system. Goodbye!", "ATM 시스템을 이용해 주셔서 감사합니다. 안녕히 가세요!"}},

            // Transaction history messages
            {"TRANSACTION_HISTORY_HEADER", {"=== Transaction History ===", "=== 거래 내역 ==="}},
            {"TRANSACTION_ID_HEADER", {"Transaction ID", "거래 ID"}},
            {"CARD_NUMBER_HEADER", {"Card Number", "카드 번호"}},
            {"TYPE_HEADER", {"Type", "유형"}},
            {"AMOUNT_HEADER", {"Amount", "금액"}},
            {"FEE_HEADER", {"Fee", "수수료"}},
            {"TIMESTAMP_HEADER", {"Timestamp", "시간"}},
            {"DETAILS_HEADER", {"Details", "상세 내용"}},
            {"TRANSACTION_HEADER", {"Transaction History", "거래 내역"}},

            // System snapshot messages
            {"SYSTEM_SNAPSHOT", {"=== System Snapshot ===", "=== 시스템 스냅샷 ==="}},
            {"ATM_SNAPSHOT", {"=== ATM Snapshot ===", "=== ATM 스냅샷 ==="}},
            {"ACCOUNT_SNAPSHOT", {"=== Account Snapshot ===", "=== 계좌 스냅샷 ==="}},
            {"ATM_INFO", {"ATM [SN: {}] remaining cash: {}", "ATM [일련번호: {}] 남은 현금: {}"}},
            {"ACCOUNT_INFO", {"Account [Bank: {}, No: {}, Owner: {}] balance: {}", "계좌 [은행: {}, 번호: {}, 소유자: {}] 잔액: {}"}},

            // General messages
            {"INVALID_CHOICE", {"Invalid choice. Please try again.", "잘못된 선택입니다. 다시 시도해주세요."}},
            {"INVALID_AMOUNT", {"Please enter a valid amount.", "올바른 금액을 입력해주세요."}},
            {"PLEASE_WAIT", {"Please wait...", "잠시만 기다려주세요..."}},

            // Bank-specific messages
            {"SINGLE_BANK_ONLY", {"This ATM only accepts cards from {}", "이 ATM은 {} 은행의 카드만 사용 가능합니다"}},
            {"PRIMARY_BANK", {"Primary Bank", "주 거래 은행"}},
            {"NON_PRIMARY_BANK", {"Non-Primary Bank", "비주거래 은행"}},

            // Additional transaction details
            {"CHECK_MIN_AMOUNT", {"Enter check amount (minimum {} KRW): ", "수표 금액을 입력하세요 (최소 {} 원): "}},
            {"INVALID_CHECK_AMOUNT", {"Invalid check amount. Minimum is {} KRW", "잘못된 수표 금액입니다. 최소 금액은 {} 원입니다"}},
            {"CHANGE_AMOUNT", {"Change amount: {} KRW", "거스름돈: {} 원"}},

            // Error messages
            {"ERROR_INSUFFICIENT_CASH", {"Error: ATM has insufficient cash", "오류: ATM에 현금이 부족합니다"}},
            {"ERROR_SYSTEM", {"System Error: {}", "시스템 오류: {}"}},
            {"ERROR_INVALID_OPERATION", {"Invalid operation", "잘못된 작업"}},
            {"CANCEL_TRANSACTION", {"Transaction cancelled.", "거래가 취소되었습니다."}},

            // For check deposit
            {"CHECK_PROMPT", {"Enter check amount (minimum KRW {}):", "수표 금액을 입력하세요 (최소 {} 원):"}},
            {"INVALID_CHECK_INPUT", {"Invalid input.", "잘못된 입력입니다."}},

            // For transaction status
            {"TRANSACTION_FEE", {"Transaction fee: KRW {}", "거래 수수료: {} 원"}},
            {"DEPOSIT_FEE_REQUIRED", {"Deposit fee required: KRW {}", "입금 수수료가 필요합니다: {} 원"}},
            {"CASH_TRANSFER_SUCCESS", {"Cash transfer successful!", "현금 이체가 완료되었습니다!"}},
            {"ACCOUNT_TRANSFER_SUCCESS", {"Account transfer successful!", "계좌 이체가 완료되었습니다!"}},
            {"CHECK_DEPOSIT_SUCCESS", {"Check deposit successful!", "수표 입금이 완료되었습니다!"}},

            // For session summary
            {"CARD_NUMBER_LABEL", {"Card Number:", "카드 번호:"}},
            {"BANK_LABEL", {"Bank:", "은행:"}},

            // additional
            {"AMOUNT_DEPOSITED", {"Amount deposited:", "입금액:"}},
            {"AMOUNT_TRANSFERRED", {"Amount transferred:", "이체액:"}},
            {"CASH_DEPOSIT_TYPE", {"Cash Deposit", "현금 입금"}},
            {"CHECK_DEPOSIT_TYPE", {"Check Deposit", "수표 입금"}},
            {"WITHDRAWAL_TYPE", {"Withdrawal", "출금"}},
            {"CASH_TRANSFER_TYPE", {"Cash Transfer", "현금 이체"}},
            {"ACCOUNT_TRANSFER_TYPE", {"Account Transfer", "계좌 이체"}},
            {"TO", {"to", "to"}},
            {"ATTEMPTS_REMAINING", {"Attempts remaining: {}", "남은 시도 횟수: {}"}},
            {"FROM", {"From", "보낸 사람"}},
            {"SYSTEM_BORDER", {"----------------------------------------", "----------------------------------------"}},
            {"BILL_FORMAT", {"{} × KRW {}", "{} × {} 원"}},
            {"SYSTEM_INIT_HEADER", {"=== ATM System Initialization ===", "=== ATM 시스템 초기화 ==="}},
            {"BANK_NAME_PROMPT", {"Bank {} name:", "{}번 은행 이름:"}},
            {"ATM_CREATION_PROMPT", {"Enter number of ATMs to create:", "생성할 ATM 수를 입력하세요:"}},
            {"ENTER_VALID_POSITIVE", {"Please enter a valid number greater than 0:", "0보다 큰 올바른 숫자를 입력하세요:"}},
            {"ATM_TYPE_PROMPT", {"ATM {} type (1: Single Bank, 2: Multi-Bank):", "ATM {} 유형 (1: 단일 은행, 2: 다중 은행):"}},
            {"INVALID_TYPE_CHOICE", {"Invalid choice. Please enter 1 or 2.", "잘못된 선택입니다. 1 또는 2를 입력하세요."}},
            {"LANG_SUPPORT_PROMPT", {"Language support (1: Unilingual, 2: Bilingual):", "언어 지원 (1: 단일 언어, 2: 이중 언어):"}},
            {"SELECT_PRIMARY_BANK", {"Select primary bank (1-{}):", "주 은행을 선택하세요 (1-{}):"}},
            {"INVALID_BANK_CHOICE", {"Invalid choice. Please select a number between 1 and {}", "잘못된 선택입니다. 1과 {} 사이의 숫자를 선택하세요."}},
            {"INIT_CASH_INVENTORY", {"Initialize cash inventory for ATM {}:", "ATM {}의 현금 재고 초기화:"}},
            {"ENTER_BILLS_COUNT", {"Enter number of {} KRW bills:", "{} 원권 지폐 수를 입력하세요:"}},
            {"ENTER_NON_NEGATIVE", {"Please enter a non-negative number.", "0 이상의 숫자를 입력하세요."}},
            {"ATM_CREATION_SUCCESS", {"ATM {} created successfully!", "ATM {}가 성공적으로 생성되었습니다!"}},
            {"ENTER_USER_COUNT", {"Enter number of users for {}:", "{}의 사용자 수를 입력하세요:"}},
            {"USER_NAME_PROMPT", {"User {} name:", "{}번 사용자 이름:"}},
            {"ACCOUNT_COUNT_PROMPT", {"Number of accounts for {}:", "{}의 계좌 수:"}},
            {"PIN_PROMPT", {"Enter 4-digit PIN for account {}:", "계좌 {}의 4자리 PIN을 입력하세요:"}},
            {"INVALID_PIN_FORMAT", {"Invalid PIN format. PIN must be exactly 4 digits.", "잘못된 PIN 형식입니다. PIN은 정확히 4자리여야 합니다."}},
            {"ACCOUNT_CREATION_SUCCESS", {"Created account {} for {}", "{}의 계좌 {}가 생성되었습니다"}},
            {"ACCOUNT_CREATION_FAILED", {"Failed to create account. Please try again.", "계좌 생성에 실패했습니다. 다시 시도해주세요."}},
            {"SYSTEM_INIT_COMPLETE", {"System initialization completed!", "시스템 초기화가 완료되었습니다!"}},
            {"MESSAGE_NOT_FOUND", {"Message not found", "메시지를 찾을 수 없습니다"}},
            {"SYSTEM_ERROR_LOG", {"Session ended: {}", "세션 종료됨: {}"}},
            {"MAX_PIN_EXCEEDED", {"Maximum PIN attempts exceeded", "최대 PIN 시도 횟수 초과"}},
            {"INSUFFICIENT_CASH_ERROR", {"insufficient cash", "현금 부족"}},
            {"CARD_ERROR", {"card error", "카드 오류"}},
            {"SYSTEM_ERROR", {"system error", "시스템 오류"}},
            {"CASH_INVENTORY_START", {"{", "{"}},
            {"CASH_INVENTORY_END", {"}", "}"}},
            {"CASH_INVENTORY_SEPARATOR", {", ", ", "}},
            {"CASH_INVENTORY_FORMAT", {"KRW {} : {}", "{}원 : {}"}},
            {"ATM_INFO_FORMAT", {"ATM [SN: {}] remaining cash: {}", "ATM [일련번호: {}] 남은 현금: {}"}},
            {"ACCOUNT_INFO_FORMAT", {"Account [Bank: {}, No: {}, Owner: {}] balance: {}", "계좌 [은행: {}, 계좌번호: {}, 소유자: {}] 잔액: {}"}},
            {"TRANSACTION_TYPE_DEPOSIT", {"Deposit", "입금"}},
            {"TRANSACTION_TYPE_WITHDRAWAL", {"Withdrawal", "출금"}},
            {"TRANSACTION_TYPE_CASH_TRANSFER", {"Cash Transfer", "현금 이체"}},
            {"TRANSACTION_TYPE_ACCOUNT_TRANSFER", {"Account Transfer", "계좌 이체"}},
            {"TRANSACTION_TYPE_UNKNOWN", {"Unknown", "알 수 없음"}},
            {"TIMESTAMP_FORMAT", {"%Y-%m-%d %H:%M:%S", "%Y년 %m월 %d일 %H시 %M분 %S초"}},
        };

    public:
        UI &operator=(const UI &other)
        {
            isBilingual = other.isBilingual;
            isKorean = other.isKorean;
            return *this;
        }

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
        std::string getLocalizedMessage(const std::string &key) const;

        void printReceipt(const std::vector<std::string> &transactionDetails) const;
    };
}

#endif