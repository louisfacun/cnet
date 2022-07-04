/*!
 * Author: Louis Philippe B. Facun
 * Email: louis@louisfacun.com
 */

#include "matrix.h"
#include "parameter.h"

parameter** param_init(int layers[], int l)
{   
    // Create a dynamically allocated array of `parameter` struct pointer
    // We used l-1 or number of layer-1 since we want l-1 size array.
    // E.g. if l = 4 then we need (4-1=3) parameters: W1,b1 W2,b2 W3,b3!
    // Thus, to refer to matrices W1,b1 we used params[0]->W, params[0]->b
    parameter** params = malloc((l-1) * sizeof(parameter*));

    for (int i = 0; i < (l-1); i++)
    {
        // Allocate a single `parameter` struct inside `params` array
        params[i] = malloc(sizeof(parameter));
        
        // Create the matrices with sizes based on `layers` array
        params[i]->W = matcreate(layers[i+1], layers[i]);
        params[i]->b = matcreate(layers[i+1], 1);

        // I want non-random filling of values so
        // I can try the same values easily in Python
        matfill_n(params[i]->W);
        matzeros(params[i]->b); // bias with zeroes

        // Multiply by 0.001 to make value smaller
        params[i]->W = matmul_by(params[i]->W, 0.001);
    }
    return params;
}