/*!
 * Author: Louis Philippe B. Facun
 * Email: louis@louisfacun.com
 */

#ifndef NETWORK_H
#define NETWORK_H

#include "matrix.h"
#include "parameter.h"

matrix* netforward_z(matrix *A, matrix *W, matrix *b);
matrix* netforward_a(matrix *A, matrix *W, matrix *b, char *activation);
matrix* netforward(matrix *X, parameter **params, int l);
double netcost(matrix *A, matrix *y);

#endif