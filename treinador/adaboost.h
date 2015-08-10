#ifndef ADABOST_H
#define ADABOST_H

#include "treinador.h"
#include "../classificador/classificador.h"

class TreinadorAdaboost : public Treinador
{
    TreinadorDistribuicao &base;
    vector<string> classes;
    unsigned iterations;
    double minalpha;
public:
    TreinadorAdaboost(TreinadorDistribuicao &base, vector<string> classes, unsigned iterations=10, double minalpha = 0.01);
    virtual ~TreinadorAdaboost() {}
    Classificador* executarTreinamento( Corpus &corpus, int atributo );
};

#endif // ADABOST_H
