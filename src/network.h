/*!
 * Author: Louis Philippe B. Facun
 * Email: louis@louisfacun.com
 */

#ifndef NETWORK_H
#define NETWORK_H

#include "matrix.h"
#include "layer.h"
#include "parameter.h"

typedef struct
{
    matrix *AL;
    layer_forward **layer_fs; 
}
network_output; // should be network_prediction_output
                // or network_forward_output

typedef struct
{
    matrix *dA;
    matrix *dW;
    matrix *db;
}
network_gradient; // network_backward_output

network_output* network_forward(matrix *X, parameter **params, int l);
network_gradient** network_backward(matrix *AL, matrix *Y, layer_forward **layer_f, int l);
double netcost(matrix *A, matrix *y);

void network_gradients_free(network_gradient **network_gs, int arr_size);
void network_output_free(network_output *network_o, int arr_size);

#endif