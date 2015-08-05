#ifndef TREINADOR_H
#define TREINADOR_H

#include "../corpus/corpus.h"
#include "../classificador/classificador.h"

class Treinador
{
    public:
        Treinador();
        virtual ~Treinador();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo ) = 0;
        virtual Treinador* construirJanela( void *popUp, Corpus &corpus );
};

#endif // TREINADOR_H
