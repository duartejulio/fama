#ifndef REGRESSAOLINEAR_H
#define REGRESSAOLINEAR_H

#include <map>
#include <vector>
#include "treinador.h"

using namespace std;

class ClassificadorRegressaoLinear:public Classificador{
        vector<float> theta;
    public:
        ClassificadorRegressaoLinear(){
        }
        void ajustarTheta(float *theta, int n){
            this->theta.resize(n);
            for (int i = 0; i < n; i++)
                this->theta[i] = theta[i];
        }
        ~ClassificadorRegressaoLinear(){
            theta.resize(0);
        }
        bool executarClassificacao(Corpus&, int);
        bool gravarConhecimento(string){throw "Não Implementado";}
        bool carregarConhecimento(string){throw "Não Implementado";}
};

class RegressaoLinear : public Treinador
{
        float alpha, regularizacao;
    public:
        RegressaoLinear(float alpha = 0.01, float regularizacao = 0.0);
        virtual ~RegressaoLinear();
        virtual Classificador* executarTreinamento( Corpus &corpus, int atributo );
};

#endif // MAISPROVAVEL_H
