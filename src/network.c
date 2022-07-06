/*!
 * Author: Louis Philippe B. Facun
 * Email: louis@louisfacun.com
 */

#include "network.h"
#include "activation.h"
#include "layer.h"
#include "matrix.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define EPSILON 0.0000001

network_output* network_forward(matrix *X, parameter **params, int l) // l=4 including input
{
    /* Whole forward propagation on all layers (computes A[L] - last activation)*/
    network_output *network_o = malloc(sizeof(network_output));

    // Create an array of struct `layer_as` to store caches
    network_o->layer_fs = malloc((l-1) * sizeof(layer_forward*));
   
    // Make input X as starting activation A
    matrix *A = X;

    // For hidden layers, assuming that activations is the same on all hidden layers
    for (int i = 0; i < (l-2); i++)
    {
        layer_forward *layer_f = activation_forward(A, params[i]->W, params[i]->b, "relu");

        // Extract current A val and prepare for next loop
        A = layer_f->layer_fa->A_new;

        // Add caches to array
        // Create cache single element
        network_o->layer_fs[i] = malloc(sizeof(layer_forward));

        // Store linear layer output (Z, AWbZ)
        network_o->layer_fs[i]->layer_fl = malloc(sizeof(layer_forward_linear));
        network_o->layer_fs[i]->layer_fl->Z = layer_f->layer_fl->Z; // linear output
        network_o->layer_fs[i]->layer_fl->A = layer_f->layer_fl->A; // cache
        network_o->layer_fs[i]->layer_fl->W = layer_f->layer_fl->W; // cache
        network_o->layer_fs[i]->layer_fl->b = layer_f->layer_fl->b; // cache

        // Create cache->activation_cache
        network_o->layer_fs[i]->layer_fa = malloc(sizeof(layer_forward_activation));
        network_o->layer_fs[i]->layer_fa->A_new = layer_f->layer_fa->A_new; // activation output
        network_o->layer_fs[i]->layer_fa->Z     = layer_f->layer_fa->Z;     // cache
    }
   
    // Output layer
    layer_forward *layer_f = activation_forward(A, params[l-2]->W, params[l-2]->b, "sigmoid");

    // Add caches to array
    int i = l-2; // last index

    // Create cache single element
    network_o->layer_fs[i] = malloc(sizeof(layer_forward));

    // Store linear layer output (Z, AWbZ)
    network_o->layer_fs[i]->layer_fl = malloc(sizeof(layer_forward_linear));
    network_o->layer_fs[i]->layer_fl->Z = layer_f->layer_fl->Z; // linear output
    network_o->layer_fs[i]->layer_fl->A = layer_f->layer_fl->A; // cache
    network_o->layer_fs[i]->layer_fl->W = layer_f->layer_fl->W; // cache
    network_o->layer_fs[i]->layer_fl->b = layer_f->layer_fl->b; // cache

    // Create cache->activation_cache
    network_o->layer_fs[i]->layer_fa = malloc(sizeof(layer_forward_activation));
    network_o->layer_fs[i]->layer_fa->A_new = layer_f->layer_fa->A_new; // activation output
    network_o->layer_fs[i]->layer_fa->Z     = layer_f->layer_fa->Z;     // cache
    
    // Activation on last layer
    network_o->AL = layer_f->layer_fa->A_new;

    // matfree(A); //error
    return network_o;
}


double netcost(matrix *AL, matrix *Y)
{
    /* Compute cost (error per training example divided by m). 
    */

    // Get m size from y
    int m = Y->cols;

    // Compute cost
    matrix *addend1 = matmul_ew(Y, matlog(matadd_by(AL, EPSILON)));
    matrix *addend2 = matmul_ew(matsub_to(Y, 1), matlog(matadd_by(matsub_to(AL, 1), EPSILON)));
    matrix *cross_entropy = matadd_ew(addend1, addend2);
    
    matrix *cost = matdiv_by(matsum(cross_entropy, 0), -1*m);

    // Convert the final matrix (1, 1) to scalar double
    double cost_scalar = matsqz(cost);

    matfree(addend1);
    matfree(addend2);
    matfree(cross_entropy);
    matfree(cost);

    return cost_scalar;
}


network_gradient** network_backward(matrix *AL, matrix *Y, layer_forward **layer_f, int l)
{
    int L = l - 1;
    int Li = L - 1; // for indexing
    network_gradient **network_gs = malloc((L) * sizeof(network_gradient*));

    // Initialize backprop
    matrix *dAL = matmul_by(matsub_ew(matdiv_ew(Y, AL), matdiv_ew(matsub_to(Y, 1), matsub_to(AL, 1))), -1);
    
    //layer_forward *current_layer_f = layer_f[L-1];
    layer_backward *layer_b = activation_backward(dAL, layer_f[L-1], "sigmoid");
  
    // Save grad on last layer
    network_gs[Li] = malloc(sizeof(network_gradient));
    network_gs[Li]->dA = layer_b->dA_prev;
    network_gs[Li]->dW = layer_b->dW;
    network_gs[Li]->db = layer_b->db;

    for (int i = Li-1; i >= 0; i--)
    {
        //printf("Checkpoint: %d %d\n", i, i+1);
        //layer_forward *current_layer_f = layer_f[i];
        layer_backward *layer_b = activation_backward(network_gs[i+1]->dA, layer_f[i], "relu");

        network_gs[i] = malloc(sizeof(network_gradient));
        network_gs[i]->dA = layer_b->dA_prev;
        network_gs[i]->dW = layer_b->dW;
        network_gs[i]->db = layer_b->db;
    }

    matfree(dAL);

    return network_gs;
}

void network_gradients_free(network_gradient **network_gs, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
    {
        matfree(network_gs[i]->dA);
        matfree(network_gs[i]->dW);
        matfree(network_gs[i]->db);
        free(network_gs[i]);
    }
    free(network_gs);
    network_gs = NULL;
}

void network_output_free(network_output *network_o, int arr_size)
{
    matfree(network_o->AL);

    linear_forwards_free(network_o->layer_fs, arr_size);

    free(network_o);
    network_o = NULL;
}