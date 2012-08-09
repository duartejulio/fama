#include "regressaologistica.h"

#include "../outros/auxfunc.h"

#include <string>
#include <sstream>
#include <iostream>

#include <math.h>
#include <stdlib.h>

bool ClassificadorRegressaoLogistica::executarClassificacao(Corpus &corpus, int atributo){
    int m, i, j, v, n;
    float total, val;
    string c;

    m = corpus.pegarQtdConjExemplos();//numero de exemplos
    n = theta.size();//numero de atributos + 1

    for (i=0; i<m; i++){
        total = 1.0*theta[0];
        for (j=0; j < n-1; j++){
            v = corpus.pegarValor(i, 0, j);

            (std::istringstream)(corpus.pegarSimbolo(v)) >> val >> std::dec;//converte para float
            total += theta[j + 1]*val;
        }

        c = classes[(sigmoid(total) >= 0.5)?1:0];
        corpus.ajustarValor(i, 0, atributo, corpus.pegarIndice(c));
    }
    return true;
}

RegressaoLogistica::RegressaoLogistica(vector<string> classes)
{
    this->classes = classes;
}

RegressaoLogistica::~RegressaoLogistica()
{
    //dtor
}

float calculaCustoLog(float **X, int *y, float *theta, int m, int n){
    int i;
    float *HO, J;

    HO = new float[m];

    matrixVetMulti(X, theta, HO, m, n);
    inplace_sigmoid(HO, m);

    J = 0;
    for (i=0; i<m; i++)
        J -= y[i]*log(HO[i]) + (1 - y[i])*log(1.0 - HO[i]);
    J /= m;

    delete[] HO;
    return J;
    //
}

void gradientDescentLog(float **X, int *y, float *theta, int m, int n, float alpha = 0.01, int num_iters = 1500){
    int iter, i, j;
    float *HO, *sum, A;

    HO = new float[m];
    sum = new float[n];

    for (j=0; j<n;j++)
        theta[j] = 0.0;

    for (iter = 0; iter < num_iters; iter++){
        matrixVetMulti(X, theta, HO, m, n);
        inplace_sigmoid(HO, m);

        for (j=0; j<n;j++)
            sum[j] = 0.0;

        for (i = 0; i < m; i++){
            A = HO[i] - y[i];
            for (j=0; j<n;j++)
                sum[j] += A*X[i][j];
        }

        for (j=0; j<n;j++)
            theta[j] -= alpha*sum[j]/m;
    }

    delete[] HO;
    delete[] sum;
}

Classificador* RegressaoLogistica::executarTreinamento( Corpus &corpus, int atributo )
{
    ClassificadorRegressaoLogistica *objClassificador = new ClassificadorRegressaoLogistica;
    float **X, *theta, val;
    int *y, i, j, m, v, n;
    map<string, int> classeMap;

    classeMap[classes[0]] = 0;
    classeMap[classes[1]] = 1;

    n = atributo + 1;
    m = corpus.pegarQtdConjExemplos();
    X = new float*[m];
    y = new int[m];

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

        y[i] = classeMap[corpus.pegarSimbolo(v)];
    }

    gradientDescentLog(X, y, theta, m, n);

    objClassificador->ajustarClasses(classes);
    objClassificador->ajustarTheta(theta, n);
    //cout << "\n" << m << " " << calculaCustoLog(X, y, theta, m, n) << "\n" << theta[0] << ", " << theta[1] << ", " << theta[2];
    delete[] theta;
    delete[] y;
    for (i=0; i<m; i++)
        delete[] X[i];
    delete[] X;

    return objClassificador;
}
