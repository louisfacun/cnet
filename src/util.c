/*!
 * Author: Louis Philippe B. Facun
 * Email: louis@louisfacun.com
 */

#include "util.h"

#include <stdlib.h>
#include <string.h>


void param_update(parameter **params, network_gradient **network_gs, double learning_rate, int l)
{
    int L = l - 1;
    int Li = L - 1; 

    for (int i = 0; i < Li; i++)
    {
        //printf("Current: %d\n", i); 
        //matprint(params[i]->W);
        //matprint(network_gs[i]->dW);
        //params[i]->W = matsub_ew(params[i]->W, matmul_by(network_gs[i]->dW, learning_rate));
        //params[i]->b = matsub_ew(params[i]->b, matmul_by(network_gs[i]->db, learning_rate));
        params[i]->W = matsub_ew(params[i]->W, matmul_by(network_gs[i]->dW, 0.01));
        params[i]->b = matsub_ew(params[i]->b, matmul_by(network_gs[i]->db, 0.01));
    }
}