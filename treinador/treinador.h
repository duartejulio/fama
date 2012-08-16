#ifndef TREINADOR_H
#define TREINADOR_H

#include "../corpus/corpus.h"
#include "../classificador/classificador.h"

class Treinador
{
    protected:
        string atributoBase;
    public:
        Treinador( string atributoBase );
        virtual ~Treinador();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo ) = 0;
};

#endif // TREINADOR_H
