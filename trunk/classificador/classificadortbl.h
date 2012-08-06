#ifndef CLASSIFICADORTBL_H
#define CLASSIFICADORTBL_H

#include "classificador.h"
#include "../treinador/maisprovavel.h"
#include <fstream>
#define LIM_FREQ_UNKNOWN 3
#define ATRBT_ANALISADO 1

class ClassificadorTBL : public Classificador
{
        Classificador* classInicial;
        vector< multimap< int, vector< string > > > regras;
        vector< string > respRegras;
    public:
        ClassificadorTBL( Classificador* classInicial );
        virtual ~ClassificadorTBL();
        virtual bool executarClassificacao( Corpus &corpusProva, int atributo );
        void inserirRegra( multimap< int, vector< string > > rule, string resp );
        virtual bool gravarConhecimento( string arquivo );
        virtual bool carregarConhecimento( string arquivo );
};

#endif // CLASSIFICADORTBL_H
