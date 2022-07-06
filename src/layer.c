/*!
 * Author: Louis Philippe B. Facun
 * Email: louis@louisfacun.com
 */

#include "layer.h"
#include "matrix.h"

#include <string.h>
#include <stdlib.h>

layer_forward_linear* linear_forward(matrix *A, matrix *W, matrix *b)
{
    /* Linear part of forward propagation (computes Z[l] - single Z) */

    layer_forward_linear *layer_fl = malloc(sizeof(layer_forward_linear));

    // Compute linear output
    matrix *Z = mataddvec_by(matmul(W, A), b);

    // Linear layer output
    layer_fl->Z = Z;
    // Cache 
    layer_fl->A = A;
    layer_fl->W = W;
    layer_fl->b = b;

    //matfree(A); //error
    //matfree(W); //error
    //matfree(b); //error
    //matfree(Z); //error

    return layer_fl;
}

layer_forward* activation_forward(matrix *A, matrix *W, matrix *b, char *activation)
{
    /* Activation part of forward propagation (computes A[l] - single activation) */

    // Call linear forward Z and get the cache
    layer_forward_linear *layer_fl = linear_forward(A, W, b);

    // Store both forward linear and activation
    layer_forward *layer_f = malloc(sizeof(layer_forward));
    layer_forward_activation *layer_fa = malloc(sizeof(layer_forward_activation));

    matrix *A_new;
    // Get A_new based on activation provided
    if (strcmp(activation, "sigmoid") == 0)
    {
        A_new = matsigmoid(layer_fl->Z);    
    }
    else if (strcmp(activation, "relu") == 0)
    {
        A_new = matrelu(layer_fl->Z);  
    }

    // Activation layer output
    layer_fa->A_new = A_new;
    layer_fa->Z = layer_fl->Z; // Cache

    layer_f->layer_fl = layer_fl;
    layer_f->layer_fa = layer_fa;

    //matfree(A_new); //error

    return layer_f;
}

layer_backward* linear_backward(matrix *dZ, layer_forward_linear *layer_fl)
{
    matrix *A_prev = layer_fl->A;
    matrix *W = layer_fl->W;

    int m = A_prev->cols;
    
    matrix *dW = matdiv_by(matmul(dZ, mattrans(A_prev)), m);
    matrix *db =  matdiv_by(matsum(dZ, 0), m);
    matrix *dA_prev = matmul(mattrans(W), dZ);

    layer_backward *layer_b = malloc(sizeof(layer_backward));
    layer_b->dA_prev = dA_prev;
    layer_b->dW = dW;
    layer_b->db = db;
    
    //matfree(dA_prev); //error

    return layer_b;
}


layer_backward* activation_backward(matrix *dA, layer_forward *layer_f, char *activation)
{
    matrix *dZ;
    layer_backward *layer_b;
    if (strcmp(activation, "sigmoid") == 0)
    {
        dZ = matsigmoid_backward(dA, layer_f->layer_fa->Z);
        layer_b = linear_backward(dZ, layer_f->layer_fl);
    }
    else if (strcmp(activation, "relu") == 0)
    {
        dZ = matrelu_backward(dA, layer_f->layer_fa->Z);
        layer_b = linear_backward(dZ, layer_f->layer_fl);
    }
    
    matfree(dZ);
    return layer_b;
}

void linear_forwards_free(layer_forward **layer_f, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
    {
        linear_forward_linear_free(layer_f[i]->layer_fl);
        linear_forward_activation_free(layer_f[i]->layer_fa);
    }
    free(layer_f);
    layer_f = NULL;
}

void linear_forward_linear_free(layer_forward_linear *layer_fl)
{
    matfree(layer_fl->Z);
    //matfree(layer_fl->A); //cannot free, pointer to X?
    //matfree(layer_fl->W); //cannot free, pointer to Wi
    //matfree(layer_fl->b); //cannot free, pointer to bi
    //free(layer_fl);
    //layer_fl = NULL;
}

void linear_forward_activation_free(layer_forward_activation *layer_fa)
{
    //matfree(layer_fa->A_new);
    //matfree(layer_fa->Z);
    //free(layer_fa);
    //layer_fa = NULL;
}