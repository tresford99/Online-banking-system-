online-banking-system-
## Online Banking System (C)

A simple console-based Online Banking System implemented in C. This program allows users to register accounts, log in, deposit, withdraw, transfer money, change passwords, and save/load account data to a file.



## Features

* **Account Registration:** Create a new bank account with an initial deposit.
* **Secure Login:** Access account using a unique account number and password.
* **Deposit:** Add funds to the account balance.
* **Withdrawal:** Remove funds, checking for sufficient balance.
* **Transfer:** Send money to another registered account.
* **Password Change:** Update the account password.
* **Display Details:** View current account holder name, number, and balance.
* **Persistence:** Account data is automatically saved to `accounts.txt` upon exit and loaded upon startup.



## Requirements

* **C Compiler:** (e.g., GCC, Clang)
* **Operating System:** Any OS that supports C compilation (Windows, Linux, macOS).



## Getting Started

### 1. Compilation

Save the provided code as a file named `banking_system.c`. Compile the source code using a C compiler (like GCC):

```bash
gcc banking_system.c -o banking_system
