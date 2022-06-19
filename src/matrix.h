/*
 * Functions for:
 * 1. Creating matrices
 * 2. Freeing matrices 
 * 3. Matrices operations
 */

#ifndef MATRIX_H
#define MATRIX_H

/*
 * Dynamically allocate multi-dimensional arrays reference: http://c-faq.com/aryptr/dynmuldimary.html
 * However, we used struct against without the struct version: (double **values = malloc(...))
 * Because we want to store row and col sizes so we won't need to count it everytime by looping.
 * Meaning, no need to create a function that counts the row and sizes every time.
 */

typedef struct
{
    double **values; // Row pointers
    int rows;        // Row size
    int cols;        // Column size
}
Matrix;

Matrix* create_matrix(int, int);
Matrix* create_zero_matrix(int, int);
void print_matrix(Matrix *);
void free_matrix(Matrix *);
void fill_num_matrix(Matrix *);
Matrix* transpose_matrix(Matrix *);
Matrix* multiply_matrix(Matrix *, Matrix *);

// TODO:
// -- Scalar to matrix or matrix to scalar
// 1. multiply_scalar_to_mat(mat, s)
// 2. add_scalar_to_mat(mat, s)

// -- Matrix to matrix
// 1. multiply_mat_to_mat(mat1, mat2)
// 2. add_mat_to_mat(mat1, mat2)

// -- Broadcasting: row to matrix, or column to matrix

#endif