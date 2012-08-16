#ifndef CLASSIFICADOR_MAISPROVAVEL_H
#define CLASSIFICADOR_MAISPROVAVEL_H

#include "classificador.h"
#include <fstream>

class ClassificadorMaisProvavel : public Classificador
{
        map< string, string > controlePalavras;
        string unknown;
    public:
        ClassificadorMaisProvavel( string atributoBase = NULL );
        virtual bool executarClassificacao( Corpus &corpusProva, int atributo );
        void ajustarcontrolePalavras( string indice, string valor );
        void ajustarUnknown( string val );
        virtual bool gravarConhecimento( string arquivo );
        virtual bool carregarConhecimento( string arquivo );
};

#endif // CLASSIFICADOR_MAISPROVAVEL_H
