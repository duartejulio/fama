#ifndef REGRESSAOLOGISTICA_H
#define REGRESSAOLOGISTICA_H

#include <map>
#include <vector>
#include "treinador.h"

using namespace std;

class ClassificadorRegressaoLogistica:public Classificador{
    private:
        vector<float> theta;
        vector<string> classes;
    public:
        ClassificadorRegressaoLogistica(){
        }
        void ajustarTheta(float *theta, int n){
            this->theta.resize(n);
            for (int i = 0; i < n; i++)
                this->theta[i] = theta[i];
        }
        ~ClassificadorRegressaoLogistica(){
            theta.resize(0);
        }
        virtual bool executarClassificacao(Corpus&, int);
        void ajustarClasses(vector<string> classes){
            this->classes = classes;
        }
        bool gravarConhecimento(string){throw "Não Implementado";}
        bool carregarConhecimento(string){throw "Não Implementado";}
};


class RegressaoLogistica : public Treinador
{
    vector<string> classes;
    public:
        RegressaoLogistica(vector<string> classes);
        virtual ~RegressaoLogistica();
        virtual Classificador* executarTreinamento( Corpus &corpus, int atributo );
};

#endif // MAISPROVAVEL_H
