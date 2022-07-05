/*!
 * Author: Louis Philippe B. Facun
 * Email: louis@louisfacun.com
 */

#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    double **values;
    int rows;
    int cols;
} matrix;

matrix* matcreate(int rows, int cols);
void matzeros(matrix *mat);
void matprint(matrix *mat);
void matfree(matrix *mat);
void matfill_n(matrix *mat);
matrix* mattrans(matrix *mat);
void matran(matrix *mat);

matrix* matmul(matrix *mat1, matrix *mat2);
matrix* matadd_ew(matrix *mat1, matrix *mat2);
matrix* matmul_ew(matrix *mat1, matrix *mat2);
matrix* matsum(matrix *mat, int axis);
matrix* matmul_by(matrix *mat, double val);
matrix* matdiv_by(matrix *mat, double val);
matrix* matpow(matrix *mat, int val);
matrix* matsigmoid(matrix *mat);
matrix* matrelu(matrix *mat);
matrix* matlog(matrix *mat);
double matsqz(matrix *mat);
matrix* matcpy(matrix *mat);
matrix* mataddvec_by(matrix *mat1, matrix *mat2);

matrix* matsub_ew(matrix *mat1, matrix *mat2);
matrix* matsub_to(matrix *mat, double val);
matrix* matsub_by(matrix *mat, double val);
matrix* matexpand_s(double val, int rows, int cols);
matrix* matexpand(matrix *mat, int axis, int size);
int matisequal(matrix *mat1, matrix *mat2);
void errsize(int m1r, int m1c, int m2r, int m2c);

#endif