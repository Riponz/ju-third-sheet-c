// #include <stdio.h>
// #include <stdlib.h>

// // Function to compute row sums and store in a new file
// void computeRowSums(FILE *inputFile, FILE *outputFile) {
//     int row = 0;
//     int col = 0;
//     int rowSum = 0;

//     // Read the matrix from the file and compute row sums
//     while (fscanf(inputFile, "%d", &col) != EOF) {
//         rowSum += col;
//         printf("%d col val\n",col);
//         if (col == '\n') {
//         printf("%d Row Sum\n",rowSum);

//             // printf("row - %d, rowsum - %d",row+1, rowSum);

//             // Write row number and row sum to the output file
//             fprintf(outputFile, "Row %d: %d\n", row + 1, rowSum);

//             // Move to the next row
//             row++;
//             rowSum = 0;

//         }
//         printf("Row sums calculated and stored in 'output_row_sums.txt'.\n");
//     }
// }

// int main() {
//     FILE *inputFile, *outputFile;

//     // Open the input file
//     inputFile = fopen("input_matrix.txt", "r");
//     if (inputFile == NULL) {
//         printf("Error opening input file.\n");
//         return 1;
//     }

//     // Open the output file
//     outputFile = fopen("output_row_sums.txt", "w");
//     if (outputFile == NULL) {
//         printf("Error opening output file.\n");
//         fclose(inputFile);
//         return 1;
//     }

//     // Compute row sums and write to the output file
//     computeRowSums(inputFile, outputFile);

//     // Close the files
//     fclose(inputFile);
//     fclose(outputFile);

//     // printf("Row sums calculated and stored in 'output_row_sums.txt'.\n");

//     return 0;
// }






#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1000 // Adjust this based on your input file

// Function to compute row sums and store in a new file
void computeRowSums(FILE *inputFile, FILE *outputFile) {
    int row = 0;
    char line[MAX_LINE_LENGTH];

    // Read each line from the file and compute row sums
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        int rowSum = 0;

        for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++) {
            // Assuming binary values are '0' and '1'
            rowSum += (line[i] - '0');
        }

        // Write row number and row sum to the output file
        fprintf(outputFile, "Row %d: %d\n", row + 1, rowSum);

        // Move to the next row
        row++;
    }
}

int main() {
    FILE *inputFile, *outputFile;

    // Open the input file
    inputFile = fopen("input_matrix.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    // Open the output file
    outputFile = fopen("output_row_sums.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        fclose(inputFile);
        return 1;
    }

    // Compute row sums and write to the output file
    computeRowSums(inputFile, outputFile);

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("Row sums calculated and stored in 'output_row_sums.txt'.\n");

    return 0;
}
