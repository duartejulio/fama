#ifndef MAISPROVAVEL_H
#define MAISPROVAVEL_H

#include "treinador.h"
#include "../classificador/classificador_maisprovavel.h"


class MaisProvavel : public Treinador
{
        int toleranciaUnknow;
    public:
        MaisProvavel( int toleranciaUnknow );
        virtual ~MaisProvavel();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo );
};

#endif // MAISPROVAVEL_H
