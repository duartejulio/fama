#ifndef ADABOST_H
#define ADABOST_H

#include "treinador.h"
#include "../classificador/classificador.h"

class TreinadorAdaboost : public Treinador
{
    Treinador &base;
    vector<string> classes;
    unsigned iterations;
    double minalpha;
    bool aceitaDistribuicao;
    vector<double> distribuicaoInicial;
public:
    TreinadorAdaboost(Treinador &base, vector<string> classes, unsigned iterations=10, double minalpha = 0.01, bool aceitaDistribuicao = true);
    virtual ~TreinadorAdaboost() {}
    Classificador* executarTreinamento( Corpus &corpus, int atributo );
    void ajustaDistribuicaoInicial(vector<double>);
};

#endif // ADABOST_H
