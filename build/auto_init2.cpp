#include <iostream>
#include <string>
#include <unistd.h>

void sendInput(const std::string &input)
{
    std::cout << input << std::flush;
    write(STDOUT_FILENO, "\n", 1);
    usleep(300000); // 300ms delay for stability
}

int main()
{
    // Initial System Setup
    sendInput("2"); // Number of banks

    // Bank 1 (한국은행)
    sendInput("한국은행");
    sendInput("2"); // Users for 한국은행
    sendInput("홍길동");
    sendInput("1");    // Accounts for 홍길동
    sendInput("1234"); // PIN for 홍길동's account
    sendInput("김철수");
    sendInput("1");    // Accounts for 김철수
    sendInput("5678"); // PIN for 김철수's account

    // Bank 2 (신한은행)
    sendInput("신한은행");
    sendInput("1"); // Users for 신한은행
    sendInput("이영희");
    sendInput("1");    // Accounts for 이영희
    sendInput("1111"); // PIN for 이영희's account

    // ATM Setup
    sendInput("2"); // Number of ATMs

    // First ATM - Bilingual, Single Bank
    sendInput("1");  // Single bank
    sendInput("2");  // Bilingual
    sendInput("1");  // Primary bank (한국은행)
    sendInput("50"); // Cash inventory
    sendInput("50");
    sendInput("50");
    sendInput("50");

    // Second ATM - Bilingual, Multi Bank
    sendInput("2");   // Multi bank
    sendInput("2");   // Bilingual
    sendInput("2");   // Primary bank (신한은행)
    sendInput("100"); // Cash inventory
    sendInput("100");
    sendInput("100");
    sendInput("100");

    // TEST 1: Language Selection and Cash Deposit
    sendInput("1");            // First ATM
    sendInput("2");            // Select Korean language
    sendInput("000000016807"); // Login with 홍길동's account
    sendInput("1234");         // PIN
    sendInput("/");            // Check initial snapshot
    sendInput("1");            // Deposit (입금)
    sendInput("1");            // Cash deposit (현금 입금)
    // Input cash
    sendInput("5"); // 5 × 1000 won
    sendInput("3"); // 3 × 5000 won
    sendInput("2"); // 2 × 10000 won
    sendInput("1"); // 1 × 50000 won
    // Fee payment
    sendInput("1"); // 1 × 1000 won fee
    sendInput("0");
    sendInput("0");
    sendInput("0");
    sendInput("/"); // Check snapshot after deposit
    sendInput("4"); // Exit (종료)

    // TEST 2: Check Deposit with Korean Interface
    sendInput("1");            // First ATM
    sendInput("2");            // Select Korean
    sendInput("000000016807"); // Login with 홍길동's account
    sendInput("1234");         // PIN
    sendInput("1");            // Deposit (입금)
    sendInput("2");            // Check deposit (수표 입금)
    sendInput("150000");       // Valid check amount
    // Fee payment
    sendInput("1"); // 1 × 1000 won fee
    sendInput("0");
    sendInput("0");
    sendInput("0");
    sendInput("/"); // Check snapshot
    sendInput("4"); // Exit

    // TEST 3: Account Transfer with Korean Interface
    sendInput("2");            // Second ATM (Multi-bank)
    sendInput("2");            // Select Korean
    sendInput("000282475249"); // Login with 김철수's account
    sendInput("5678");         // PIN
    sendInput("3");            // Transfer (이체)
    sendInput("2");            // Account transfer (계좌 이체)
    sendInput("000000016807"); // To 홍길동's account
    sendInput("50000");        // Transfer amount
    sendInput("/");            // Check snapshot
    sendInput("4");            // Exit

    // TEST 4: Edge Case - Wrong PIN in Korean
    sendInput("1");            // First ATM
    sendInput("2");            // Select Korean
    sendInput("000000016807"); // Login with 홍길동's account
    sendInput("9999");         // Wrong PIN
    sendInput("9999");         // Wrong PIN again
    sendInput("9999");         // Wrong PIN third time
    sendInput("4");            // Exit

    // TEST 5: Edge Case - Maximum Withdrawals in Korean
    sendInput("2");            // Second ATM
    sendInput("2");            // Select Korean
    sendInput("000000016807"); // Login with 홍길동's account
    sendInput("1234");         // PIN
    sendInput("2");            // Withdrawal (출금)
    sendInput("10000");        // First withdrawal
    sendInput("2");            // Withdrawal
    sendInput("10000");        // Second withdrawal
    sendInput("2");            // Withdrawal
    sendInput("10000");        // Third withdrawal
    sendInput("2");            // Try fourth withdrawal (should fail with Korean message)
    sendInput("10000");
    sendInput("/"); // Check snapshot
    sendInput("4"); // Exit

    // TEST 6: Invalid Check Amount in Korean
    sendInput("1");            // First ATM
    sendInput("2");            // Select Korean
    sendInput("000000016807"); // Login with 홍길동's account
    sendInput("1234");         // PIN
    sendInput("1");            // Deposit
    sendInput("2");            // Check deposit
    sendInput("50000");        // Invalid check amount (below 100,000)
    sendInput("4");            // Exit

    // TEST 7: Cash Transfer with Insufficient Fee in Korean
    sendInput("2");            // Second ATM
    sendInput("2");            // Select Korean
    sendInput("000000016807"); // Login with 홍길동's account
    sendInput("1234");         // PIN
    sendInput("3");            // Transfer
    sendInput("1");            // Cash transfer
    sendInput("000282475249"); // To 김철수's account
    // Input transfer cash
    sendInput("5"); // 5 × 1000 won
    sendInput("1"); // 1 × 5000 won
    sendInput("0");
    sendInput("0");
    // Insufficient fee payment
    sendInput("0"); // Try to pay no fee
    sendInput("0");
    sendInput("0");
    sendInput("0");
    sendInput("4"); // Exit

    // TEST 8: Maximum Cash Insert Limit in Korean
    sendInput("1");            // First ATM
    sendInput("2");            // Select Korean
    sendInput("000000016807"); // Login with 홍길동's account
    sendInput("1234");         // PIN
    sendInput("1");            // Deposit
    sendInput("1");            // Cash deposit
    // Try to insert more than 50 bills
    sendInput("51"); // 51 × 1000 won (exceeds limit)
    sendInput("0");
    sendInput("0");
    sendInput("0");
    sendInput("/"); // Check snapshot
    sendInput("4"); // Exit

    // TEST 9: Admin View in Korean
    sendInput("1");            // First ATM
    sendInput("2");            // Select Korean
    sendInput("999999999999"); // Admin card
    sendInput("1");            // View transaction history

    // TEST 10: Switch Language Mid-Session
    sendInput("2");            // Second ATM
    sendInput("2");            // Start with Korean
    sendInput("000000016807"); // Login with 홍길동's account
    sendInput("1234");         // PIN
    sendInput("2");            // Withdrawal
    sendInput("20000");        // Withdraw some money
    sendInput("1");            // Switch to English
    sendInput("2");            // Another withdrawal
    sendInput("30000");        // Withdraw some more
    sendInput("/");            // Check snapshot
    sendInput("4");            // Exit

    sendInput("q"); // Quit program

    close(STDOUT_FILENO);
    return 0;
}