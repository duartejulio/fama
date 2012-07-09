#ifndef TREINADOR_H
#define TREINADOR_H

#include "corpus.h"
#include "classificador.h"

class Treinador
{
    public:
        Treinador();
        virtual ~Treinador();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo ) = 0;
};

#endif // TREINADOR_H
