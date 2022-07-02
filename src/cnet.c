#include "matrix.h"
#include "activation.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(void)
{
    // Working logistic regression
    clock_t tic = clock();

    // INPUT
    matrix* X = matcreate(3, 6);
    //x(1)
    X->values[0][0] = 1;
    X->values[1][0] = 0;
    X->values[2][0] = 1;
    //x(2)
    X->values[0][1] = 0;
    X->values[1][1] = 1;
    X->values[2][1] = 1;
    //x(3)
    X->values[0][2] = 0;
    X->values[1][2] = 0;
    X->values[2][2] = 1;
    //x(4) 
    X->values[0][3] = 1;
    X->values[1][3] = 1;
    X->values[2][3] = 1;
    //x(5) 
    X->values[0][4] = 0;
    X->values[1][4] = 1;
    X->values[2][4] = 1;
    //x(6) m=6
    X->values[0][5] = 1;
    X->values[1][5] = 0;
    X->values[2][5] = 1;

    // GROUND TRUTH
    matrix* y = matcreate(1, 6);
    y->values[0][0] = 0;
    y->values[0][1] = 1;
    y->values[0][2] = 0;
    y->values[0][3] = 1;
    y->values[0][4] = 1;
    y->values[0][5] = 0;

    // WEIGHTS
    matrix* W = matcreate(3, 1);
    W->values[0][0] = 0.1;
    W->values[1][0] = 0.2;
    W->values[2][0] = 0.3;

    // BIASES
    matrix* b = matcreate(1, 1);
    b->values[0][0] = 0.5;

    double alpha = 0.01; // learning rate
    int m = 6; // training examples
    int n = 3; // features

    for (int i = 0; i < 20000; i++)
    {
        matrix *b_expanded = matexpand(b, 2, m);
        matrix *pred = matsigmoid(matadd_ew(matmul(mattrans(W), X), b_expanded));
        matrix* error = matdiv_by(matsum(matpow(matsub_ew(pred, y)), 1), m);
        
        if (i % 1000 == 0)
            printf("[%d] Error: %f\n", i, error->values[0][0]);

        // Gradient descent
        matrix* dz = matsub_ew(pred, y);
        matrix* dw = matdiv_by(matmul(X, mattrans(dz)), m);
        matrix* db = matdiv_by(matsum(dz, 1), m);
        W = matsub_ew(W, matmul_by(dw, alpha));
        b = matsub_ew(b, matmul_by(db, alpha));
    }
    
    // Testing prediction on final weights and b
    matrix *b_expanded = matexpand(b, 2, m);
    matrix* a = matsigmoid(matadd_ew(matmul(mattrans(W), X), b_expanded));
    matprint(a);

    clock_t toc = clock();
    printf("Elapsed: %f seconds\n", ((double)(toc - tic) / CLOCKS_PER_SEC));
}