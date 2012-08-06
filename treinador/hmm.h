#ifndef HMM_H
#define HMM_H

#include "treinador.h"
#include "../classificador/classificadorhmm.h"

class HMM : public Treinador
{
    public:
        virtual ~HMM();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo );
};

#endif // HMM_H
