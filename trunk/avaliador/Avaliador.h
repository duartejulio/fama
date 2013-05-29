#ifndef AVALIADOR_H
#define AVALIADOR_H

#include "../corpus/corpus.h"

class Avaliador
{
    public:
        Avaliador();
        virtual ~Avaliador();
        virtual vector<float> calcularDesempenho( Corpus &corpus, int atributo_padrao, int atributo_teste ) = 0;
        virtual vector<float> calcularDesempenho2( Corpus &corpus, int atributo_padrao, int atributo_teste, int atributo_considerar ) = 0;
};

#endif // AVALIADOR_H
