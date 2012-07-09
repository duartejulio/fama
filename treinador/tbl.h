#ifndef TBL_H
#define TBL_H

#include "treinador.h"
#include "classificadortbl.h"
#include "maisprovavel.h"
#include <set>
#define LIM_FREQ_UNKNOWN 3
#define ATRBT_UTILIZADO "pos"
#define ATRBT_CLASSIFICADO 0

class TBL : public Treinador
{
        Classificador *classInicial;
        int toleranciaScore;
        vector< map< int, string > > moldeRegras;
        bool carregarMolde( string arqMoldeRegras );
//        bool salvarEstado( string saveFile, vector<int> good, vector<int> bad );
//        bool carregarEstado( string saveFile, vector<int> &good, vector<int> &bad );
    public:
        TBL( Classificador* classInicial, string arqMoldeRegras, int toleranciaScore );
        virtual ~TBL();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo );
};

#endif // TBL_H
