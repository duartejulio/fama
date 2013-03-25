#ifndef HMM_H
#define HMM_H

#include "treinador.h"
#include "../classificador/classificadorhmm.h"

class HMM : public Treinador
{
        string atributoBase;
    public:
        HMM( string atributoBase = "word" );
        virtual ~HMM();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo );
        //virtual Treinador* construirJanela( Param &popUp );
};

#endif // HMM_H
