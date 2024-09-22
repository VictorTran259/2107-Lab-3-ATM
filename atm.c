//Victor Tran, 9/5/22, CIS 2107
//Lab 3 ATM Machine
//Write a C Program for an ATM machine.

//The types of ATM transaction are:
//1. Balance.
//2. Cash withdrawal.
//3. Cash deposition.
//4. Quit.

//All ATM transactions (menu options) need to be implemented in terms of functions.
//You will call those functions based on the menu option.

// Initially, Nana has one checking account with a balance of $5000 with PIN number of 3014.
// Money amount validation:
//o Catch invalid numerical inputs (Negative numbers and Zeroes).
//o Users can enter numbers only.
//o Remember  any  ATM  has  numpad  only.  This  numpad  has  neither  letters  nor  special
//characters.
//o Don’t worry about entering other inputs rather than numbers for now.
//o I mean don’t worry what would happen if the user enters a string, a char, or a special
//characters instead of a number. We will discuss this later in another chapter.
//o In  short,  if  the  Nana  enters  wrong  amount,  ask  her  to  enter  amount  again,  after  3
//unsuccessful attempts, display an error message and terminate the program.
// PIN validation:
//o Nana has 3 attempts to enter PIN. After that the program logs them off, and end the
//program.
// Once Nana chooses to finish using the ATM, print out Thank You message and tell her the
//number of transactions she has made.
// All ATM transactions (menu options) need to be implemented in terms of functions.
//o You will call those functions based on the menu option.
// All ATM transactions have receipts, but it is up to the user to choose.
//o Use 1 for yes, and 2 for No.
//o The receipt is virtual. No need to display the receipt on screen.


// Balance:
//o Nothing special about it. Basically it prints out the balance.

// Cash withdrawal:
//o The limit is $1000 a day.
//o For every withdrawal transaction, there is a receipt.
//o Nana enter the amount to withdraw in multiples of 20s. (i.e.; 20, 40, 60, 80, and so on).
//o ATM machine cannot output 1s, 5s, or 10s paper bills only, and of course No coins.

// Cash deposition:
//o The limit is $10000 a day.
//o For every withdrawal transaction, there is a receipt.
//o Nana enter the amount to deposit.
//o ATM machine accepts any paper bills including 1s, 5s, and 10s, but of course No coins.

// Quit:
//o From its name, you will the number of transactions and Thank You message program.
//o Finally, end the program.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PIN 3014
#define WITHDRAWALLIMIT 1000
#define DEPOSITLIMIT 10000

int main() {
    int pinAttemptCount = 0;
    int withdrawalAttemptCount = 0;
    int depositAttemptCount = 0;
    int numberOfTransactions = 0;
    int pinInput;
    int userAction;
    double fractPart;
    double intPart;
    double withdrawalInput;
    double depositInput;
    int amountWithdrawn = 0;
    int amountDeposited = 0;
    int currentBalance = 5000;

    //The user enters an input for the pin number. If the user enters the wrong pin number 3 times, the program terminates.
    printf("Welcome to ATM\n");
    printf("================================================\n");
    printf("Please enter your pin number: ");
    scanf("%d", &pinInput);
    pinAttemptCount++;
    while(pinInput != PIN) {
        printf("ERROR: Invalid pin number. Please enter your pin number again. ");
        scanf("%d", &pinInput);
        if(pinAttemptCount == 2 && pinInput != PIN) {
            printf("================================================\n");
            printf("You have entered an invalid pin number too many times and have been logged out.");
            exit(0);
        }
        pinAttemptCount++;
    }

    printf("================================================\n");
    printf("Login successful. How can we help you today?\n");
    printf("1. Display current balance\n");
    printf("2. Withdraw money from your account\n(Multiples of $20 only and withdrawal limit of $1000 a day)\n");
    printf("3. Deposit money into your account\n(You can deposit any type of paper bill and deposit up to $10000 a day)\n");
    printf("4. Log out of your account\n");
    printf("================================================\n");
    scanf("%d", &userAction);
    printf("================================================\n");

    //Allows the user to continuously use the ATM's 3 available actions until they enter 4 to logout
    while(userAction != 4) {
        //Balance action
        if(userAction == 1) {
            balance(currentBalance);
            numberOfTransactions++;
            scanf("%d", &userAction);
            printf("================================================\n");
        }

        //Withdrawal action
        if(userAction == 2) {
            printf("How much would you like to withdraw? $");
            scanf("%lf", &withdrawalInput);
            fractPart = modf (withdrawalInput, &intPart);
            withdrawalAttemptCount++;

            //Allows the user 3 tries to input a valid withdrawal amount.
            //The while loop ends early if the user inputs a valid withdrawal amount (not divisible by 20, larger than the withdrawal limit, negative number, decimal/coin).
            while(withdrawalAttemptCount < 3 && ((int)withdrawalInput%20 != 0 || withdrawalInput > WITHDRAWALLIMIT || withdrawalInput <= 0 || fractPart != 0)) {
                printf("ERROR: Invalid withdrawal input. Please enter a valid withdrawal amount. $");
                scanf("%lf", &withdrawalInput);
                fractPart = modf (withdrawalInput, &intPart);
                withdrawalAttemptCount++;
            }
            //If the withdrawAttemptCount counter went up to 3, check to see if the last input was a valid input. If it wasn't, the program is terminated.
            if(withdrawalAttemptCount > 2 && ((int)withdrawalInput%20 != 0 || withdrawalInput > WITHDRAWALLIMIT || withdrawalInput <= 0 || fractPart != 0)) {
                printf("You have entered an invalid withdrawal amount too many times and have been logged out.");
                exit(0);
            }

            //Stops the user from withdrawing if they've withdrawn the daily maximum amount already or they entered a withdrawal input that will cause them to exceed the daily maximum limit
            //If nothing is wrong with the user's input, carries out the withdrawal and increases the numberOfTransactions counter by 1.
            if(amountWithdrawn + withdrawalInput > WITHDRAWALLIMIT) {
                if(amountWithdrawn >= WITHDRAWALLIMIT) {
                    printf("================================================\n");
                    printf("ERROR: You have already withdrawn the maximum amount today.\n");
                    printf("================================================\n");
                }
                else if(amountWithdrawn < WITHDRAWALLIMIT) {
                    printf("================================================\n");
                    printf("ERROR: The amount you entered will cause you to exceed the daily withdrawal limit.\n");
                    printf("You can withdraw $%d more for today.\n", WITHDRAWALLIMIT - amountWithdrawn);
                    printf("================================================\n");
                }
                userOptions();
            }
            else {
                amountWithdrawn += withdrawalInput;
                currentBalance = cashWithdrawal(currentBalance, (int)withdrawalInput, amountWithdrawn);
                numberOfTransactions++;
            }

            withdrawalAttemptCount = 0;
            scanf("%d", &userAction);
            printf("================================================\n");
        }

        //Deposit action
        if(userAction == 3) {
            printf("How much would you like to deposit? $");
            scanf("%lf", &depositInput);
            fractPart = modf (depositInput, &intPart);
            depositAttemptCount++;

            //Allows the user 3 tries to input a valid deposit amount. The while loop ends early if the user inputs a valid deposit amount.
            //The while loop ends early if the user inputs a valid withdrawal amount (larger than the withdrawal limit, negative number, decimal/coin).
            while(depositAttemptCount < 3 && (depositInput > DEPOSITLIMIT || depositInput <= 0 || fractPart != 0)) {
                printf("ERROR: Invalid deposit input. Please enter a valid deposit amount. $");
                scanf("%lf", &depositInput);
                fractPart = modf (depositInput, &intPart);
                depositAttemptCount++;
            }
            //If the depositAttemptCount counter went up to 3, check to see if the last input was a valid input. If it wasn't, the program is terminated.
            if(depositAttemptCount > 2 && (depositInput > DEPOSITLIMIT || depositInput <= 0 || fractPart != 0)) {
                printf("You have entered an invalid deposit amount too many times and have been logged out.");
                exit(0);
            }

            //Stops the user from depositing if they've deposited the daily maximum amount already or they entered a deposit input that will cause them to exceed the daily maximum limit
            //If nothing is wrong with the user's input, carries out the withdrawal and increases the numberOfTransactions counter by 1.
            if(amountDeposited + depositInput > DEPOSITLIMIT) {
                if(amountDeposited >= DEPOSITLIMIT) {
                    printf("================================================\n");
                    printf("ERROR: You have already deposited the maximum amount today.\n");
                    printf("================================================\n");
                }
                else if(amountDeposited < DEPOSITLIMIT) {
                    printf("================================================\n");
                    printf("ERROR: The amount you entered will cause you to exceed the daily deposit limit.\n");
                    printf("You can deposit $%d more for today.\n", DEPOSITLIMIT - amountDeposited);
                    printf("================================================\n");
                }
                userOptions();
            }
            else {
                amountDeposited += depositInput;
                currentBalance = cashDeposit(currentBalance, (int)depositInput, amountDeposited);
                numberOfTransactions++;
            }

            depositAttemptCount = 0;
            scanf("%d", &userAction);
            printf("================================================\n");
        }
    }

    //The while loop was stopped so the user wants to log out.
    quit(numberOfTransactions);

    return 0;
}

//Prints out the current balance in the user's account
void balance(int balance) {
    printf("Your current balance is $%d\n", balance);
    printf("================================================\n");
    userOptions();
}

//Subtracts the amount that the user wants to withdraw from the current balance of the account.
//Tells the user their balance after the withdrawal, how much they've withdrawn today, and how much more they can withdraw today.
//Asks the user if they would like a receipt.
//Returns the value of the new balance to main after the withdrawal.
int cashWithdrawal(int balance, int withdrawalInput, int amountWithdrawn) {
    balance -= withdrawalInput;
    printf("================================================\n");
    printf("Withdrew $%d from your account.\nYour new balance is $%d.\n", withdrawalInput, balance);
    printf("You have withdrawn $%d so far today.\n", amountWithdrawn);
    printf("You can withdraw $%d more for today.\n", WITHDRAWALLIMIT - amountWithdrawn);
    printf("================================================\n");

    receiptOption();
    userOptions();

    return balance;
}

//Adds the amount that the user wants to deposit to the current balance of the account.
//Tells the user their balance after the deposit, how much they've deposited today, and how much more they can deposit today.
//Asks the user if they would like a receipt.
//Returns the value of the new balance to main after the deposit.
int cashDeposit(int balance, int depositInput, int amountDeposited) {
    balance += depositInput;
    printf("================================================\n");
    printf("Deposited $%d into your account.\nYour new balance is $%d.\n", depositInput, balance);
    printf("You have deposited $%d so far today.\n", amountDeposited);
    printf("You can deposit $%d more for today.\n", DEPOSITLIMIT - amountDeposited);
    printf("================================================\n");

    receiptOption();
    userOptions();

    return balance;
}

//Prints out the thank you message and how many transactions were made during the session.
//Terminates the program.
void quit(int numberOfTransactions) {
    printf("Thank you for using ATM.\nYou have made %d transaction(s) during this session.\nLogging out...\n", numberOfTransactions);
    exit(0);
}

//Prints out all the actions of the ATM for the user
void userOptions() {
    printf("How else can we help you today?\n");
    printf("1. Display current balance\n");
    printf("2. Withdraw money from your account\n(Multiples of $20 only and withdrawal limit of $1000 a day)\n");
    printf("3. Deposit money into your account\n(You can deposit any type of paper bill and deposit up to $10000 a day)\n");
    printf("4. Logout of your account\n");
    printf("================================================\n");
}

//Gives the user the option to receive a receipt is they want one
void receiptOption() {
    int receiptOption;

    printf("Would you like a receipt for your transaction?\n1. Yes\n2. No\n");
    printf("================================================\n");
    scanf("%d", &receiptOption);
    printf("================================================\n");

    if(receiptOption == 1) {
        printf("Printing receipt...\n");
        printf("================================================\n");
    }
    else if(receiptOption == 2) {
        printf("No receipt will be printed\n");
        printf("================================================\n");
    }
}
