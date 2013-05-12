#ifndef PROCESSADORLOG_H
#define PROCESSADORLOG_H

#include "processador.h"

class ProcessadorLogaritmo
{
        int numatributos;
        vector<string> atributo, novosAtributos;
        bool attcriados;
        int b;
        float maxvalor;
        float minvalor;
        float normalizador;



    public:
        ProcessadorLogaritmo(vector<string> atr, int b, float normalizador);
        vector<string> processarCorpus(Corpus&);
        void normalizarCorpus(Corpus&);
        ~ProcessadorLogaritmo();
        void criarAtributos(Corpus&);

};

#endif // PROCESSADORLOG_H

