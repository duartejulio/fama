#ifndef VALIDADOR_H
#define VALIDADOR_H

#include "../corpus/corpus.h"
#include "../avaliador/avaliador.h"
#include "../treinador/treinador.h"
#define ATRBT_ANALISADO 1
#define ATRBT_CLASSIFICADO 0

class Validador
{
    public:
        Validador();
        virtual ~Validador();
//        bool ajustarNumeroIteracoes( int numeroIteracoes );
        bool ajustarAvaliador( Avaliador &avaliador );
        virtual vector< vector< float > > executarExperimento( Treinador &treinador, Corpus &corpus ) = 0;
    protected:
        Avaliador *avaliador;
        vector< vector< int > > particoes;
        bool gerarParticoesTeste();
};

#endif // VALIDADOR_H
