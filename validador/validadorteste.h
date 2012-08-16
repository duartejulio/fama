#ifndef VALIDADORTESTE_H
#define VALIDADORTESTE_H

#include "validador.h"


class ValidadorTeste : public Validador
{
        Corpus *corpusTeste;
    public:
        ValidadorTeste( Avaliador &avaliador, Corpus &corpusTeste );
        virtual ~ValidadorTeste();
        vector< vector< float > > executarExperimento( Treinador &treinador, Corpus &corpus, int atributoTreino, int atributoTeste );
};

#endif // VALIDADORTESTE_H
