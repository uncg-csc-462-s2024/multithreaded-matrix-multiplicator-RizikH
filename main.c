/**
 * This is a multithreaded matrix multiplication program.
 * it takes in a .txt file and create 2 matrices A and B. Multiplies A * B and store it in a new Matrix C.
 *
 * @author Rihaddad2@uncg.edu
 * @version 03/29/2024
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * @brief Entry point of the matrix multiplication program.
 * Reads matrices from a file, multiplies them using multiple threads, and outputs the result.
 * 
 * @param argc The number of command line arguments.
 * @param argv Array of command line arguments. Expects a file name as the first argument.
 * @return int Returns 0 on success, or 1 if an error occurs (e.g., incorrect number of arguments, file open failure).
 */
int main(int argc, char *argv[]) {
    FILE *fp;
    MatrixData data; //MatrixData is a typedef struct in main.h

    // Check for correct number of command line arguments
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }
    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Failed to open file %s\n", argv[1]);
        return 1;
    }

    // Read matrix dimensions from file
    fscanf(fp, "%d %d %d", &data.A_rows, &data.A_cols_B_rows, &data.B_cols);
    initialize_arrays(&data, fp);
    fclose(fp);

    // Create threads and pass them the data they need to calculate the result matrix
    pthread_t *threads = malloc(data.A_rows * data.B_cols * sizeof(pthread_t));
    ThreadData *threadDataArray = malloc(data.A_rows * data.B_cols * sizeof(ThreadData));

    for (int i = 0; i < data.A_rows; i++) {
        for (int j = 0; j < data.B_cols; j++) {
            ThreadData *td = &threadDataArray[i * data.B_cols + j]; //ThreadData is a typedef struct in main.h
            td->row = i;
            td->col = j;
            td->data = &data;
            pthread_create(&threads[i * data.B_cols + j], NULL, (void *)multiply, (void *)td);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < data.A_rows * data.B_cols; i++) {
        pthread_join(threads[i], NULL);
    }

    print_matrix(data.resultMatrix, data.A_rows, data.B_cols);
    printf("\n");

    free(threads);
    free(threadDataArray);
    free_matrices(&data);
    return 0;
}

/**
 * @brief Initializes matrices A, B, and the result matrix by allocating memory and reading their contents from a file.
 * 
 * @param data Pointer to the MatrixData struct containing matrix dimensions.
 * @param fp File pointer to the input file containing matrix data.
 */
void initialize_arrays(MatrixData *data, FILE *fp) {
    data->matrixA = malloc(data->A_rows * sizeof(double *));
    data->matrixB = malloc(data->A_cols_B_rows * sizeof(double *));
    data->resultMatrix = malloc(data->A_rows * sizeof(double *));

    // Allocate memory for matrices A, B, and result matrix
    for (int i = 0; i < data->A_rows; i++) {
        data->matrixA[i] = malloc(data->A_cols_B_rows * sizeof(double));
        data->resultMatrix[i] = malloc(data->B_cols * sizeof(double));
    }
    for (int i = 0; i < data->A_cols_B_rows; i++) {
        data->matrixB[i] = malloc(data->B_cols * sizeof(double));
    }
    // Fill matrices A and B from file
    for (int i = 0; i < data->A_rows; i++) {
        for (int j = 0; j < data->A_cols_B_rows; j++) {
            fscanf(fp, "%lf", &data->matrixA[i][j]);
        }
    }
    for (int i = 0; i < data->A_cols_B_rows; i++) {
        for (int j = 0; j < data->B_cols; j++) {
            fscanf(fp, "%lf", &data->matrixB[i][j]);
        }
    }
}

/**
 * @brief Prints the contents of a matrix to standard output.
 * 
 * @param matrix Double pointer to the matrix to be printed.
 * @param m Number of rows in the matrix.
 * @param n Number of columns in the matrix.
 */
void print_matrix(double **matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        printf("\n");
        for (int j = 0; j < n; j++) {
            printf("%lf ", matrix[i][j]);
        }
    }
}

/**
 * @brief The function that each thread will execute to multiply a specific row of matrix A by a specific column of matrix B.
 * 
 * @param td Pointer to ThreadData struct containing the indices for the row and column as well as matrix data.
 */
void multiply(ThreadData *td) {
    double sum = 0.0;
    for (int i = 0; i < td->data->A_cols_B_rows; ++i) {
        sum += td->data->matrixA[td->row][i] * td->data->matrixB[i][td->col];
    }
    td->data->resultMatrix[td->row][td->col] = sum; // Store the result in the result matrix
}

/**
 * @brief Frees dynamically allocated memory for matrices A, B, and the result matrix.
 * 
 * @param data Pointer to the MatrixData struct that holds pointers to matrices and their dimensions.
 */
void free_matrices(MatrixData *data) {
// Free dynamically allocated memory
    for (int i = 0; i < data->A_rows; i++) {
        free(data->matrixA[i]);
        free(data->resultMatrix[i]);
    }
    free(data->matrixA);
    free(data->resultMatrix);

    for (int i = 0; i < data->A_cols_B_rows; i++) {
        free(data->matrixB[i]);
    }
    free(data->matrixB);
}
