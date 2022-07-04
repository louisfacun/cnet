/*!
 * Author: Louis Philippe B. Facun
 * Email: louis@louisfacun.com
 */

#include "activation.h"
#include "matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

matrix* matcreate(int rows, int cols)
{
    /* Dynamically allocate a 2d array as a matrix struct.
    
    Parameters:
        rows: (int) Size of rows.
        cols: (int) Size of columns.

    Returns:
        mat: (struct*)
    */

    // Allocate a struct Matrix pointer
    matrix *mat = malloc(sizeof(matrix));

    // Allocate "row" pointers
    mat->values = malloc(rows * sizeof(double*));
    
    // Allocate "columns" pointer per "row" pointer
    for (int i = 0; i < rows; i++)
    {
        mat->values[i] = malloc(cols * sizeof(double));
    }

    // Don't forget to store the size of row and col 
    mat->rows = rows; 
    mat->cols = cols;

    return mat;
}


void matzeros(matrix *mat)
{   
    /* Put zeros to all matrix values.
         
    Parameters:
        mat: (struct*)
    */
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            mat->values[i][j] = 0.0;
        }
    }
}


void matprint(matrix *mat)
{
    /* Display matrix values and size (rows, cols).
         
    Parameters:
        mat: (struct*)

    Example:
        [[0.000 0.000 0.000]
         [0.000 0.000 0.000]]
         Size: (2, 3)
    */
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


void matfree(matrix *mat)
{
    /* Free allocated matrix row and column pointers.
         
    Parameters:
        mat: (struct*)
    */
    for (int i = 0; i < mat->rows; i++)
    {
        // Free column pointers per row
        free(mat->values[i]);
    }
    // Free row pointers
    free(mat->values);

    // Free matrix struct pointer
    free(mat);
}


void matfill_n(matrix *mat)
{
    /* Fill the matrix with 1 to row*col values.
         
    Parameters:
        mat: (struct*)
    */
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


matrix* mattrans(matrix *old_mat)
{   
    /* Transpose a matrix.
         
    Parameters:
        mat: (struct*) Pointer of the matrix to be transposed.

    Returns:
        new_mat: (struct*) Transposed matrix on a new pointer.
    */

    // Cannot directly alter the previous matrix (not sure) 
    // so we need to create a new matrix struct with a reversed size: (col, row)
    matrix *new_mat = matcreate(old_mat->cols, old_mat->rows);
    
    // Use formula new[j][i] := old[i][j]
    for (int i = 0; i < old_mat->rows; i++)
    {
        for (int j = 0; j < old_mat->cols; j++)
        {
            new_mat->values[j][i] = old_mat->values[i][j];
        }
    }
    return new_mat;
}


matrix* matmul(matrix *mat1, matrix *mat2)
{
    /* Get the "matrix product" of two matrices.
         
    Parameters:
        mat1: (struct*)
        mat2: (struct*)

    Returns:
        mat3: (struct*)
    */

    // Check if k are equal (m1[i][k] * m2[k][j] = m3[i][j])
    if (mat1->cols != mat2->rows)
    {
        printf("Matrix k size are not equal!\n");
        exit(1);
    }

    // Since m1[i][k] * m2[k][j] = m3[i][j]
    // Create a matrix with size of (i,j)
    matrix *mat3 = matcreate(mat1->rows, mat2->cols);

    for (int i = 0; i < mat1->rows; i++)
    {
        for (int j = 0; j < mat2->cols; j++)
        {
            double sum = 0;
            for (int k = 0; k < mat2->rows; k++)
            {
                sum += mat1->values[i][k] * mat2->values[k][j];
            }
            mat3->values[i][j] = sum;
        }
    }
    return mat3;
}


void matran(matrix *mat)
{
    /* Put randomized values 0-1 on a given matrix pointer.
         
    Parameters:
        mat: (struct*)
    */

    //srand(time(0));
    for(int i = 0; i < mat->rows; i++)
    {
        for(int j = 0; j < mat->cols; j++)
        {
            mat->values[i][j] = (double)rand() / (double)RAND_MAX;
        } 
    }
}


matrix* matsub_ew(matrix *mat1, matrix *mat2)
{
    /* Element wise subtraction.
         
    Parameters:
        mat1: (struct*)
        mat2: (struct*)

    Returns:
        mat3: (struct*)
    */

    // Since this is an element wise subtraction,
    // Check if both rows and cols are equal
    if (mat1->rows != mat2->rows && mat1->cols != mat2->cols)
    {
        printf("Matrix 1 and 2 cols and/or rows are not equal!\n");
        printf("Matrix 1 size: (%d, %d)\n", mat1->rows, mat1->cols);
        printf("Matrix 2 size: (%d, %d)\n", mat2->rows, mat2->cols);
        exit(1);
    }

    matrix *mat3 = matcreate(mat1->rows, mat1->cols);
    for (int i = 0; i < mat1->rows; i++)
    {
        for (int j = 0; j < mat1->cols; j++)
        {
            mat3->values[i][j] = mat1->values[i][j] - mat2->values[i][j];
        }
    }
    return mat3;
}


matrix* matpow(matrix *mat)
{    
    /* Element wise power (2).
         
    Parameters:
        mat: (struct*)

    Returns:
        mat2: (struct*)
    */
    matrix *mat2 = matcreate(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            mat2->values[i][j] = pow(mat->values[i][j], 2);
        }
    }
    return mat2;
}


matrix* matsum(matrix *mat, int axis)
{
    /* Sum a matrix by axis.
    
    Parameters:
        mat: (struct*)
        axis: (integer)

    Returns:
        sum: (struct*)
    
    Notes:
        axis = 1(row), 2(col), 3=all
    */
    if (axis == 1)
    {
        matrix *sum = matcreate(mat->rows, 1);
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
        matrix *sum = matcreate(1, mat->cols);
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


matrix* matexpand(matrix *mat, int axis, int amount)
{
    /* Expand a matrix by axis.
    
    Parameters:
        mat: (struct*)
        axis: (integer)
        amount: (integer) Amount to expand.

    Returns:
        scaled: (struct*)
    
    Notes:
        axis = 1(row), 2(col)
    */   
    if (axis == 1)
    {
        // TODO: check if row size > 1, otherwise we should not allow scaling row w/ size more than 2
        matrix* scaled = matcreate(amount, mat->cols);
        
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
    else if (axis == 2)
    {
        // TODO: same row checking
        matrix* scaled = matcreate(mat->rows, amount);
        
        // Copy the cols to "amount" cols
        for (int j = 0; j < amount; j++)
        {
            for (int i = 0; i < mat->rows; i++)
            {
                scaled->values[i][j] = mat->values[i][0]; // 0 for first col only
            }
        }
        return scaled;
    }
    return mat;
}


matrix* matmul_ew(matrix *mat1, matrix *mat2)
{
    /* Element-wise matrix multiplication.
    
    Parameters:
        mat1: (struct*)
        mat2: (struct*)

    Returns:
        mat3: (struct*)
    */

    // Since this is an element wise ,
    // Check if both rows and cols are equal
    if (mat1->rows != mat2->rows && mat1->cols != mat2->cols)
    {
        printf("Matrix 1 and 2 cols and/or rows are not equal!\n");
        printf("Matrix 1 size: (%d, %d)\n", mat1->rows, mat1->cols);
        printf("Matrix 2 size: (%d, %d)\n", mat2->rows, mat2->cols);
        exit(1);
    }

    matrix *mat3 = matcreate(mat1->rows, mat1->cols);
    
    for (int i = 0; i < mat1->rows; i++)
    {
        for (int j = 0; j < mat1->cols; j++)
        {
            mat3->values[i][j] = mat1->values[i][j] * mat2->values[i][j];
        }
    }
    return mat3;
}


matrix* matdiv_by(matrix *mat, double amount)
{
    /* Matrix to scalar division.
    
    Parameters:
        mat: (struct*)
        amount: (double) Divide by scalar value.

    Returns:
        mat2: (struct*)
    */
    matrix* mat2 = matcreate(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            mat2->values[i][j] = mat->values[i][j] / amount;
        }
    }
    return mat2;
}


matrix* matmul_by(matrix *mat, double amount)
{
    /* Matrix to scalar multiplication.
    
    Parameters:
        mat: (struct*)
        amount: (double) Multiply by scalar value.

    Returns:
        prod: (struct*)
    */
    matrix* prod = matcreate(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            prod->values[i][j] = mat->values[i][j] * amount;
        }
    }
    return prod;
}


matrix* matsigmoid(matrix *m)
{
    /* Apply element-wise sigmoid using sigmoid() from activation.h
    
    Parameters:
        m: (struct*)

    Returns:
        m2: (struct*)
    */
    matrix* m2 = matcreate(m->rows, m->cols);
    for (int i=0; i<m->rows; i++){
        for (int j=0; j<m->cols; j++){
            m2->values[i][j] = sigmoid(m->values[i][j]);
        }
    }
    return m2;
}


matrix* matadd_ew(matrix *mat1, matrix *mat2)
{
    /* Element-wise matrix addition.
    
    Parameters:
        mat1: (struct*)
        mat2: (struct*)

    Returns:
        mat3: (struct*)
    */

    // Since this is an element wise ,
    // Check if both rows and cols are equal
    if (mat1->rows != mat2->rows && mat1->cols != mat2->cols)
    {
        printf("Matrix 1 and 2 cols and/or rows are not equal!\n");
        printf("Matrix 1 size: (%d, %d)\n", mat1->rows, mat1->cols);
        printf("Matrix 2 size: (%d, %d)\n", mat2->rows, mat2->cols);
        exit(1);
    }

    matrix *mat3 = matcreate(mat1->rows, mat1->cols);
    for (int i = 0; i < mat1->rows; i++)
    {
        for (int j = 0; j < mat1->cols; j++)
        {
            mat3->values[i][j] = mat1->values[i][j] + mat2->values[i][j];
        }
    }
    return mat3;
}


double matsqz(matrix *mat)
{
    /* Get (1, 1) matrix value to scalar double value.
    
    */
    // Check if it's actually a 1 by 1 matrix
    if (mat->rows != 1 || mat->cols != 1)
    {
        printf("Error: cannot use matsqz() on size (%d, %d).\n", mat->rows, mat->cols);
        exit(1);
    }
    return mat->values[0][0];
}

matrix* matcpy(matrix *mat)
{
    matrix* mat2 = matcreate(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            mat2->values[i][j] = mat->values[i][j];
        }
    }
    return mat2;
}

// Mat by vec addition
matrix* mataddvec_by(matrix *mat1, matrix *mat2)
{
    matrix* mat3 = matcreate(mat1->rows, mat1->cols);
    
    // Size checking

    // None of both rows and cols matches
    if (mat1->rows != mat2->rows && mat1->cols != mat2->cols)
    {
        printf("Error: cannot broadcast, none of the sizes match: (%d, %d) != (%d, %d).\n", mat1->rows, mat1->cols, mat2->rows, mat2->cols);
        exit(1);
    }
    // Sanity check
    else if (mat1->rows == mat2->rows && mat1->cols == mat2->cols)
    {
        printf("Error: do not use this function, both sizes match: (%d, %d) == (%d, %d).\n", mat1->rows, mat1->cols, mat2->rows, mat2->cols);
        exit(1);
    }
    // Row size matches, broadcast horizontally
    else if (mat1->rows == mat2->rows && mat1->cols != mat2->cols)
    {
        for (int j = 0; j < mat1->cols; j++)
        {
            for (int i = 0; i < mat1->rows; i++)
            {
                mat3->values[i][j] = mat1->values[i][j] + mat2->values[i][0];
            }
        }
        return mat3;
    }
    
    // Col size matches, broadcast vertically
    else if (mat1->rows != mat2->rows && mat1->cols == mat2->cols)
    {
        for (int i = 0; i < mat1->rows; i++)
        {
            for (int j = 0; j < mat1->cols; j++)
            {
                mat3->values[i][j] = mat1->values[i][j] + mat2->values[0][j];
            }
        }
        return mat3;
    }
    return mat3;
}

/*
    TODO:
    1. Simplify element-wise matrix operations:

    matops_ew(matrix1, matrix2, operation)
    {
        switch (operation)
            case 1:
                do addition
            case 2:
                do subtraction
            case 3:
                do multiplication
            case 4:
                do division
    }

    Then, in main code, call matops_ew().
    But the additional parameter makes it complicated.

    OR

    Call matops_ew() on each function:
    
    E.g. matadd_ew()
         {
            matops_ew(m1, m2, ops)
         }

    So, in main code, we can call matadd_ew(), matsub_ew etc..
    Also do it on matrix to scalar operations.
    
*/