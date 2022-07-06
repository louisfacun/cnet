/*!
 * Author: Louis Philippe B. Facun
 * Email: louis@louisfacun.com
 */

#include "activation.h"
#include "matrix.h"

#include <math.h>

double sigmoid(double Z)
{
    double A;
    A  = 1 / (1 + exp(-1 * Z));

    return A; 
}

double relu(double Z)
{
    double A;
    A = (Z <= 0) ? 0 : Z;

    return A;
}
