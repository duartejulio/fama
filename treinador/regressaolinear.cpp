#include "regressaolinear.h"

#include "../outros/auxfunc.h"

#include <string>
#include <sstream>
#include <iostream>


#include <stdlib.h>

bool ClassificadorRegressaoLinear::executarClassificacao(Corpus &corpus, int atributo){
    int m, i, j, v, n;
    float total, val;


    m = corpus.pegarQtdConjExemplos();//numero de exemplos
    n = theta.size();//numero de atributos + 1

    for (i=0; i<m; i++){
        total = 1.0*theta[0];
        for (j=0; j < n-1; j++){
            v = corpus.pegarValor(i, 0, j);

            (std::istringstream)(corpus.pegarSimbolo(v)) >> val >> std::dec;//converte para float
            total += theta[j + 1]*val;
        }

        //c = (string)total;
        std::ostringstream c;
        c << total << std::dec;
        corpus.ajustarValor(i, 0, atributo, corpus.pegarIndice(c.str()));
    }
    return true;
}

RegressaoLinear::RegressaoLinear(float alpha, float regularizacao):
 alpha(alpha), regularizacao(regularizacao)
{
}

RegressaoLinear::~RegressaoLinear()
{
    //dtor
}

float calculaCustoLin(float **X, float *y, float *theta, int m, int n){
    int i;
    float *HO, J;

    HO = new float[m];

    matrixVetMulti(X, theta, HO, m, n);


    J = 0;
    for (i=0; i<m; i++)
        J += (HO[i]-y[i])*(HO[i]-y[i]);
    J /= (2*m);

    delete[] HO;
    return J;
    //
}

void gradientDescentLin(float **X, float *y, float *theta, int m, int n,
                        float alpha = 0.01, float regularizacao = 0,
                        int num_iters = 1500){
    int iter, i, j;
    float *HO, *sum, A;

    HO = new float[m];
    sum = new float[n];

    for (j=0; j<n;j++)
        theta[j] = 0.0;

    for (iter = 0; iter < num_iters; iter++){
        matrixVetMulti(X, theta, HO, m, n);


        for (j=0; j<n;j++)
            sum[j] = 0.0;

        for (i = 0; i < m; i++){
            A = HO[i] - y[i];
            for (j=0; j<n;j++)
                sum[j] += A*X[i][j];
        }
        theta[0] -= alpha*sum[0]/m;
        for (j=1; j<n;j++)
            theta[j] = theta[j]*(1 - alpha*regularizacao/m) - alpha*sum[j]/m;
    }

    delete[] HO;
    delete[] sum;
}

Classificador* RegressaoLinear::executarTreinamento( Corpus &corpus, int atributo )
{
    ClassificadorRegressaoLinear *objClassificador = new ClassificadorRegressaoLinear;
    float **X, *y, *theta, val;
    int i, j, m, v, n;


    n = atributo + 1;
    m = corpus.pegarQtdConjExemplos();
    X = new float*[m];
    y = new float[m];

    theta = new float[n];
    for (i=0; i<m; i++){
        X[i] = new float[n];
        X[i][0] = 1.0;
        for (j=0; j<atributo;j++){
            v = corpus.pegarValor(i, 0, j);

            (std::istringstream)(corpus.pegarSimbolo(v)) >> val >> std::dec;//converte para float
            X[i][j + 1] = val;
        }
        v = corpus.pegarValor(i, 0, atributo);

        (std::istringstream)(corpus.pegarSimbolo(v)) >> val >> std::dec;//converte para float
        y[i] = val;
    }

    gradientDescentLin(X, y, theta, m, n, alpha, regularizacao);

    objClassificador->ajustarTheta(theta, n);
    //cout << "\n" << m << " " << calculaCustoLin(X, y, theta, m, n) << "\n" << theta[0] << ", " << theta[1] << endl;
    delete[] theta;
    delete[] y;
    for (i=0; i<m; i++)
        delete[] X[i];
    delete[] X;

    return objClassificador;
}
