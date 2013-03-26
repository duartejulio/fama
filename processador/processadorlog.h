#ifndef PROCESSADORLOG_H
#define PROCESSADORLOG_H

#include "processador.h"

class ProcessadorLogaritmo
{
        int numatributos;
        vector<string> atributo, novosAtributos;
        bool attcriados;
        int b;



    public:
        ProcessadorLogaritmo(vector<string> atr, int b);
        vector<string> processarCorpus(Corpus&);
        ~ProcessadorLogaritmo();
        void criarAtributos(Corpus&);

};

#endif // PROCESSADORLOG_H

