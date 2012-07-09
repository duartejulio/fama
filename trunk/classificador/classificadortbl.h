#ifndef CLASSIFICADORTBL_H
#define CLASSIFICADORTBL_H

#include "classificador.h"
#include "maisprovavel.h"
#include <fstream>
#define LIM_FREQ_UNKNOWN 3
#define ATRBT_ANALISADO 1

class ClassificadorTBL : public Classificador
{
        ///pode ter este atributo aqui?
        Classificador* classInicial;
        vector< map< int, map< string, string > > > regras;
        vector< string > respRegras;
    public:
        ClassificadorTBL( Classificador* classInicial );
        virtual ~ClassificadorTBL();
        virtual bool executarClassificacao( Corpus &corpusProva, int atributo );
        void inserirRegra( map< int, map< string, string > > rule, string resp );
        virtual bool gravarConhecimento( string arquivo );
        virtual bool carregarConhecimento( string arquivo );
};

#endif // CLASSIFICADORTBL_H
