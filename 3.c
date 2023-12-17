#include <stdio.h>
#include <stdlib.h>

// Define the structure to store customer data
struct Customer
{
    int accountNumber;
    char name[50];
    float balance;
};

// Function to print account number and name of customers with balance below Rs. 1000
void printLowBalanceCustomers(struct Customer customers[], int numCustomers)
{
    int flag = 0;
    printf("Customers with balance below Rs. 1000:\n");
    for (int i = 0; i < numCustomers; ++i)
    {
        if (customers[i].balance < 1000)
        {
            flag = 1;
            printf("Account Number: %d, Name: %s\n", customers[i].accountNumber, customers[i].name);
        }
    }
    if (flag == 0)
        printf("No one has balance less than 1000");
}

// Function to deposit or withdraw amount from the specified account
void transaction(struct Customer *customer, float amount, int code)
{
    if (code == 1)
    { // Deposit
        customer->balance += amount;
        printf("Deposit successful. New balance: Rs. %.2f\n", customer->balance);
    }
    else if (code == 0)
    { // Withdrawal
        if (amount > customer->balance)
        {
            printf("The balance is insufficient for the specified withdrawal.\n");
        }
        else
        {
            customer->balance -= amount;
            printf("Withdrawal successful. New balance: Rs. %.2f\n", customer->balance);
        }
    }
    else
    {
        printf("Invalid transaction code.\n");
    }
}

int main()
{
    // Assume there can be more than 100 customers
    const int maxCustomers = 1000;

    // Create an array of Customer structures
    struct Customer customers[maxCustomers];

    // Open the file for reading
    FILE *file = fopen("bank.txt", "r");

    // Check if the file is opened successfully
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // Read customer details from the file
    int numCustomers = 0;
    while (fscanf(file, "%d %s %f", &customers[numCustomers].accountNumber, customers[numCustomers].name, &customers[numCustomers].balance) == 3)
    {
        numCustomers++;
        if (numCustomers >= maxCustomers)
        {
            printf("Maximum number of customers reached.\n");
            break;
        }
    }

    // Close the file
    fclose(file);
    int choice;

    int accountNumber;
    float transactionAmount;
    int transactionCode;

    while (1)
    {

        printf("\n*****MENU*****\n");
        printf("1 for Display Account with balance below 1000\n");
        printf("2 for Withdrawal/Deposit\n");
        printf("0 for EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            // Print customers with balance below Rs. 1000
            printLowBalanceCustomers(customers, numCustomers);
            break;
        case 2:
            printf("Enter account number for transaction: ");
            scanf("%d", &accountNumber);

            // Find the customer with the specified account number
            struct Customer *customer = NULL;
            for (int i = 0; i < numCustomers; ++i)
            {
                if (customers[i].accountNumber == accountNumber)
                {
                    customer = &customers[i];
                    break;
                }
            }

            // Perform the transaction if the customer is found
            if (customer != NULL)
            {
                printf("Enter transaction amount: ");
                scanf("%f", &transactionAmount);

                printf("Enter transaction code (1 for deposit, 0 for withdrawal): ");
                scanf("%d", &transactionCode);

                transaction(customer, transactionAmount, transactionCode);
            }
            else
            {
                printf("Customer with account number %d not found.\n", accountNumber);
            }
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
