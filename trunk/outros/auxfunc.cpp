#include "auxfunc.h"

#include "math.h"

//r = axb (a[m][n] b[n])
void matrixVetMulti(float **a, float *b, float *r, int m, int n){
    int i, j;

    for (i=0;i<m;i++){
        r[i] = 0.0;
        for (j=0;j<n;j++)
            r[i] += a[i][j]*b[j];
    }
}

//g(z) = 1 / (1 + e^-z)
float sigmoid(float z){
    return 1.0/(1.0 + exp(-z));
}

//g[z] = 1 / (1 + e^-g[z]) //para todo z
void inplace_sigmoid(float z[], int m){
    for (int i=0; i<m; i++)
        z[i] = 1.0/(1.0 + exp(-z[i]));
}

