#ifndef MATRIX_H
#define MATRIX_H

typedef struct
{
    double **values;
    int rows;
    int cols;
}
matrix;

matrix* matcreate(int rows, int cols);
void matzeros(matrix *mat);
void matprint(matrix *mat);
void matfree(matrix *mat);
void matfill_n(matrix *mat);
matrix* mattrans(matrix *mat);
void matran(matrix *mat);

matrix* matmul(matrix *mat1, matrix *mat2);
matrix* matadd_ew(matrix *mat1, matrix *mat2);
matrix* matsub_ew(matrix *mat1, matrix *mat2);
matrix* matmul_ew(matrix *mat1, matrix *mat2);
//matrix* matdiv_ew(matrix *mat1, matrix *mat2);
matrix* matsum(matrix *mat, int axis);
matrix* matexpand(matrix *mat, int axis, int amount);
//matrix* matadd_by(matrix *mat, double amount);
//matrix* matsub_by(matrix *mat, double amount);
matrix* matmul_by(matrix *mat, double amount);
matrix* matdiv_by(matrix *mat, double amount);
matrix* matpow(matrix *mat);
matrix* matsigmoid(matrix *mat);
double matsqz(matrix *mat);

#endif