#ifndef CORPUSMATRIZC50_H
#define CORPUSMATRIZC50_H

#include <fstream>
#include <vector>
#include "corpus.h"
#include "../C50/c50.h"


#define INF 0x3f3f3f3f

class CorpusC50 : public Corpus
{
    private:
        char separador;
        bool dividirExemplos;
        bool apararValores;
        vector<string> classes;
        vector< vector<string> > attValName;
    public:
        void ajustarSeparador(char);
        CorpusC50( vector<string> atributos = vector<string>(),
                      char separador = '_', bool dividirExemplos = false,
                      bool apararValores = false);
        bool carregarArquivo(string arquivo );
        bool carregarArquivo2(string arquivo );
        bool gravarArquivo( string arquivo );
        void adicionarCasos(C50 &objc50);
        void casos(C50 &objc50);
        vector<string> pegarClasses();
        vector< vector<string> > pegarAttValores();
        virtual Corpus* clone();
};

#endif // CORPUSMATRIZ_H

