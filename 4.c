#include <stdio.h>

// Define the DATE structure
struct DATE {
    int day;
    int month;
    int year;
};

// Function to compare two dates
int compareDates(struct DATE date1, struct DATE date2) {
    if (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day) {
        return 1; // Dates are equal
    } else {
        return 0; // Dates are unequal
    }
}

int main() {
    // Declare two DATE structures
    struct DATE date1, date2;

    // Input the first date
    printf("Enter the first date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &date1.day, &date1.month, &date1.year);

    // Input the second date
    printf("Enter the second date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &date2.day, &date2.month, &date2.year);

    // Call the function to compare dates
    if (compareDates(date1, date2)) {
        printf("Equal\n");
    } else {
        printf("Unequal\n");
    }

    return 0;
}
