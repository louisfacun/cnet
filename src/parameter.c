/*!
 * Author: Louis Philippe B. Facun
 * Email: louis@louisfacun.com
 */

#include "parameter.h"
#include "matrix.h"

#include <stdlib.h>

parameter** param_init(int layers[], int l)
{
    parameter **params = malloc((l-1) * sizeof(parameter*));

    for (int i = 0; i < (l-1); i++) {
        params[i] = malloc(sizeof(parameter));
        
        params[i]->W = matcreate(layers[i+1], layers[i]);
        params[i]->b = matcreate(layers[i+1], 1);

        matran(params[i]->W);
        //matran(params[i]->b);
        matzeros(params[i]->b); // bias with zeroes

        params[i]->W = matmul_by(params[i]->W, 0.001);
        //params[i]->b = matmul_by(params[i]->b, 0.001);
    }
    return params;
}