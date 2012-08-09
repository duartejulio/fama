#ifndef CORPUSMATRIZ_H
#define CORPUSMATRIZ_H

#include <fstream>
#include "corpus.h"

#define INF 0x3f3f3f3f

class CorpusMatriz : public Corpus
{
    private:
        char separador;
        bool dividirExemplos;
    public:
        void ajustarSeparador(char);
        CorpusMatriz( vector<string> atributos = vector<string>(),
                      char separador = '_', bool dividirExemplos = false);
        virtual bool carregarArquivo( string arquivo );
        virtual bool gravarArquivo( string arquivo );
        virtual Corpus* clone();
};

#endif // CORPUSMATRIZ_H
