#include <stdio.h>

int main() {
    FILE *sourceFile, *destinationFile;
    char character;

    // Open the source file for reading
    sourceFile = fopen("8-a.txt", "r");
    if (sourceFile == NULL) {
        printf("Error opening source file.\n");
        return 1;
    }

    // Open the destination file for appending
    destinationFile = fopen("8-b.txt", "a");
    if (destinationFile == NULL) {
        printf("Error opening destination file.\n");
        fclose(sourceFile);
        return 1;
    }

    // Copy the contents of the source file to the destination file
    while ((character = fgetc(sourceFile)) != EOF) {
        fputc(character, destinationFile);
    }

    // Close the files
    fclose(sourceFile);
    fclose(destinationFile);

    printf("Contents added to 'destination.txt'.\n");

    return 0;
}
