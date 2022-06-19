// TODO: simplify var names
// eg. matrix* mat_T(matrix *mat)

#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

// Dynamically allocate a 2d array as a Matrix (struct)
Matrix* create_matrix(int rows, int cols)
{
    // Create a struct Matrix pointer
    Matrix *matrix = malloc(sizeof(Matrix));

    // Create row pointers
    matrix->values = malloc(rows * sizeof(double*));
    
    // Allocate columns per row pointer
    for (int i = 0; i < rows; i++)
    {
        matrix->values[i] = malloc(cols * sizeof(double));
    }

    // Don't forget to store the size of row and col 
    matrix->rows = rows; 
    matrix->cols = cols;

    return matrix;
}

// Create a matrix using create_matrix() with zeroes as default value
Matrix* create_zero_matrix(int rows, int cols)
{   
    Matrix *matrix = create_matrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix->values[i][j] = 0.0;
        }
    }
    return matrix;
}

/* Display a plain matrix
 * e.g. matrix(2, 3)
 * 0.000 0.000 0.000
 * 0.000 0.000 0.000
 */
void print_matrix(Matrix *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            printf("%10.3f ", matrix->values[i][j]);
        }
        printf("\n");
    } 
}

// Free matrix pointers
void free_matrix(Matrix *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        // Free the column pointers
        free(matrix->values[i]);
    }
    // Free the row pointers
    free(matrix);
    matrix = NULL; // Not sure if necessary
}

// Fill the matrix with 1 to row*col
void fill_num_matrix(Matrix *matrix)
{
    int z = 1;
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            matrix->values[i][j] = z;
            z++;
        }
    }
}

/*****************************
*****MATRIX OPERATIONS********
*****************************/

// Transpose a given matrix
Matrix* transpose_matrix(Matrix *old_matrix)
{   
    // Cannot directly (not sure) alter the previous matrix, so we need to create new matrix struct
    // With reversed size: (row, col) -> (col, row)
    Matrix *new_matrix = create_matrix(old_matrix->cols, old_matrix->rows);

    // Copy the values with OLD[i][j] -> NEW[j][i]
    for (int i = 0; i < old_matrix->rows; i++)
    {
        for (int j = 0; j < old_matrix->cols; j++)
        {
            new_matrix->values[j][i] = old_matrix->values[i][j];
        }
    } 
    return new_matrix;
}

// Matrix product of two matrices
Matrix* multiply_matrix(Matrix *matrix1, Matrix *matrix2)
{
    // Check if k are equal (m1[i][k] * m2[k][j] = m3[i][j])
    if (matrix1->cols != matrix2->rows)
    {
        printf("Matrix k size are not equal!\n");
        exit(1);
    }

    // Since m1[i][k] * m2[k][j] = m3[i][j]
    // Create a matrix with dimension of (i,j)
    Matrix *matrix_product = create_matrix(matrix1->rows, matrix2->cols);

    for (int i = 0; i < matrix1->rows; i++)
    {
	    for (int j = 0; j < matrix2->cols; j++)
        {
		    double sum = 0;

            for (int k = 0; k < matrix2->rows; k++)
            {
                sum += matrix1->values[i][k] * matrix2->values[k][j];
            }
			matrix_product->values[i][j] = sum;
		}
	}
    return matrix_product;
}