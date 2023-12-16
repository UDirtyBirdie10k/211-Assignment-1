#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int isPresent(int sudokuMatrix[9][9], int row, int col, int num) {
    // Check if 'num' is not in the current row, current column, or current 3x3 subgrid
    for (int i = 0; i < 9; i++) {
        if (sudokuMatrix[row][i] == num || sudokuMatrix[i][col] == num || sudokuMatrix[row - row % 3 + i / 3][col - col % 3 + i % 3] == num) {
            return 0;
        }
    }
    return 1;
}

int isSudokuValid(int sudokuMatrix[9][9]) {
    int rowCheck[9][10] = {0};
    int colCheck[9][10] = {0};
    int subgridCheck[9][10] = {0};

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int num = sudokuMatrix[row][col];

            if (num < 1 || num > 9 || rowCheck[row][num] || colCheck[col][num] || subgridCheck[3 * (row / 3) + col / 3][num]) {
                return 0; // Invalid number or duplicate
            }

            rowCheck[row][num] = 1;
            colCheck[col][num] = 1;
            subgridCheck[3 * (row / 3) + col / 3][num] = 1;
        }
    }

    return 1;
}


int solveSudoku(int sudokuMatrix[9][9]) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (sudokuMatrix[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isPresent(sudokuMatrix, row, col, num)) {
                        sudokuMatrix[row][col] = num;

                        if (isSudokuValid(sudokuMatrix) && solveSudoku(sudokuMatrix)) {
                        return 1; // Solved
                    }

                        sudokuMatrix[row][col] = 0; // Backtrack
                    }
                }
                return 0; // Unable to solve
            }
        }
    }
    return 1; // Solved
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }

    FILE* file = fopen(argv[1], "r");

    if (file == NULL) {
        return 1;
    }
    
    bool solvableFile = false;

    int sudokuMatrix[9][9];
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char inputChar;
            fscanf(file, " %c", &inputChar);
            if (inputChar == '_') {
                solvableFile = true;
                sudokuMatrix[i][j] = 0; // Use 0 to represent unspecified digits
            } else {
                sudokuMatrix[i][j] = inputChar - '0'; // Convert character to integer
            }
        }
    }

    fclose(file);

    if(solvableFile == true){
        
        if (solveSudoku(sudokuMatrix)) {
        printf("solvable\n");
        }
        else{
             printf("unsolvable\n");
        }
    }else{

        if(isSudokuValid(sudokuMatrix)){
        printf("correct\n");
        }
        else{
            printf("incorrect\n");

        }
    }


    return 0;
}

            

