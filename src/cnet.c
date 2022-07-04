/*!
 * Author: Louis Philippe B. Facun
 * Email: louis@louisfacun.com
 */

#include "input.h"
#include "matrix.h"
#include "network.h"
#include "parameter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void)
{
    printf("Starting cnet...\n\n");
    clock_t tic = clock();
    
    // 1. Load input: X and y
    int m = 6;
    int n = 3;
    input *in = inload("data/streetlight/data.txt", n, m);
    //matprint(in->X);
    //matprint(in->y);

    // 2. Specify layer sizes
    // Layers: {input, hidden1, hidden2, output}
    int layers[] = {n, 4, 5, 1};
    int L = 4;

    // 3. Initialize weights and bias
    parameter** params = param_init(layers, L);
    //matprint(params[0]->W);
    //matprint(params[0]->b);

    // 4. Forward
    matrix *A = netforward(in->X, params, L);
    matprint(A);
    double cost = netcost(A, in->y);
    printf("Cost: %f\n", cost);

    clock_t toc = clock();
    printf("Elapsed: %f seconds\n", ((double)(toc - tic) / CLOCKS_PER_SEC));
}