/*!
 * Author: Louis Philippe B. Facun
 * Email: louis@louisfacun.com
 */

#ifndef LAYER_H
#define LAYER_H

#include "matrix.h"

typedef struct
{
    matrix *Z;

    // For caching
    matrix *A;
    matrix *W;
    matrix *b;
}
layer_forward_linear; 

typedef struct
{
    matrix *A_new;

    // For caching
    matrix *Z;
}
layer_forward_activation; 

typedef struct
{
    layer_forward_linear *layer_fl;
    layer_forward_activation *layer_fa;
}
layer_forward;

typedef struct
{
    matrix *dA_prev;
    matrix *dW;
    matrix *db;
}
layer_backward;



layer_forward_linear*
linear_forward(matrix *A, matrix *W, matrix *b);

layer_forward*
activation_forward(matrix *A, matrix *W, matrix *b, char *activation);

layer_backward*
linear_backward(matrix *dZ, layer_forward_linear *layer_fl);

layer_backward* 
activation_backward(matrix *dA, layer_forward *layer_f, char *activation);

void linear_forwards_free(layer_forward **layer_f, int arr_size);
void linear_forward_linear_free(layer_forward_linear *layer_fl);
void linear_forward_activation_free(layer_forward_activation *layer_fa);

#endif
