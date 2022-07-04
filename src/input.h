#ifndef INPUT_H
#define INPUT_H

#include "matrix.h"

typedef struct
{
    matrix *X; // Input features
    matrix *y; // Input labels
}
input;

input* inload(char *fname, int n, int m);

#endif