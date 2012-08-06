#ifndef VALIDADORKDOBRAS_H
#define VALIDADORKDOBRAS_H

#include "validador.h"


class ValidadorKDobras : public Validador
{
        int dobras;
    public:
        ValidadorKDobras( int dobras );
        virtual ~ValidadorKDobras();
        vector< vector< float > > executarExperimento( Treinador &treinador, Corpus &corpus );

};

#endif // VALIDADORKDOBRAS_H
