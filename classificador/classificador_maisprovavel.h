#ifndef CLASSIFICADOR_MAISPROVAVEL_H
#define CLASSIFICADOR_MAISPROVAVEL_H

#include "classificador.h"
#include <fstream>

class ClassificadorMaisProvavel : public Classificador
{
        map< string, string > controlePalavras;
        string unknown;
        string atributoBase;
    public:
        ClassificadorMaisProvavel( string atributoBase, map< string, string > controlePalavras, string unknown );
        ClassificadorMaisProvavel();
        ClassificadorMaisProvavel( string arquivo );
        virtual bool executarClassificacao( Corpus &corpusProva, int atributo );
        virtual bool gravarConhecimento( string arquivo );
        virtual bool carregarConhecimento( string arquivo );
};

#endif // CLASSIFICADOR_MAISPROVAVEL_H
