#include <iostream>
#include <string>
#include <unistd.h>

void sendInput(const std::string &input)
{
    std::cout << input << std::flush;
    write(STDOUT_FILENO, "\n", 1);
    usleep(200000); // 200ms delay for stability
}

int main()
{
    // Initial System Setup
    sendInput("2"); // Number of banks

    // Bank 1
    sendInput("bank1");
    sendInput("2"); // Users for bank1
    sendInput("user1");
    sendInput("1"); // Accounts for user1
    sendInput("user2");
    sendInput("1"); // Accounts for user2

    // Bank 2
    sendInput("bank2");
    sendInput("2"); // Users for bank2
    sendInput("user1");
    sendInput("1"); // Accounts for user1
    sendInput("user2");
    sendInput("1"); // Accounts for user2

    // ATM setup
    sendInput("2"); // Number of ATMs

    // First ATM - Single Bank
    sendInput("1");  // Single bank
    sendInput("1");  // Unilingual
    sendInput("1");  // Primary bank (bank1)
    sendInput("10"); // Cash inventory
    sendInput("10");
    sendInput("10");
    sendInput("10");

    // Second ATM - Multi Bank
    sendInput("2");  // Multi bank
    sendInput("2");  // Bilingual
    sendInput("2");  // Primary bank (bank2)
    sendInput("10"); // Cash inventory
    sendInput("10");
    sendInput("10");
    sendInput("10");

    // Start using the ATM
    sendInput("2"); // Select the multi-bank ATM (ATM 2)

    sendInput("1"); // Select English language

    // Use bank1's account (non-primary for ATM2)
    sendInput("000000016807"); // First account created for bank1/user1

    sendInput("1234"); // PIN

    // Test Deposit
    sendInput("1"); // Select Deposit
    sendInput("1"); // Cash deposit
    // Insert cash
    sendInput("5"); // 5 x 1000 won
    sendInput("3"); // 3 x 5000 won
    sendInput("2"); // 2 x 10000 won
    sendInput("1"); // 1 x 50000 won

    // Test Withdrawal
    sendInput("2");     // Select Withdraw
    sendInput("30000"); // Amount to withdraw

    // Test Transfer to primary bank account
    sendInput("3");            // Select Transfer
    sendInput("2");            // Account transfer
    sendInput("001622650073"); // Transfer to bank2/user1 account (primary bank)
    sendInput("20000");        // Transfer amount

    // Test Transfer to non-primary bank account
    sendInput("3");            // Select Transfer
    sendInput("2");            // Account transfer
    sendInput("000282475249"); // Transfer to another bank1 account
    sendInput("15000");        // Transfer amount

    // Test Cash Transfer
    sendInput("3");            // Select Transfer
    sendInput("1");            // Cash transfer
    sendInput("001622650073"); // Transfer to bank2 account
    // Insert cash
    sendInput("5"); // 5 x 1000 won
    sendInput("2"); // 2 x 5000 won
    sendInput("1"); // 1 x 10000 won
    sendInput("0"); // 0 x 50000 won

    // Exit
    sendInput("4"); // Quit

    close(STDOUT_FILENO);
    return 0;
}