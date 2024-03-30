#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

// Struct definition for passing matrix data to threads
typedef struct {
    double **matrixA;
    double **matrixB;
    double **resultMatrix;
    int A_rows;
    int A_cols_B_rows;
    int B_cols;
} MatrixData;

typedef struct {
  int row;
  int col;
  MatrixData *data;
} ThreadData;

// Function prototypes
void initialize_arrays(MatrixData *data, FILE *fp);
void print_matrix(double **matrix, int m, int n);
void multiply(ThreadData *td);
void free_matrices(MatrixData *data);




#endif // MAIN_H
