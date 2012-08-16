#ifndef VALIDADOR_H
#define VALIDADOR_H

#include "../corpus/corpus.h"
#include "../avaliador/avaliador.h"
#include "../treinador/treinador.h"

class Validador
{
    public:
        Validador( Avaliador &avaliador, int numeroIteracoes = 1 );
        virtual ~Validador();
        bool ajustarNumeroIteracoes( int numeroIteracoes );
        bool ajustarAvaliador( Avaliador &avaliador );
        virtual vector< vector< float > > executarExperimento( Treinador &treinador, Corpus &corpus, int atributoTreino, int atributoTeste ) = 0;
    protected:
        Avaliador *avaliador;
        int numeroIteracoes;
};

#endif // VALIDADOR_H
