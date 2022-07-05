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
    matrix *res = malloc(sizeof(matrix));
    res->values = malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        res->values[i] = malloc(cols * sizeof(double));
    } 
    res->rows = rows; 
    res->cols = cols;
    return res;
}

// put zeros to an existing matrix
void matzeros(matrix *mat)
{   
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            mat->values[i][j] = 0.0;
        }
    }
}

// put 1 to n values
void matfill_n(matrix *mat)
{
    int z = 1;
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            mat->values[i][j] = z;
            z++;
        }
    }
}

void matran(matrix *mat)
{
    //srand(time(0));
    for(int i = 0; i < mat->rows; i++) {
        for(int j = 0; j < mat->cols; j++) {
            mat->values[i][j] = (double)rand() / (double)RAND_MAX;
        } 
    }
}

void matprint(matrix *mat)
{
    printf("[");
    for (int i = 0; i < mat->rows; i++) {
        printf("%s", i == 0 ? "[" : " [");
        for (int j = 0; j < mat->cols; j++) {
            printf("%10.8f%s", mat->values[i][j], j == (mat->cols-1) ? "" : " ");
        }
        printf("%s", i == (mat->rows-1) ? "]" : "]\n");
    }
    printf("]\n");
    printf(" Size: (%d, %d)\n\n", mat->rows, mat->cols);
}

void matfree(matrix *mat)
{
    for (int i = 0; i < mat->rows; i++) {
        free(mat->values[i]);
    }
    free(mat->values);
    free(mat);
}

matrix* mattrans(matrix *mat)
{   
    matrix *res = matcreate(mat->cols, mat->rows);
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            res->values[j][i] = mat->values[i][j];
        }
    }
    return res;
}

// special matrix product
matrix* matmul(matrix *mat1, matrix *mat2)
{
    if (mat1->cols != mat2->rows) {
        printf("Error: matrix k size are not equal: (%d, %d) != (%d, %d)\n", mat1->rows, mat1->cols, mat2->rows, mat2->cols);
        exit(1);
    }
    matrix *res = matcreate(mat1->rows, mat2->cols);
    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat2->cols; j++) {
            double sum = 0;
            for (int k = 0; k < mat2->rows; k++){
                sum += mat1->values[i][k] * mat2->values[k][j];
            }
            res->values[i][j] = sum;
        }
    }
    return res;
}

matrix* matpow(matrix *mat, int val)
{
    matrix *res = matcreate(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            res->values[i][j] = pow(mat->values[i][j], val);
        }
    }
    return res;
}

// sum by row(0) or col(1)
matrix* matsum(matrix *mat, int axis)
{
    matrix *res = NULL;
    if (axis == 0) {
        res = matcreate(mat->rows, 1);
        for (int i = 0; i < mat->rows; i++) {
            double row_sum = 0;
            for (int j = 0; j < mat->cols; j++) {
                row_sum += mat->values[i][j];
            }
            res->values[i][0] += row_sum;
        }
        return res;
    } else if (axis == 1) {
        res = matcreate(1, mat->cols);
        for (int j = 0; j < mat->cols; j++) {
            double col_sum = 0;
            for (int i = 0; i < mat->rows; i++) {
                col_sum += mat->values[i][j];
            }
            res->values[0][j] += col_sum;
        }
        return res;
    } else {
        // TODO: sum either row->col or col->row
    }
    return res;
}

// matrix to matrix element-wise multiplication
matrix* matmul_ew(matrix *mat1, matrix *mat2)
{
    if (!matisequal(mat1, mat2)) {
        errsize(mat1->rows, mat1->cols, mat2->rows, mat2->cols);
        exit(1);
    }
    matrix *res = matcreate(mat1->rows, mat1->cols);
    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat1->cols; j++) {
            res->values[i][j] = mat1->values[i][j] * mat2->values[i][j];
        }
    }
    return res;
}

// matrix to scalar division
matrix* matdiv_by(matrix *mat, double val)
{
    matrix* res = matcreate(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            res->values[i][j] = mat->values[i][j] / val;
        }
    }
    return res;
}

// matrix to scalar multiplication
matrix* matmul_by(matrix *mat, double val)
{
    matrix* res = matcreate(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            res->values[i][j] = mat->values[i][j] * val;
        }
    }
    return res;
}

// apply element-wise sigmoid
matrix* matsigmoid(matrix *mat)
{
    matrix* res = matcreate(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            res->values[i][j] = sigmoid(mat->values[i][j]);
        }
    }
    return res;
}

// apply element-wise relu
matrix* matrelu(matrix *mat)
{
    matrix* res = matcreate(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            res->values[i][j] = relu(mat->values[i][j]);
        }
    }
    return res;
}

// apply element-wise logarithm
matrix* matlog(matrix *mat)
{
    matrix* res = matcreate(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            res->values[i][j] = log(mat->values[i][j]);
        }
    }
    return res;
}

// matrix to matrix element-wise addition
matrix* matadd_ew(matrix *mat1, matrix *mat2)
{
    if (!matisequal(mat1, mat2)) {
        errsize(mat1->rows, mat1->cols, mat2->rows, mat2->cols);
        exit(1);
    }
    matrix *res = matcreate(mat1->rows, mat1->cols);
    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat1->cols; j++) {
            res->values[i][j] = mat1->values[i][j] + mat2->values[i][j];
        }
    }
    return res;
}

// squeeze matrix into double
double matsqz(matrix *mat)
{
    if (mat->rows != 1 || mat->cols != 1) {
        printf("Error: cannot use matsqz() on size (%d, %d).\n", mat->rows, mat->cols);
        exit(1);
    }
    return mat->values[0][0];
}

matrix* matcpy(matrix *mat)
{
    matrix* res = matcreate(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            res->values[i][j] = mat->values[i][j];
        }
    }
    return res;
}

// matrix to vector addition
matrix* mataddvec_by(matrix *mat1, matrix *mat2)
{
    matrix* res = matcreate(mat1->rows, mat1->cols);
    if (!matisequal(mat1, mat2)) {
        printf("Error: cannot broadcast, none of the sizes match: (%d, %d) != (%d, %d).\n", mat1->rows, mat1->cols, mat2->rows, mat2->cols);
        exit(1);
    } else if (matisequal(mat1, mat2)) {
        printf("Error: do not use this function, both sizes match: (%d, %d) == (%d, %d).\n", mat1->rows, mat1->cols, mat2->rows, mat2->cols);
        exit(1);
    }
    // column size matches, broadcast by row
    else if (mat1->rows != mat2->rows && mat1->cols == mat2->cols)
    {
        matrix *matvec = matexpand(mat2, 0, mat1->rows);
        res = matadd_ew(mat1, matvec);
        return res;
    }
    // row size matches, broadcast by column
    else if (mat1->rows == mat2->rows && mat1->cols != mat2->cols)
    {
        matrix *matvec = matexpand(mat2, 1, mat1->cols);
        res = matadd_ew(mat1, matvec);
        return res;
    }
    return res;
}

// check if matrix 1 and 2 row and size are equal
int matisequal(matrix *mat1, matrix *mat2)
{
   return ((mat1->rows == mat2->rows && mat1->cols == mat2->cols) ? 1 : 0);
}

void errsize(int m1r, int m1c, int m2r, int m2c)
{
    printf("Error: unequal size: (%d, %d) != (%d, %d)\n", m1r, m1c, m2r, m2c);
}

// matrix to matrix element-wise subtraction
matrix* matsub_ew(matrix *mat1, matrix *mat2)
{
    if (!matisequal(mat1, mat2)) {
        errsize(mat1->rows, mat1->cols, mat2->rows, mat2->cols);
        exit(1);
    }
    matrix *res = matcreate(mat1->rows, mat1->cols);
    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat1->cols; j++) {
            res->values[i][j] = mat1->values[i][j] - mat2->values[i][j];
        }
    }
    return res;
}

// scalar to matrix subtraction
matrix* matsub_to(matrix *mat, double val)
{
    matrix *res = matcreate(mat->rows, mat->cols);
    matrix *matval = matexpand_s(val, mat->rows, mat->cols);
    res = matsub_ew(matval, mat);
    return res;
}

// matrix to scalar subtraction
matrix* matsub_by(matrix *mat, double val)
{
    matrix *res = matcreate(mat->rows, mat->cols);
    matrix *matval = matexpand_s(val, mat->rows, mat->cols);
    res = matsub_ew(mat, matval);
    return res;
}

// expand a scalar with size by copying
matrix* matexpand_s(double val, int rows, int cols)
{
    matrix* res = matcreate(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res->values[i][j] = val;
        }
    } 
    return res; 
}

// expand a vector with size by copying
matrix* matexpand(matrix *mat, int axis, int size)
{
    matrix* res = NULL;
    if (axis == 0) {
        res = matcreate(size, mat->cols);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < mat->cols; j++) {
                res->values[i][j] = mat->values[0][j]; 
            }
        } 
        return res;
    } 
    else if (axis == 1) {
        res = matcreate(mat->rows, size);
        for (int j = 0; j < size; j++) {
            for (int i = 0; i < mat->rows; i++) {
                res->values[i][j] = mat->values[i][0];
            }
        } 
        return res;
    } 
    return res;
}