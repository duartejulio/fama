#ifndef VALIDADORKDOBRAS_H
#define VALIDADORKDOBRAS_H

#include "validador.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

class ValidadorKDobras : public Validador
{
    public:
        ValidadorKDobras( Avaliador &avaliador, int dobras );
        virtual ~ValidadorKDobras();
        vector< vector< float > > executarExperimento( Treinador &treinador, Corpus &corpus, int atributoTreino, int atributoTeste );

};

#endif // VALIDADORKDOBRAS_H
