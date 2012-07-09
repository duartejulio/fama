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
    public:
        virtual bool executarClassificacao( Corpus &corpusProva, int atributo );
        void definirMatrizTransicao( map< string, map< string, double > > matrizTransicao );
        void ajustarTabFreqObservacoes( string pos, string palavra );
        void ajustarVetInicial( string pos );
        virtual bool gravarConhecimento( string arquivo );
        virtual bool carregarConhecimento( string arquivo );
};

#endif // CLASSIFICADORHMM_H
