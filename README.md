# CIS 2107 Lab 3 - ATM

## ATM Machine
Write a C Program for an ATM machine.

### The types of ATM transaction are:
    1. Balance.
    2. Cash withdrawal.
    3. Cash deposition.
    4. Quit.

All ATM transactions (menu options) need to be implemented in terms of functions.
You will call those functions based on the menu option.

Initially, Nana has one checking account with a balance of $5000 with PIN number of 3014.

### Money amount validation:
    o Catch invalid numerical inputs (Negative numbers and Zeroes).
    o Users can enter numbers only.
    o Remember  any  ATM  has  numpad  only.  This  numpad  has  neither  letters  nor  special
    characters.
    o Don’t worry about entering other inputs rather than numbers for now.
    o I mean don’t worry what would happen if the user enters a string, a char, or a special
    characters instead of a number. We will discuss this later in another chapter.
    o In  short,  if  the  Nana  enters  wrong  amount,  ask  her  to  enter  amount  again,  after  3
    unsuccessful attempts, display an error message and terminate the program.

### PIN validation:
    o Nana has 3 attempts to enter PIN. After that the program logs them off, and end the
      program.
     Once Nana chooses to finish using the ATM, print out Thank You message and tell her the
      number of transactions she has made.
     All ATM transactions (menu options) need to be implemented in terms of functions.
    o You will call those functions based on the menu option.
     All ATM transactions have receipts, but it is up to the user to choose.
    o Use 1 for yes, and 2 for No.
    o The receipt is virtual. No need to display the receipt on screen.


### Balance:
    o Nothing special about it. Basically it prints out the balance.

### Cash withdrawal:
    o The limit is $1000 a day.
    o For every withdrawal transaction, there is a receipt.
    o Nana enter the amount to withdraw in multiples of 20s. (i.e.; 20, 40, 60, 80, and so on).
    o ATM machine cannot output 1s, 5s, or 10s paper bills only, and of course No coins.

### Cash deposition:
    o The limit is $10000 a day.
    o For every withdrawal transaction, there is a receipt.
    o Nana enter the amount to deposit.
    o ATM machine accepts any paper bills including 1s, 5s, and 10s, but of course No coins.

### Quit:
    o From its name, you will the number of transactions and Thank You message program.
    o Finally, end the program.
