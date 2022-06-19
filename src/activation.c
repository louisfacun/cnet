#include "activation.h"

#include <math.h>

// Sigmoid/logistic function
double sigmoid(double z)
{
    return 1 / (1 + exp(-1 * z));
}

// Rectified Linear Unit (RELU) -> max(0, z)
double relu(double z)
{
    return z <= 0 ? 0 : z;
}