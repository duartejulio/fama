#ifndef VALIDADORTESTE_H
#define VALIDADORTESTE_H

#include "validador.h"


class ValidadorTeste : public Validador
{
        Corpus *corpusTreino;
    public:
        ValidadorTeste( Corpus &corpusTreino );
        virtual ~ValidadorTeste();
        vector< vector< float > > executarExperimento( Treinador &treinador, Corpus &corpus );
};

#endif // VALIDADORTESTE_H
