#ifndef TBL_H
#define TBL_H

#include "treinador.h"
#include "classificadortbl.h"
#include "maisprovavel.h"
#include "regra.h"
#include <algorithm>
#include <cmath>
#define ATRBT_CLASSIFICADO 0

class TBL : public Treinador
{
        Classificador *classInicial;
        int toleranciaScore;
        vector< multimap< int, string > > moldeRegras;
        bool carregarMolde( string arqMoldeRegras );
        bool contemEstrutura( multimap< int, vector< int > > estrutura, multimap< int, vector< int > > bestEstrutura );
    public:
        TBL( Classificador* classInicial, string arqMoldeRegras, int toleranciaScore );
        virtual ~TBL();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo );
};

#endif // TBL_H
