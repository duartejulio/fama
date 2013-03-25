#ifndef MAISPROVAVEL_H
#define MAISPROVAVEL_H

#include "treinador.h"
#include "../classificador/classificador_maisprovavel.h"


class MaisProvavel : public Treinador
{
        int toleranciaUnknow;
        string atributoBase;
    public:
        MaisProvavel( string atributoBase = "word", int toleranciaUnknow = 2 );
        virtual ~MaisProvavel();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo );
};

#endif // MAISPROVAVEL_H
