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
    sendInput("2");  // Single bank
    sendInput("1");  // Unilingual
    sendInput("1");  // Primary bank (bank1)
    sendInput("10"); // Cash inventory
    sendInput("10");
    sendInput("10");
    sendInput("10");

    // Second ATM - Single Bank
    sendInput("2");  // Single bank
    sendInput("1");  // Unilingual
    sendInput("2");  // Primary bank (bank2)
    sendInput("10"); // Cash inventory
    sendInput("10");
    sendInput("10");
    sendInput("10");

    // Start using ATM
    sendInput("1"); // Select ATM 1 (Primary: bank1)

    // Use bank1's account (primary bank)
    sendInput("000000016807"); // First account of bank1/user1
    sendInput("1234");         // PIN

    // Test Deposit with primary bank
    sendInput("1"); // Select Deposit
    sendInput("1"); // Cash deposit
    // Insert cash
    sendInput("5"); // 5 x 1000 won = 5,000
    sendInput("3"); // 3 x 5000 won = 15,000
    sendInput("2"); // 2 x 10000 won = 20,000
    sendInput("1"); // 1 x 50000 won = 50,000
    // Total deposit: 90,000 won (fee: 1,000 won - primary bank)

    // Test Withdrawal from primary bank
    sendInput("2");     // Select Withdraw
    sendInput("30000"); // Amount to withdraw (fee: 1,000 won - primary bank)

    // Test Transfer to another primary bank account
    sendInput("3");            // Select Transfer
    sendInput("2");            // Account transfer
    sendInput("000282475249"); // Transfer to bank1/user2 account (primary to primary)
    sendInput("20000");        // Transfer amount (fee: 2,000 won - primary to primary)

    // Test Cash Transfer
    sendInput("3");            // Select Transfer
    sendInput("1");            // Cash transfer
    sendInput("000984943658"); // Transfer to bank1/user2
    // Insert cash
    sendInput("5"); // 5 x 1000 won = 5,000
    sendInput("2"); // 2 x 5000 won = 10,000
    sendInput("1"); // 1 x 10000 won = 10,000
    sendInput("0"); // 0 x 50000 won = 0
    // Total cash transfer: 25,000 won (fee: 1,000 won - fixed fee)

    // Test Transfer to non-primary bank
    sendInput("3");            // Select Transfer
    sendInput("2");            // Account transfer
    sendInput("000984943658"); // Transfer to bank2/user1 account
    sendInput("15000");        // Transfer amount

    // Exit
    sendInput("4"); // Quit

    close(STDOUT_FILENO);
    return 0;
}