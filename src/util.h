/*!
 * Author: Louis Philippe B. Facun
 * Email: louis@louisfacun.com
 */

#ifndef UTIL_H
#define UTIL_H

// having a problem declaring this to either network or parameter
#include "network.h"
#include "parameter.h"

void param_update(parameter **params, network_gradient **network_gs, double learning_rate, int l);

#endif