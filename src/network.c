/*!
 * Author: Louis Philippe B. Facun
 * Email: louis@louisfacun.com
 */

#include "network.h"
#include "matrix.h"
#include "parameter.h"

#include <string.h>

matrix* netforward_z(matrix *A, matrix *W, matrix *b)
{
    /* Linear part of forward propagation (computes Z[l] - single Z).
    
    Parameters:
        A: (struct*) Activations values from previous layer.
        W: (struct*) Weights matrix.
        b: (struct*) Biases matrix.

    Returns:
        Z: (struct*)
    */

    matrix *Z = mataddvec_by(matmul(W, A), b);
    return Z;
}


matrix* netforward_a(matrix *A, matrix *W, matrix *b, char *activation)
{
    /* Activation part of forward propagation (computes A[l] - single activation).
    
    Parameters:

    Returns:
    */

    matrix *Z = netforward_z(A, W, b);
    matrix *A_new;

    if (strcmp(activation, "sigmoid") == 0)
    {
        A_new = matsigmoid(Z);    
    }
    
    return A_new;
}


matrix* netforward(matrix *X, parameter **params, int l)
{
    /* Whole forward propagation on all layers (computes A[L] - last activation).
    
    Parameters:

    Returns:
    */

    // Make input X as starting activation A
    matrix *A = X;

    // Hidden layers
    // Assuming that activations is similar on all hidden layers
    for (int i = 0; i < (l-2); i++)
    {
        //A_prev = A;
        A = netforward_a(A, params[i]->W, params[i]->b, "sigmoid");
    }
    
    // Output layer
    A = netforward_a(A, params[2]->W, params[2]->b, "sigmoid");
    return A;
}


double netcost(matrix *A, matrix *y)
{
    /* Compute cost (error per training example divided by m).
    
    Parameters:

    Returns:
    */

    int m = y->cols;
    matrix *cost = matdiv_by(matsum(matpow(matsub_ew(A, y)), 1), m);
    double cost_scalar = matsqz(cost);
    return cost_scalar;
}