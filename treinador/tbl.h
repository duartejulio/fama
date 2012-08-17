#ifndef TBL_H
#define TBL_H

#include "treinador.h"
#include "../classificador/classificadortbl.h"
#include "maisprovavel.h"
#include "../outros/regra.h"
#include <cmath>
#define ATRBT_CLASSIFICADO 0

class TBL : public Treinador
{
        Classificador *classInicial;
        int toleranciaScore;
        vector< multimap< int, string > > moldeRegras;
        string atributoChute;
        bool carregarMolde( string arqMoldeRegras );
    public:
        TBL( Classificador* classInicial, string arqMoldeRegras, string atributoChute, int toleranciaScore );
        virtual ~TBL();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo );
};

#endif // TBL_H
