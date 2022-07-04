/*!
 * Author: Louis Philippe B. Facun
 * Email: louis@louisfacun.com
 */

#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

input* inload(char *fpath, int n, int m)
{
    /* Load training examples: X and y from comma-separated value text file.
    
    Parameters:
        fname: (string) File path of the text file. 
        n: (int) Expected number of features.
        m: (int) Expected number of training examples.

    Returns:
        in: (struct*)
    */

    FILE *fp;
    if ((fp = fopen(fpath, "r")) == NULL)
    {
        printf("Error: cannot open file.\n");
        exit(1);
    }
    
    // Storage of current file line
    char buffer[512];

    // Allocate input struct
    input *in = malloc(sizeof(input));

    // Allocate X and y matrices
    in->X = matcreate(n, m);
    in->y = matcreate(1, m);

    // Refers to (i)th training example
    int i = 0;

    // Loop all text file lines
    while(fgets(buffer, sizeof(buffer), fp))
    {
        // Split line by comma (kinda)
        char *token = strtok(buffer, ",");

        // Refers to column index
        int j = 0;
        
        // Loop through splitted lines values
        while (token != NULL)
        {
            // Expects label
            if (j == 0)
            {
                in->y->values[0][i] = atoi(token);
            }
            // Expects features
            else
            {
                // Assumes that features are already flatten
                // We subtract 1 to j because features starts from second column value (j=1)
                in->X->values[j-1][i] = atoi(token);
            }
            // Go to next column value
            token = strtok(NULL, ",");
            j++;
        }
        i++;
    }
    fclose(fp);
    return in;
}