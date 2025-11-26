#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 20
#define MAX_ACCOUNT_NUMBER_LENGTH 10

typedef struct {
    char name[MAX_NAME_LENGTH];
    char accountNumber[MAX_ACCOUNT_NUMBER_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    float balance;
} Account;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

void registerAccount();
void depositMoney();
void withdrawMoney();
void transferMoney();
void changePassword();
void displayAccountDetails();
void saveAccountsToFile();
void loadAccountsFromFile();
int findAccount(char *accountNumber);
void loginSystem();

int main() {
    loadAccountsFromFile();
    int choice;
    while (1) {
        printf("Online Banking System\n");
        printf("1. Login\n");
        printf("2. Register Account\n");
        printf("3. deposit money\n");
        printf("4. withdraw money\n");
        printf("5. trasfer money\ n");
        printf("6. enter password\n");
        printf("7. change password\n");
        printf("8. forgot password\n");
        printf("9. reset password\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                registerAccount();
                break;
            case 2:
                loginSystem();
                break;
            case 3:
                saveAccountsToFile();
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void registerAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Maximum accounts reached. Cannot register new account.\n");
        return;
    }
    Account newAccount;
    printf("Enter your name: ");
    scanf("%s", newAccount.name);
    printf("Enter account number: ");
    scanf("%s", newAccount.accountNumber);
    printf("Enter password: ");
    scanf("%s", newAccount.password);
    printf("Enter initial deposit: ");
    scanf("%f", &newAccount.balance);
    accounts[accountCount++] = newAccount;
    printf("Account registered successfully.\n");
}

void loginSystem() {
    char accountNumber[MAX_ACCOUNT_NUMBER_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    printf("Enter account number: ");
    scanf("%s", accountNumber);
    printf("Enter password: ");
    scanf("%s", password);
    int index = findAccount(accountNumber);
    if (index != -1 && strcmp(accounts[index].password, password) == 0) {
        printf("Login successful.\n");
        int choice;
        while (1) {
            printf("1. Deposit Money\n");
            printf("2. Withdraw Money\n");
            printf("3. Transfer Money\n");
            printf("4. Change Password\n");
            printf("5. Display Account Details\n");
            printf("6. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    depositMoney(index);
                    break;
                case 2:
                    withdrawMoney(index);
                    break;
                case 3:
                    transferMoney(index);
                    break;
                case 4:
                    changePassword(index);
                    break;
                case 5:
                    displayAccountDetails(index);
                    break;
                case 6:
                    return;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    } else {
        printf("Invalid account number or password.\n");
    }
}

void depositMoney(int index) {
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    accounts[index].balance += amount;
    printf("Deposit successful. New balance: %.2f\n", accounts[index].balance);
}

void withdrawMoney(int index) {
    float amount;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);
    if (accounts[index].balance >= amount) {
        accounts[index].balance -= amount;
        printf("Withdrawal successful. New balance: %.2f\n", accounts[index].balance);
    } else {
        printf("Insufficient funds.\n");
    }
}

void transferMoney(int index) {
    char recipientAccountNumber[MAX_ACCOUNT_NUMBER_LENGTH];
    float amount;
    printf("Enter recipient account number: ");
    scanf("%s", recipientAccountNumber);
    int recipientIndex = findAccount(recipientAccountNumber);
    if (recipientIndex != -1) {
        printf("Enter amount to transfer: ");
        scanf("%f", &amount);
        if (accounts[index].balance >= amount) {
            accounts[index].balance -= amount;
            accounts[recipientIndex].balance += amount;
            printf("Transfer successful. New balance: %.2f\n", accounts[index].balance);
        } else {
            printf("Insufficient funds.\n");
        }
    } else {
        printf("Recipient account not found.\n");
    }
}

void changePassword(int index) {
    char newPassword[MAX_PASSWORD_LENGTH];
    printf("Enter new password: ");
    scanf("%s", newPassword);
    strcpy(accounts[index].password, newPassword);
    printf("Password changed successfully.\n");
}

void displayAccountDetails(int index) {
    printf("Account Holder Name: %s\n", accounts[index].name);
    printf("Account Number: %s\n", accounts[index].accountNumber);
    printf("Balance: %.2f\n", accounts[index].balance);
}

int findAccount(char *accountNumber) {
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].accountNumber, accountNumber) == 0) {
            return i;
        }
    }
    return -1;
}

void saveAccountsToFile() {
    FILE *file = fopen("accounts.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < accountCount; i++) {
        fprintf(file, "%s %s %s %.2f\n", accounts[i].name, accounts[i].accountNumber, accounts[i].password, accounts[i].balance);
    }
    fclose(file);
}

void loadAccountsFromFile() {
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        return;
    }
    while (fscanf(file, "%s %s %s %f", accounts[accountCount].name, accounts[accountCount].accountNumber, accounts[accountCount].password, &accounts[accountCount].balance) != EOF) {
        accountCount++;
    }
    fclose(file);
}