#ifndef TREINADORC50_H
#define TREINADORC50_H

#include "treinador.h"
#include "../classificador/classificadorc50.h"


class TreinadorC50 : public Treinador
{
        vector<string> atributos;
		vector<string> classes;
		vector< vector<string> > attValName;
		C50 objC50;
                float cf;
    public:
        TreinadorC50( vector<string> atributos, vector<string> classes, vector< vector<string> > attValName,C50 objC50, float cf );
        virtual ~TreinadorC50();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo );
};

#endif // TREINADORC50_H
