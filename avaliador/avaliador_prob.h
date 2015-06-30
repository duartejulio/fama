#ifndef AVALIADOR_PROB_H
#define AVALIADOR_PROB_H

#include "Avaliador.h"

class AvaliadorProvavel: public Avaliador
{
    private:
        vector<bool> considerar;
    public:
        AvaliadorProvavel() {}
        virtual ~AvaliadorProvavel() {}
        virtual vector<float> calcularDesempenho( Corpus &corpus, int atributo_padrao, int atributo_teste );
};

#endif // AVALIADOR_H
