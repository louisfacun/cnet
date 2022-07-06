/*!
 * Author: Louis Philippe B. Facun
 * Email: louis@louisfacun.com
 */

// working full gradient descent
// problem: still figuring what allocated memory should be freed

#include "input.h"
#include "matrix.h"
#include "network.h"
#include "parameter.h"
#include "layer.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void)
{
    printf("Starting cnet...\n\n");
    clock_t tic1 = clock();
    
    // 1. Load input: X and y
    int m = 6;
    int n = 3;
    input *in = inload("data/streetlight/data.txt", n, m);

    //input *in = inload("data/mnist/data.csv", n, m); // m1000 n784

    printf("Data loaded...\n");
    //matrix *X = matdiv_by(in->X, 255);
    matrix *X = in->X;

    // 2. Specify layer sizes
    // Layers: {input, hidden1, hidden2, output}
    int layers[] = {n, 24, 24, 1};
    int L = 4;

    // 3. Initialize weights and bias
    parameter **params = param_init(layers, L);
    printf("Parameters initialized...\n");

    int iteration = 50000;

    for (int i = 0; i < iteration; i++)
    {
        // 4. Forward
        network_output *network_o = network_forward(X, params, L);
        
        // 5. compute cost
        double cost = netcost(network_o->AL, in->y);
        if (i % 1000 == 0)
        {
            printf("[%d] Cost computed: %f\n", i, cost);
        }

        // 6. backprop
        network_gradient **network_gs = network_backward(network_o->AL, in->y, network_o->layer_fs, L);
        
        // 7. update param
        for (int j=0; j < L-1; j++)
        {
            params[j]->W = matsub_ew(params[j]->W, matmul_by(network_gs[j]->dW, 0.1));
            params[j]->b = matsub_ew(params[j]->b, matmul_by(network_gs[j]->db, 0.1));
        }

        network_output_free(network_o, L-1);
        network_gradients_free(network_gs, L-1);
        //exit(1);
    }
    //network_output *network_o = network_forward(X, params, L);

    // Expect close to 0, 1, 0, 1, 1, 0
    //matprint(network_o->AL);

    clock_t toc1 = clock();
    printf("Elapsed: %f seconds\n", ((double)(toc1 - tic1) / CLOCKS_PER_SEC));
}