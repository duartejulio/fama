#ifndef VALIDADORTREINO_H
#define VALIDADORTREINO_H

#include "validador.h"

class ValidadorTreino : public Validador
{
    public:
        ValidadorTreino();
        virtual ~ValidadorTreino();
        vector< vector< float > > executarExperimento( Treinador &treinador, Corpus &corpus );
};

#endif // VALIDADORTREINO_H
