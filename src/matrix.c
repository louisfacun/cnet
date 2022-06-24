// TODO: edit indices from i to r(row), j to c(col)

#include "matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Dynamically allocate a 2d array as a Matrix (struct)
matrix* mat_create(int rows, int cols)
{
    // Create a struct Matrix pointer
    matrix *mat = malloc(sizeof(matrix));

    // Create "row" pointers
    mat->values = malloc(rows * sizeof(double*));
    
    // Create "columns" per "row" pointer
    for (int i = 0; i < rows; i++)
    {
        mat->values[i] = malloc(cols * sizeof(double));
    }

    // Don't forget to store the size of row and col 
    mat->rows = rows; 
    mat->cols = cols;

    return mat;
}

// Put zeros to a matrix
void mat_zeros(matrix *mat)
{   
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            mat->values[i][j] = 0.0;
        }
    }
}

/* Display a plain matrix
 * e.g. matrix(2, 3)
 * [[0.000 0.000 0.000]
 *  [0.000 0.000 0.000]]
 */
void mat_print(matrix *mat)
{
    printf("[");
    for (int i = 0; i < mat->rows; i++)
    {
        printf("%s", i == 0 ? "[" : " [");
        for (int j = 0; j < mat->cols; j++)
        {
            printf("%10.8f%s", mat->values[i][j], j == (mat->cols-1) ? "" : " ");
        }
        printf("%s", i == (mat->rows-1) ? "]" : "]\n");
    }
    printf("]\n");
    printf(" Size: (%d, %d)\n\n", mat->rows, mat->cols);
}

// Free matrix pointers
void mat_free(matrix *mat)
{
    for (int i = 0; i < mat->rows; i++)
    {
        // Free the column pointers
        free(mat->values[i]);
    }
    // Free the row pointers
    free(mat);
    mat = NULL; // Not sure if necessary
}

// Fill the matrix with 1 to row*col (only used for testing)
void mat_fill_num(matrix *mat)
{
    int z = 1;
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            mat->values[i][j] = z;
            z++;
        }
    }
}

/*****************************
       MATRIX OPERATIONS
*****************************/

// Transpose a given matrix
matrix* mat_transpose(matrix *old_mat)
{   
    // Cannot directly (not sure) alter the previous matrix, so we need to create new matrix struct
    // With reversed size: (row, col) -> (col, row)
    matrix *new_mat = mat_create(old_mat->cols, old_mat->rows);
    
    // Copy the values with OLD[i][j] -> NEW[j][i]
    for (int i = 0; i < old_mat->rows; i++)
    {
        for (int j = 0; j < old_mat->cols; j++)
        {
            new_mat->values[j][i] = old_mat->values[i][j];
        }
    }

    //free(old_mat);
    return new_mat;
}

// Matrix product of two matrices
matrix* mat_multiply(matrix *mat1, matrix *mat2)
{
    // Check if k are equal (m1[i][k] * m2[k][j] = m3[i][j])
    if (mat1->cols != mat2->rows)
    {
        printf("Matrix k size are not equal!\n");
        exit(1);
    }

    // Since m1[i][k] * m2[k][j] = m3[i][j]
    // Create a matrix with dimension of (i,j)
    matrix *mat_prod = mat_create(mat1->rows, mat2->cols);

    for (int i = 0; i < mat1->rows; i++)
    {
        for (int j = 0; j < mat2->cols; j++)
        {
            double sum = 0;

            for (int k = 0; k < mat2->rows; k++)
            {
                sum += mat1->values[i][k] * mat2->values[k][j];
            }
            mat_prod->values[i][j] = sum;
        }
    }

    return mat_prod;
}

// Put randomized values 0-1 on a matrix pointer
void mat_random(matrix *mat)
{
    //srand(time(0));
    for(int i = 0; i < mat->rows; i++)
    {
        for(int j = 0; j < mat->cols; j++)
        {
            mat->values[i][j] = (double)rand() / (double)RAND_MAX;
        } 
    }
}

// Element wise subtraction
matrix* mat_subtract(matrix *mat1, matrix *mat2)
{
    // Since this is an element wise subtraction,
    // Check if both rows and cols are equal
    if (mat1->rows != mat2->rows && mat1->cols != mat2->cols)
    {
        printf("Matrix 1 and 2 cols and/or rows are not equal!\n");
        printf("Matrix 1 size: (%d, %d)\n", mat1->rows, mat1->cols);
        printf("Matrix 2 size: (%d, %d)\n", mat2->rows, mat2->cols);
        exit(1);
    }

    matrix *diff = mat_create(mat1->rows, mat1->cols);
    
    for (int i = 0; i < mat1->rows; i++)
    {
        for (int j = 0; j < mat1->cols; j++)
        {
            diff->values[i][j] = mat1->values[i][j] - mat2->values[i][j];
        }
    }

    return diff;
}

// Element wise power
matrix *mat_power(matrix *mat)
{
    matrix *powered = mat_create(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            powered->values[i][j] = pow(mat->values[i][j], 2);
        }
    }
    return powered; // powered XD
}

// Sum by axis= 1(row), 2(col), 3=all
matrix *mat_sum(matrix *mat, int axis)
{
    if (axis == 1)
    {
        matrix *sum = mat_create(mat->rows, 1);
        for (int i = 0; i < mat->rows; i++)
        {
            double row_sum = 0;
            for (int j = 0; j < mat->cols; j++)
            {
                row_sum += mat->values[i][j];
            }
            sum->values[i][0] += row_sum;
        }
        return sum;
    }
    else if (axis == 2)
    {
        matrix *sum = mat_create(1, mat->cols);
        for (int j = 0; j < mat->cols; j++)
        {
            double col_sum = 0;
            for (int i = 0; i < mat->rows; i++)
            {
                col_sum += mat->values[i][j];
            }
            sum->values[0][j] += col_sum;
        }
        return sum;
    }
    else
    {
        // TODO: sum either row->col or col->row
    }
    return mat;
}

// scale matrix or copy, axis= 1(row), 2(col)
matrix* mat_scale(matrix* mat, int axis, int amount)
{   
    if (axis == 1)
    {
        matrix* scaled = mat_create(amount, mat->cols);
        
        // Copy the row to "amount" rows
        for (int i = 0; i < amount; i++)
        {
            for (int j = 0; j < mat->cols; j++)
            {
                scaled->values[i][j] = mat->values[0][j]; // 0 for first row only
            }
        }
        return scaled;
    }
    return mat;
}

// Element-wise matrix multiplication
matrix* mat_multiply_ew(matrix *mat1, matrix *mat2)
{
    // Since this is an element wise ,
    // Check if both rows and cols are equal
    if (mat1->rows != mat2->rows && mat1->cols != mat2->cols)
    {
        printf("Matrix 1 and 2 cols and/or rows are not equal!\n");
        printf("Matrix 1 size: (%d, %d)\n", mat1->rows, mat1->cols);
        printf("Matrix 2 size: (%d, %d)\n", mat2->rows, mat2->cols);
        exit(1);
    }

    matrix *prod = mat_create(mat1->rows, mat1->cols);
    
    for (int i = 0; i < mat1->rows; i++)
    {
        for (int j = 0; j < mat1->cols; j++)
        {
            prod->values[i][j] = mat1->values[i][j] * mat2->values[i][j];
        }
    }

    return prod;
}

// Scalar division
matrix* mat_divide_by(matrix* mat, double dividend)
{
    matrix* quotient = mat_create(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            quotient->values[i][j] = mat->values[i][j] / dividend;
        }
    }

    return quotient;
}

// Scalar multiplication
matrix* mat_multiply_by(matrix* mat, double amount)
{
    matrix* prod = mat_create(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            prod->values[i][j] = mat->values[i][j] * amount;
        }
    }

    return prod;
}