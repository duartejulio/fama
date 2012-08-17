#ifndef VALIDADORDIVISAO_H
#define VALIDADORDIVISAO_H

#include "validador.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

class ValidadorDivisao : public Validador
{
        float percTeste;
    public:
        ValidadorDivisao( Avaliador &avaliador, int numeroIteracoes, float percTeste );
        virtual ~ValidadorDivisao();
        vector< vector< float > > executarExperimento( Treinador &treinador, Corpus &corpus, int atributoTreino, int atributoTeste );
};

#endif // VALIDADORDIVISAO_H
