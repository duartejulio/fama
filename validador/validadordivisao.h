#ifndef VALIDADORDIVISAO_H
#define VALIDADORDIVISAO_H

#include "validador.h"


class ValidadorDivisao : public Validador
{
        float percTeste;
        int numeroIteracoes;
    public:
        ValidadorDivisao( float percTeste, int numeroIteracoes );
        virtual ~ValidadorDivisao();
        vector< vector< float > > executarExperimento( Treinador &treinador, Corpus &corpus );
};

#endif // VALIDADORDIVISAO_H
