#ifndef CLASSIFICADORHMM_H
#define CLASSIFICADORHMM_H

#include "classificador.h"
#include <fstream>
#include <cmath>

class ClassificadorHMM : public Classificador
{
        map< string, map< string, double > > matrizTransicao;
        map< string, map< string, double > > tabFreqObservacoes;
        map< string, double > vetInicial;
        string atributoBase;
    public:
        ClassificadorHMM( string atributoBase, map< string, double > vetInicial, map< string, map< string, double > > matrizTransicao, map< string, map< string, double > > tabFreqObservacoes );
        ClassificadorHMM();
        ClassificadorHMM( string arquivo );
        virtual bool executarClassificacao( Corpus &corpusProva, int atributo );
        virtual bool gravarConhecimento( string arquivo );
        virtual bool carregarConhecimento( string arquivo );
};

#endif // CLASSIFICADORHMM_H
