#ifndef AVALIADOR_DIFERENCA_H
#define AVALIADOR_DIFERENCA_H

#include "avaliador.h"

class AvaliadorDiferenca : public Avaliador
{
    public:
        AvaliadorDiferenca();
        virtual ~AvaliadorDiferenca();
        virtual vector<float> calcularDesempenho( Corpus &corpus, int atributo_padrao, int atributo_teste );
};

#endif // AVALIADOR_DIFERENCA_H
