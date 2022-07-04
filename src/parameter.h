/*!
 * Author: Louis Philippe B. Facun
 * Email: louis@louisfacun.com
 */

#ifndef PARAMETER_H
#define PARAMETER_H

#include "matrix.h"

typedef struct
{
    matrix *W; // Weights
    matrix *b; // Biases
}
parameter;

parameter** param_init(int layers[], int l);

#endif