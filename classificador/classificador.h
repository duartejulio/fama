#ifndef CLASSIFICADOR_H
#define CLASSIFICADOR_H

#include "../corpus/corpus.h"

class Classificador
{
    public:
        Classificador();
        virtual ~Classificador();
        virtual bool executarClassificacao( Corpus &corpusProva, int atributo ) = 0;
        virtual bool gravarConhecimento( string arquivo ) = 0;
        virtual bool carregarConhecimento( string arquivo ) = 0;
        virtual string descricaoConhecimento ();
};

#endif // CLASSIFICADOR_H
