#ifndef AVALIADOR_MATRIZ_CONFUSAO_H
#define AVALIADOR_MATRIZ_CONFUSAO_H

#include "avaliador.h"

class AvaliadorMatrizConfusao : public Avaliador
{
        vector<string> classes;
        vector<float> ultimaMatriz;
    public:
        AvaliadorMatrizConfusao(vector<string>);
        virtual ~AvaliadorMatrizConfusao();
        virtual vector<float> calcularDesempenho( Corpus &corpus, int atributo_padrao, int atributo_teste );
        virtual bool imprimirMatrizConfusao();
        virtual vector<float> calcularDesempenho2( Corpus &corpus, int atributo_padrao, int atributo_teste, int atributo_considerar ){return vector<float>();}

};

#endif // AVALIADOR_MATRIZ_CONFUSAO_H
