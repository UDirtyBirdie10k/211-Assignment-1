#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


void multiplyMatrices(int** a, int** b, int** c, int k) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            c[i][j] = 0;
            for (int l = 0; l < k; l++) {
                c[i][j] += a[i][l] * b[l][j];
            }
        }
    }
}

void printMatrix(int** result, int k) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {

            printf("%d", result[i][j]);

            if(j == k - 1){
                continue;
            }
            else{
                printf(" ");
            }

        }
        printf("\n");
    }
}

void freeMatrix(int** matrix, int k) {
    for (int i = 0; i < k; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


int main(int argc, char* argv[]) {

if(argc != 2){

    return 1;

}

FILE* file = fopen(argv[1], "r");

if(file == NULL){
    
    return 1;

}

int k,n;

fscanf(file, "%d", &k);                                     /*Read size of matrix*/

int** matrix = (int**)malloc(k * sizeof(int*));

int** result = (int**)malloc(k * sizeof(int*));

    for (int i = 0; i < k; i++) {                   /*This allocates the memory for the matrix being taken in from the file*/

        matrix[i] = (int*)malloc(k * sizeof(int));
        result[i] = (int*)malloc(k * sizeof(int));

    }

    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){

            fscanf(file, "%d", &matrix[i][j]);

        }
    }

    fscanf(file, "%d", &n);                                     /*Read n to see how many times to multiply*/


if (n == 0) {
        // If the exponent is 0, the result is the identity matrix
        for(int i = 0; i < k; i++){
            for(int j = 0; j < k; j++){

                result[i][j] = (i == j) ? 1 : 0;


            }
        }
    } else {

        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                result[i][j] = matrix[i][j];                /*initialzes the result of the read matrix from file to another temp matrix*/
            }
        }

        for (int i = 1; i < n; i++) {
            int** tempMat = (int**)malloc(k * sizeof(int*));
            for (int j = 0; j < k; j++) {
                tempMat[j] = (int*)malloc(k * sizeof(int));             /*Calculates the multiplatices with memory allocation*/
            }
            multiplyMatrices(result, matrix, tempMat, k);

            for (int j = 0; j < k; j++) {
                for (int l = 0; l < k; l++) {
                    result[j][l] = tempMat[j][l];                   /*copies the finsihed matrix to the result matrix which is what will be printed*/
                }
            }

            for (int j = 0; j < k; j++) {
                free(tempMat[j]);                               
            }                                               /*free the temporary matrix*/
            free(tempMat);
        }
    }

printMatrix(result,k);

freeMatrix(result, k);
freeMatrix(matrix, k);

    return 0;
}