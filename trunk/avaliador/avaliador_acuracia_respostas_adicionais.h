#ifndef AVALIADOR_ACURACIA_H
#define AVALIADOR_ACURACIA_H

#include "avaliador.h"

class AvaliadorAcuraciaRespostasAdicionais : public Avaliador
{
	vector <unsigned int> atributos;
    public:
        AvaliadorAcuraciaRespostasAdicionais(vector<unsigned int>);
        virtual ~AvaliadorAcuraciaRespostasAdicionais();
        virtual vector<float> calcularDesempenho( Corpus &corpus, int atributo_padrao, int atributo_teste );
        virtual vector<float> calcularDesempenho2( Corpus &corpus, int atributo_padrao, int atributo_teste, int atributo_considerar );

};

#endif // AVALIADOR_ACURACIA_H
