#include <stdio.h>

// Function to add two time values
void addTime(int h1, int m1, int s1, int h2, int m2, int s2, int *resultH, int *resultM, int *resultS) {
    int totalSeconds = (s1 + s2) % 60;
    int carrySeconds = (s1 + s2) / 60;

    int totalMinutes = (m1 + m2 + carrySeconds) % 60;
    int carryMinutes = (m1 + m2 + carrySeconds) / 60;

    *resultH = h1 + h2 + carryMinutes;
    *resultM = totalMinutes;
    *resultS = totalSeconds;
}

int main() {
    int hours1, minutes1, seconds1;
    int hours2, minutes2, seconds2;
    int resultHours, resultMinutes, resultSeconds;

    // Input the first time
    printf("Enter the first time (hours minutes seconds): ");
    scanf("%d %d %d", &hours1, &minutes1, &seconds1);

    // Input the second time
    printf("Enter the second time (hours minutes seconds): ");
    scanf("%d %d %d", &hours2, &minutes2, &seconds2);

    // Call the function to add the times
    addTime(hours1, minutes1, seconds1, hours2, minutes2, seconds2, &resultHours, &resultMinutes, &resultSeconds);

    // Display the result
    printf("Sum of times: %d hours, %d minutes, %d seconds\n", resultHours, resultMinutes, resultSeconds);

    return 0;
}
