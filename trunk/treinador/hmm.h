#ifndef HMM_H
#define HMM_H

#include "treinador.h"
#include "../classificador/classificadorhmm.h"

class HMM : public Treinador
{
        string atributoBase;
    public:
        HMM( string atributoBase );
        virtual ~HMM();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo );
};

#endif // HMM_H
