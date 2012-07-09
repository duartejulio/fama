#ifndef AVALIADOR_H
#define AVALIADOR_H

#include "corpus.h"

using namespace std;

class Avaliador
{
    public:
        Avaliador();
        virtual ~Avaliador();
        virtual vector<float> calcularDesempenho( Corpus &corpus, int atributo_padrao, int atributo_teste ) = 0;
};

#endif // AVALIADOR_H
