#ifndef VALIDADORTREINO_H
#define VALIDADORTREINO_H

#include "validador.h"

class ValidadorTreino : public Validador
{
    public:
        ValidadorTreino( Avaliador &avaliador );
        virtual ~ValidadorTreino();
        vector< vector< float > > executarExperimento( Treinador &treinador, Corpus &corpus, int atributoTreino, int atributoTeste );
};

#endif // VALIDADORTREINO_H
