/*
File: BankingSystem.C
Description: A project demo of a simple banking system
Author: Doung
Date: 14/3/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accountNumber;
    char name[50];
    float balance;
};

void displayMenu() {
    printf("\n--- Simple Banking System ---\n");
    printf("1. Create Account\n");
    printf("2. Deposit Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Check Balance\n");
    printf("5. View Account Details\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

void createAccount(struct Account accounts[], int *count) {
    if (*count >= 100) {
        printf("Account limit reached!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &accounts[*count].accountNumber);

    printf("Enter name: ");
    scanf(" %[^\n]", accounts[*count].name);

    printf("Enter initial balance: ");
    scanf("%f", &accounts[*count].balance);

    (*count)++;
    printf("Account created successfully!\n");
}

void depositMoney(struct Account accounts[], int count) {
    int accountNumber;
    float amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);

            accounts[i].balance += amount;
            printf("Deposit successful! New balance: %.2f\n", accounts[i].balance);
            return;
        }
    }

    printf("Account not found!\n");
}

void withdrawMoney(struct Account accounts[], int count) {
    int accountNumber;
    float amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);

            if (amount > accounts[i].balance) {
                printf("Insufficient balance!\n");
            } else {
                accounts[i].balance -= amount;
                printf("Withdrawal successful! New balance: %.2f\n", accounts[i].balance);
            }
            return;
        }
    }

    printf("Account not found!\n");
}

void checkBalance(struct Account accounts[], int count) {
    int accountNumber;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            printf("Account balance: %.2f\n", accounts[i].balance);
            return;
        }
    }

    printf("Account not found!\n");
}

void viewAccountDetails(struct Account accounts[], int count) {
    int accountNumber;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            printf("\n--- Account Details ---\n");
            printf("Account Number: %d\n", accounts[i].accountNumber);
            printf("Name: %s\n", accounts[i].name);
            printf("Balance: %.2f\n", accounts[i].balance);
            return;
        }
    }

    printf("Account not found!\n");
}

void saveAccounts(struct Account accounts[], int count) {
    FILE *file = fopen("accounts.dat", "wb");
    if (file == NULL) {
        printf("Error saving accounts!\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, file);
    fwrite(accounts, sizeof(struct Account), count, file);
    fclose(file);
    printf("Accounts saved successfully!\n");
}

void loadAccounts(struct Account accounts[], int *count) {
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL) {
        printf("No saved accounts found.\n");
        return;
    }

    fread(count, sizeof(int), 1, file);
    fread(accounts, sizeof(struct Account), *count, file);
    fclose(file);
    printf("Accounts loaded successfully!\n");
}

int main() {
    struct Account accounts[100];
    int count = 0;
    int choice;

    loadAccounts(accounts, &count);

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount(accounts, &count);
                break;
            case 2:
                depositMoney(accounts, count);
                break;
            case 3:
                withdrawMoney(accounts, count);
                break;
            case 4:
                checkBalance(accounts, count);
                break;
            case 5:
                viewAccountDetails(accounts, count);
                break;
            case 6:
                saveAccounts(accounts, count);
                printf("Exiting the program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}