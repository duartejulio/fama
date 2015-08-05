#ifndef CLASSIFICADOR_H
#define CLASSIFICADOR_H

#include "corpus/corpus.h"
#include <vector>
#include <string>

class Classificador
{
    public:
        Classificador();
        virtual ~Classificador();
        virtual bool executarClassificacao( Corpus &corpusProva, int atributo ) = 0;
        //virtual vector< vector<string> > executarAlgoritmo (Corpus &corpus) = 0;
        virtual bool gravarConhecimento( string arquivo ) = 0;
        virtual bool carregarConhecimento( string arquivo ) = 0;
        virtual string descricaoConhecimento ();
};

#endif // CLASSIFICADOR_H
