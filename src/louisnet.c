#include "matrix.h"
#include "activation.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int main(void)
{
    clock_t tic = clock();

    // INPUT
    matrix* X = mat_create(3, 4);
    //x(1)
    X->values[0][0] = 1;
    X->values[1][0] = 0;
    X->values[2][0] = 1;
    //x(2)
    X->values[0][1] = 1;
    X->values[1][1] = 1;
    X->values[2][1] = 1;
    //x(3)
    X->values[0][2] = 0;
    X->values[1][2] = 1;
    X->values[2][2] = 1;
    //x(4) m=4
    X->values[0][3] = 1;
    X->values[1][3] = 1;
    X->values[2][3] = 0;

    // GROUND TRUTH
    matrix* y = mat_create(1, 4);
    y->values[0][0] = 0;
    y->values[0][1] = 1;
    y->values[0][2] = 1;
    y->values[0][3] = 1;

    // WEIGHTS
    matrix* W = mat_create(1, 3);
    W->values[0][0] = 0.5;
    W->values[0][1] = 0.2;
    W->values[0][2] = 0.5;

    double alpha = 0.01;

    for (int i = 0; i < 2000; i++)
    {
        
        // PRODUCT
        matrix* a = mat_multiply(W, X);
        //mat_print(a);
        
        matrix* error = mat_divide_by(mat_sum(mat_power(mat_subtract(a, y)), 1), 4);
       
        printf("[%d] Error: %f\n", i, error->values[0][0]);
        
        matrix* delta = mat_subtract(a, y);
        matrix* scaled_delta = mat_scale(delta, 1, 3);
        matrix* prod_delta = mat_multiply_ew(scaled_delta, X);
        matrix* sum_delta = mat_sum(prod_delta, 1);
        matrix* final_delta = mat_transpose(mat_divide_by(sum_delta, 4));

        W = mat_subtract(W, mat_multiply_by(final_delta, alpha));
    }
    matrix* a = mat_multiply(W, X);
    mat_print(a);

    //free(X);
    //free(error);
    //free(y);
    //free(W);
    //free(a);

    clock_t toc = clock();
    printf("Elapsed: %f seconds\n", ((double)(toc - tic) / CLOCKS_PER_SEC));
    
}