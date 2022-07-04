/*!
 * Author: Louis Philippe B. Facun
 * Email: louis@louisfacun.com
 */

#include "activation.h"
#include <math.h>

double sigmoid(double z)
{
    // Sigmoid / logistic function.
    return 1 / (1 + exp(-1 * z));
}


double relu(double z)
{
    // Rectified Linear Unit (RELU) -> max(0, z)
    return z <= 0 ? 0 : z;
}