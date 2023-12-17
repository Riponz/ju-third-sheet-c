#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_BOOKS 1000

struct Library
{
    int accessionNumber;
    char title[100];
    char author[50];
    float price;
    int isIssued; // 0 for not issued, 1 for issued
};

void stringToLower(char *str)
{
    if (str == NULL)
    {
        return; // Check for NULL pointer
    }

    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = tolower((unsigned char)str[i]);
    }
}

struct Library books[MAX_BOOKS];
int bookCount = 0;

void readFromFile()
{
    FILE *file = fopen("library.txt", "r");
    if (file == NULL)
    {
        printf("Could not open file for reading.\n");
        return;
    }

    while (fscanf(file, "%d %s %s %f %d",
                  &books[bookCount].accessionNumber,
                  books[bookCount].title,
                  books[bookCount].author,
                  &books[bookCount].price,
                  &books[bookCount].isIssued) != EOF)
    {
        bookCount++;
    }

    fclose(file);
}

void writeToFile()
{
    FILE *file = fopen("library.txt", "w");
    if (file == NULL)
    {
        printf("Could not open file for writing.\n");
        return;
    }

    for (int i = 0; i < bookCount; i++)
    {
        fprintf(file, "%d %s %s %.2f %d\n",
                books[i].accessionNumber,
                books[i].title,
                books[i].author,
                books[i].price,
                books[i].isIssued);
    }

    fclose(file);
}

void addBook()
{
    if (bookCount < MAX_BOOKS)
    {
        printf("Enter Accession Number: ");
        scanf("%d", &books[bookCount].accessionNumber);
        printf("Enter Title: ");
        scanf(" %[^\n]s", books[bookCount].title);
        printf("Enter Author: ");
        scanf(" %[^\n]s", books[bookCount].author);
        printf("Enter Price: ");
        scanf("%f", &books[bookCount].price);
        books[bookCount].isIssued = 0;
        bookCount++;
        printf("Book added successfully.\n");
    }
    else
    {
        printf("Library is full. Cannot add more books.\n");
    }
}

void displayBookInfo()
{
    if (bookCount > 0)
    {
        printf("\nAccession Number\tTitle\t\tAuthor\t\tPrice\t\tStatus\n");
        for (int i = 0; i < bookCount; i++)
        {
            printf("%d\t\t\t%s\t\t%s\t\t%.2f\t\t%s\n", books[i].accessionNumber,
                   books[i].title, books[i].author, books[i].price,
                   (books[i].isIssued == 0) ? "Available" : "Issued");
        }
    }
    else
    {
        printf("No books in the library.\n");
    }
}

void listBooksByAuthor()
{
    char authorName[50];
    int found = 0;
    printf("Enter Author Name: ");
    scanf(" %s", authorName);

    printf("\nBooks by %s:\n", authorName);
    for (int i = 0; i < bookCount; i++)
    {
        char check[50];
        strcpy(check, books[i].author);
        stringToLower(check);
        stringToLower(authorName);

        if (strcmp(check, authorName) == 0)
        {
            printf("%s\n", books[i].title);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No books found by %s.\n", authorName);
    }
}

void listTitleOfBook()
{
    int accessionNumber;
    int found = 0;
    printf("Enter Accession Number: ");
    scanf("%d", &accessionNumber);

    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].accessionNumber == accessionNumber)
        {
            printf("Title: %s\n", books[i].title);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Book not found with Accession Number %d.\n", accessionNumber);
    }
}

void listBookCount()
{
    printf("Total Books in the Library: %d\n", bookCount);
}

void listBooksByAccession()
{
    if (bookCount > 0)
    {
        printf("\nBooks in the Order of Accession Number:\n");
        printf("Accession Number\tTitle\t\tAuthor\t\tPrice\t\tStatus\n");
        for (int i = 0; i < bookCount; i++)
        {
            printf("%d\t\t\t%s\t\t%s\t\t%.2f\t\t%s\n", books[i].accessionNumber,
                   books[i].title, books[i].author, books[i].price,
                   (books[i].isIssued == 0) ? "Available" : "Issued");
        }
    }
    else
    {
        printf("No books in the library.\n");
    }
}

int main()
{
    // Read existing data from file at the beginning
    readFromFile();

    int choice;

    do
    {
        printf("\nLibrary Management System\n");
        printf("1. Add book information\n");
        printf("2. Display book information\n");
        printf("3. List all books of given author\n");
        printf("4. List the title of specified book\n");
        printf("5. List the count of books in the library\n");
        printf("6. List the books in the order of accession number\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            displayBookInfo();
            break;
        case 3:
            listBooksByAuthor();
            break;
        case 4:
            listTitleOfBook();
            break;
        case 5:
            listBookCount();
            break;
        case 6:
            listBooksByAccession();
            break;
        case 7:
            printf("Exiting program. Saving data to file...\n");
            // Write data to file before exiting
            writeToFile();
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 7);

    return 0;
}
