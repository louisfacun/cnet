/*!
 * Author: Louis Philippe B. Facun
 * Email: louis@louisfacun.com
 */

#include "input.h"
#include "matrix.h"
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
    int L = 4;
    int layers[] = {n, 4, 5, 1};
    parameter** params = param_init(layers, L);
    matprint(params[0]->W);
    matprint(params[0]->b);
    
    // 3. Initialize weights and bias


    /*
    // W1 3=features, 4=units on layer1
    matrix *W1 = matcreate(3, 4);
    W1->values[0][0] = 1;
    W1->values[1][0] = 2;
    W1->values[2][0] = 3;
    W1->values[0][1] = 4;
    W1->values[1][1] = 5;
    W1->values[2][1] = 6;
    W1->values[0][2] = 7;
    W1->values[1][2] = 8;
    W1->values[2][2] = 9;
    W1->values[0][3] = 1;
    W1->values[1][3] = 2;
    W1->values[2][3] = 3;
    
    // b1
    matrix *b1 = matcreate(4, 1);
    b1->values[0][0] = 1;
    b1->values[1][0] = 2;
    b1->values[2][0] = 3;
    b1->values[3][0] = 4;

    // W2, 4=units prev layer, 1=unit on layer2(output)
    matrix *W2 = matcreate(4, 1);
    W2->values[0][0] = 1;
    W2->values[1][0] = 2;
    W2->values[2][0] = 3;
    W2->values[3][0] = 4;

    // b2
    matrix *b2 = matcreate(1, 1);
    b2->values[0][0] = 1;

    matrix *b1_ex = matexpand(b1, 2, 6); // broadcast! xD
    matrix *z1 = matadd_ew(matmul(mattrans(W1), in->X), b1_ex);
    matrix *a1 = matsigmoid(z1);

    matrix *b2_ex = matexpand(b2, 2, 6); // broadcast! xD
    matrix *z2 = matadd_ew(matmul(mattrans(W2), a1), b2_ex);
    matrix *a2 = matsigmoid(z2);
    
    matprint(a2);*/
  

    clock_t toc = clock();
    printf("Elapsed: %f seconds\n", ((double)(toc - tic) / CLOCKS_PER_SEC));
}