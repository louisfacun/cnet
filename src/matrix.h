#ifndef MATRIX_H
#define MATRIX_H

/*
 * Dynamically allocate multi-dimensional arrays reference: http://c-faq.com/aryptr/dynmuldimary.html
 * However, we used struct against without the struct version: (double **values = malloc(...))
 * Because we want to store row and col sizes so we won't need to count it everytime by looping.
 * Meaning, no need to create a function that counts the row and sizes every time.
 * Edit: I'm not sure if you can count malloced array!
 */

typedef struct
{
    double **values; // Row pointers
    int rows;        // Row size
    int cols;        // Column size
}
matrix;

matrix* mat_create(int, int);
void mat_zeros(matrix*);
void mat_print(matrix*);
void mat_free(matrix*);
void mat_fill_num(matrix*);
matrix* mat_transpose(matrix*);
matrix* mat_multiply(matrix*, matrix*);
void mat_random(matrix*);
matrix* mat_subtract(matrix*, matrix*);
matrix* mat_init(double*, int, int);
matrix* mat_power(matrix*);
matrix* mat_sum(matrix*, int);
matrix* mat_scale(matrix*, int, int);
matrix* mat_multiply_ew(matrix*, matrix*);
matrix* mat_divide_by(matrix*, double);
matrix* mat_multiply_by(matrix*, double);

#endif