#ifndef C50TREINADOR_H
#define C50TREINADOR_H

#include "treinador.h"
//#include "../classificador/c50classificador.h"


class C50Treinador : public Treinador
{
        vector<string> atributos;
		vector<string> classes;
        float cf;
    public:
        C50Treinador(float cf, vector<string> atributos, vector<string> classes);
        void ajustarAtributos(vector<string> atr){atributos = atr;}
        virtual ~C50Treinador();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo );
};

#endif // C50TreinadorTREINADOR_H
