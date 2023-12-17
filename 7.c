#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *inputFile, *outputFile;
    char character;

    // Open the input file
    inputFile = fopen("upper.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    // Open the output file
    outputFile = fopen("upper-output.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        fclose(inputFile);
        return 1;
    }

    // Read each character from the input file, convert to uppercase, and write to the output file
    while ((character = fgetc(inputFile)) != EOF) {
        fputc(toupper(character), outputFile);
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("Text converted to uppercase and stored in 'output.txt'.\n");

    return 0;
}
