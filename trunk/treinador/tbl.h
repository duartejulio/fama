#ifndef TBL_H
#define TBL_H

#include "treinador.h"
#include "../classificador/classificadortbl.h"
#include "maisprovavel.h"
#include "../outros/regra.h"
#include <cmath>

class TBL : public Treinador
{
        Classificador *classInicial;
        int toleranciaScore;
        vector< multimap< int, string > > moldeRegras;
        string atributoChute;
        bool carregarMolde( string arqMoldeRegras );
    public:
        TBL( Classificador* classInicial = NULL, string arqMoldeRegras = "", string atributoChute = "tpos", int toleranciaScore = 5 );
        virtual ~TBL();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo );
};

#endif // TBL_H
